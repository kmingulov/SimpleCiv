#ifndef MODEL
#define MODEL

#include <stdio.h>
#include <stdlib.h>

#include "definitions.h"
#include "../../modules/dyn_array/dyn_array.h"
#include "../../modules/int_array/int_array.h"

#include "../../modules/graph/graph.h"
#include "../../modules/cell/cell.h"

#include "../../modules/unit/unit.h"
#include "../../modules/technology/technology.h"

#include "../../modules/player/player.h"

/*
    Struct of world properties.
*/
typedef struct WorldProperties
{
    // Count of rows and columns in map.
    int map_r, map_c;

    // Players' count.
    int players_count;

    // And their names.
    DynArray * player_names;
} WorldProperties;

/*
    Struct of world.
*/
typedef struct World
{
    // Properties.
    WorldProperties * properties;

    // Game graph.
    Node * graph_players; // Players.
    Node * graph_map;     // Map.

    // Technology tree. Type of each node is struct Technology.
    Node * tech_tree;

    // Common info about technologies and units.
    DynArray * units_info; // Type — UnitCommonInfo.
    DynArray * techs_info; // Type — TechnologyCommonInfo.
} World;

/*
    Creates world.
*/
World * createWorld();

/*
    Destroys world.
*/
void destroyWorld(World * world);

/*
    Save world to xml files.
    TODO This is _just_ draft. In future this function will receive char * name,
    save world to several xml files and add them to tar.gz (or any other)
    archive. So variable FILE * map_file is temporary.
*/
void saveWorld(World * world, WorldProperties * properties, FILE * map_file);

#endif
