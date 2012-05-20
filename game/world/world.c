#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../modules/parser/xml.h"
#include "../../modules/map/map.h"
#include "../../modules/landscape/landscape.h"
#include "../../modules/player/player.h"
#include "../../modules/city/city.h"
#include "../../modules/unit/unit.h"
#include "../../modules/unit/unit_table.h"
#include "../../modules/unit/unit_common_info.h"
#include "../../modules/technology/technology_parse_info.h"
#include "../../modules/technology/technology_table.h"
#include "../../modules/log/log.h"
#include "../../modules/fog/fog.h"

#include "world_errors.h"
#include "world.h"

World * createWorld(FILE * log)
{
    // Allocate memory for world.
    World * world = malloc(sizeof(World));

    // Parsing config.xml.
    world -> properties = parseXML(XML_CONFIG);
    if(!noErrorsInWorldProperties(log, world -> properties))
    {
        return NULL;
    }

    // Parsing units.xml.
    world -> units_info = parseXML(XML_UNITS);
    if(!noErrorsInUnitsInfo(log, world -> units_info))
    {
        return NULL;
    }

    // Parsing technologies.xml.
    DynArray * techs_data = parseXML(XML_TECHNOLOGIES);
    if(!noErrorsInTechsData(log, techs_data))
    {
        return NULL;
    }

    // Creating edges in technology tree (we already have nodes).
    world -> tech_tree = createEdgesInTechnologyTree(techs_data);

    // Creating techs_info table.
    world -> techs_info = daCreate();
    for(int i = 0; i < techs_data -> length; i++)
    {
        TechnologyParseInfo * t = (TechnologyParseInfo *) daGetByIndex(techs_data, i);
        daPrepend(world -> techs_info, t -> tech_in_tree);
    }

    // Creating tech tables.
    IntArray * tech_table = createTechnologyTable(world -> techs_info);

    // Creating unit tables.
    IntArray * unit_table = createUnitTable(tech_table, world -> techs_info, world -> units_info);

    // Free techs_data.
    daDestroy(techs_data, &destroyTechnologyParseInfo);

    // Creating map and landscape.
    world -> map = createMap(world -> properties -> map_r, world -> properties -> map_c);
    generateMap(world -> map);

    // Creating players list.
    world -> graph_players = NULL; // Graph head.
    Node * temp = NULL;            // Temporary variable.
    for(int i = 0; i < world -> properties -> players_count; i++)
    {
        // Creating new player.
        char * name = (char *) daGetByIndex(world -> properties -> player_names, i);
        char * city_name = (char *) daGetByIndex(world -> properties -> player_cities, i);
        Player * player = createPlayer(name, iaCopy(unit_table), iaCopy(tech_table));
        // Adding player colour.
        player -> colour = i % PLAYER_COLOURS_COUNT;
        // Add player's fog.
        player -> fog = createFog(world -> map -> max_r, world -> map -> max_c);
        // Creating default city.
        // createCity() function returns NULL, if nothing created. Trying create
        // city!
        City * city = NULL;
        while(city == NULL)
        {
            city = createCity(world, city_name, rand() % world -> properties -> map_r, rand() % world -> properties -> map_c, player);
        }
        createUnit(world, city -> r, city -> c, 14, player);
        player -> graph_map = world -> map -> head;
        temp = addNode(temp, EDGE_NEXT_PLAYER, NODE_PLAYER, player);
        // Remembering head.
        if(world -> graph_players == NULL)
        {
            world -> graph_players = temp;
        }
    }
    // Computer player.
    char * name = malloc(sizeof(char) * 8);
    Player * player = createPlayer(strcpy(name, "Neutral"), NULL, NULL);
    player -> is_computer = 1;
    player -> colour = 5;
    // Generating units.
    int r, c, counter = 0;
    while(counter < 2 * world -> properties -> players_count)
    {
        r = rand() % world -> properties -> map_r;
        c = rand() % world -> properties -> map_c;
        Cell * cell = (Cell *) getMapCell(world -> map, r, c) -> data;
        if(cell -> territory != CELL_TYPE_WATER)
        {
            // Creating caravans.
            createUnit(world, r, c, 13, player);
            counter++;
        }
    }
    temp = addNode(temp, EDGE_NEXT_PLAYER, NODE_PLAYER, player);
    world -> computer = player;

    // Link list.
    addEdge(temp, world -> graph_players, EDGE_NEXT_PLAYER);

    iaDestroy(unit_table);
    iaDestroy(tech_table);

    printf("Done\n");

    printf("All done!\n");

    // Returning world.
    return world;
}

/*
    Deletes graph's node.
*/
void destroyGraphNode(unsigned char type, void * data)
{
    switch(type)
    {
        case NODE_PLAYER:
            destroyPlayer( ((Player *) data) );
        break;
    }
}

void destroyWorld(World * world)
{
    // Auxiliary array for destroyGraph();
    DynArray * deleted = daCreate();

    // Destroy map.
    destroyMap(world -> map);

    // Destroy properties.
    daDestroy(world -> properties -> player_names, NULL);
    daDestroy(world -> properties -> player_cities, NULL);
    free(world -> properties);

    // Destroy array of UnitCommonInfos.
    daDestroy(world -> units_info, &destroyUnitCommonInfo);

    // Destroy array of pointers to tech_in_tree.
    daDestroy(world -> techs_info, &destroyTechnology);

    // Destroy world.
    destroyGraph(world -> graph_players, deleted, &destroyGraphNode);
    free(world);

    // Destroy auxiliary array.
    daDestroy(deleted, NULL);
}
