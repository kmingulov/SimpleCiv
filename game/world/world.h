#ifndef MODEL
#define MODEL

#include "../../modules/dyn_array/dyn_array.h"
#include "../../modules/player/player.h"
#include "../../modules/graph/graph.h"
#include "definitions.h"
#include "world_properties.h"

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

    // Computer player.
    Player * computer;

    // Technology tree. Type of each node is struct Technology.
    Node * tech_tree;

    // Common info about technologies and units.
    DynArray * units_info; // Type — UnitCommonInfo.
    DynArray * techs_info; // Type — Node (in tech tree).
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
