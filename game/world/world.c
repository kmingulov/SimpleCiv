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

    // Parse config.xml.
    world -> properties = parseXML(XML_CONFIG);
    if(!noErrorsInWorldProperties(log, world -> properties))
    {
        return NULL;
    }

    // Parse units.xml.
    world -> units_info = parseXML(XML_UNITS);
    if(!noErrorsInUnitsInfo(log, world -> units_info))
    {
        return NULL;
    }

    // Parse technologies.xml.
    DynArray * techs_data = parseXML(XML_TECHNOLOGIES);
    if(!noErrorsInTechsData(log, techs_data))
    {
        return NULL;
    }

    // Create edges in technology tree (we already have nodes).
    world -> tech_tree = createEdgesInTechnologyTree(techs_data);

    // Create techs_info table.
    world -> techs_info = daCreate();
    for(int i = 0; i < techs_data -> length; i++)
    {
        TechnologyParseInfo * t = (TechnologyParseInfo *) daGetByIndex(techs_data, i);
        daPrepend(world -> techs_info, t -> tech_in_tree);
    }

    // Create tech tables.
    IntArray * tech_table = createTechnologyTable(world -> techs_info);

    // Create unit tables.
    IntArray * unit_table = createUnitTable(tech_table, world -> techs_info, world -> units_info);

    // Free techs_data.
    daDestroy(techs_data, &destroyTechnologyParseInfo);

    // Create map and landscape.
    world -> map = createMap(world -> properties -> map_r, world -> properties -> map_c);
    generateMap(world -> map);

    // Create players list.
    world -> players = listCreate();
    for(int i = 0; i < world -> properties -> players_count; i++)
    {
        // Create new player.
        char * name = (char *) daGetByIndex(world -> properties -> player_names, i);
        char * city_name = (char *) daGetByIndex(world -> properties -> player_cities, i);
        Player * player = createPlayer(name, iaCopy(unit_table), iaCopy(tech_table));
        // Add player's colour.
        player -> colour = i % PLAYER_COLOURS_COUNT;
        // Add player's fog.
        player -> fog = createFog(world -> map -> max_r, world -> map -> max_c);
        // Create default city. createCity() function returns NULL, if nothing
        // created. Trying create city!
        City * city = NULL;
        while(city == NULL)
        {
            city = createCity(world, city_name, rand() % world -> properties -> map_r, rand() % world -> properties -> map_c, player);
        }
        // Create start unit (lumberjack).
        createUnit(world, city -> r, city -> c, 14, player);
        // Set his map head.
        player -> graph_map = world -> map -> head;
        // Add him to list.
        listPrepend(world -> players, player);
    }

    // Add computer player.
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
    listPrepend(world -> players, player);
    world -> computer = player;

    // Destroy additional data.
    iaDestroy(unit_table);
    iaDestroy(tech_table);

    // Return world.
    return world;
}

void destroyWorld(World * world)
{
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

    // Destroy players list.
    listDestroy(world -> players, &destroyPlayer);

    // Destroy world.
    free(world);
}
