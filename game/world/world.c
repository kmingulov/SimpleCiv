#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../modules/parser/xml.h"
#include "../../modules/cell/cell.h"
#include "../../modules/landscape/landscape.h"
#include "../../modules/player/player.h"
#include "../../modules/city/city.h"
#include "../../modules/unit/unit.h"
#include "../../modules/unit/unit_table.h"
#include "../../modules/unit/unit_common_info.h"
#include "../../modules/technology/technology_parse_info.h"
#include "../../modules/technology/technology_table.h"
#include "world.h"

World * createWorld()
{
    // Allocate memory for world.
    World * world = malloc(sizeof(World));

    // Parsing config.xml.
    printf("Parsing config.xml… ");
    world -> properties = parseXML(XML_CONFIG);
    if(world -> properties == NULL)
    {
        printf("Failed\n\033[1;31mError:\033[0m config.xml doesn't exist or corrupted.\n");
        return NULL;
    }
    printf("Done\n");

    // Parsing units.xml.
    printf("Parsing resources/units.xml… ");
    world -> units_info = parseXML(XML_UNITS);
    if(world -> units_info == NULL)
    {
        printf("Failed\n\033[1;31mError:\033[0m resources/units.xml doesn't exist or corrupted.\n");
        return NULL;
    }
    printf("%d units loaded\n", world -> units_info -> length);

    // Parsing technologies.xml.
    printf("Parsing resources/technologies.xml… ");
    DynArray * techs_data = parseXML(XML_TECHNOLOGIES);
    if(techs_data == NULL)
    {
        printf("Failed\n\033[1;31mError:\033[0m resources/technologies.xml doesn't exist or corrupted.\n");
        return NULL;
    }
    printf("%d technologies loaded\n", techs_data -> length);

    // Going through techs_data and creating tech tree.
    printf("Creating technology tree… ");
    // Creates edges in technology tree (we already have nodes).
    world -> tech_tree = createEdgesInTechnologyTree(techs_data);
    printf("Done\n");

    // Creating techs_info table.
    world -> techs_info = daCreate();
    for(int i = 0; i < techs_data -> length; i++)
    {
        TechnologyParseInfo * t = (TechnologyParseInfo *) daGetByIndex(techs_data, i);
        daPrepend(world -> techs_info, t -> tech_in_tree);
    }

    // Creating tech tables.
    printf("Creating technology table… ");
    IntArray * tech_table = createTechnologyTable(world -> techs_info);
    printf("Done\n");

    // Creating unit tables.
    printf("Creating units table… ");
    IntArray * unit_table = createUnitTable(tech_table, world -> techs_info, world -> units_info);
    printf("Done\n");

    // Free techs_data.
    printf("Freeing auxiliary data… ");
    daDestroy(techs_data, &destroyTechnologyParseInfo);
    printf("Done\n");

    // Creating map.
    printf("Creating map %dx%d… ", world -> properties -> map_r, world -> properties -> map_c);
    world -> graph_map = createMap(world -> properties -> map_r, world -> properties -> map_c);
    printf("Done\n");

    printf("Creating landscape… ");
    generateMap(world -> graph_map, world -> properties -> map_r, world -> properties -> map_c);
    printf("Done\n");

    // Creating players list.
    printf("Creating list of %d players… ", world -> properties -> players_count);
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
        // Creating default city.
        // createCity() function returns NULL, if nothing created. Trying create
        // city!
        City * city = NULL;
        while(city == NULL)
        {
            city = createCity(world, city_name, rand() % world -> properties -> map_r, rand() % world -> properties -> map_c, player);
        }
        createUnit(world, city -> r, city -> c, 14, player);
        player -> graph_map = world -> graph_map;
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
        Cell * cell = (Cell *) getCell(world -> graph_map, r, c) -> data;
        if(cell -> territory != CELL_TYPE_WATER)
        {
            // Creating caravans.
            createUnit(world, r, c, 13, player);
            counter++;
        }
    }
    temp = addNode(temp, EDGE_NEXT_PLAYER, NODE_PLAYER, player);

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
    destroyMap(world -> graph_map, world -> properties -> map_r, world -> properties -> map_c);

    // Destroy properties.
    daDestroy(world -> properties -> player_names, NULL);
    daDestroy(world -> properties -> player_cities, NULL);
    free(world -> properties);

    // Destroy array of UnitCommonInfos.
    daDestroy(world -> units_info, &destroyUnitCommonInfo);

    // Destroy array of pointers to tech_in_tree.
    daDestroy(world -> techs_info, &destroyTechnologyCommonInfo);

    // Destroy world.
    destroyGraph(world -> graph_players, deleted, &destroyGraphNode);
    free(world);

    // Destroy auxiliary array.
    daDestroy(deleted, NULL);
}
