#ifndef MODEL
#define MODEL

#include "definitions.h"
#include "../../modules/dyn_array/dyn_array.h"
#include "../../modules/int_array/int_array.h"

#include "../../modules/graph/graph.h"
#include "../../modules/cell/cell.h"

/*
    Struct of world properties.
*/
typedef struct WorldProperties
{
    // Count of rows and columns in map.
    int map_r, map_c;

    // Players' count.
    int players_count;

    // And their names and city's names.
    DynArray * player_names;
    DynArray * player_cities;
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

#endif
