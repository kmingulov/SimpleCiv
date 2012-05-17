#ifndef WORLD_DEFINITIONS
#define WORLD_DEFINITIONS

/*
    ADMIN MODE.
*/
#define ADMIN_MODE            0

/*
    BALANCE DEFINES.
*/
// Unit's resource cost.
#define BALANCE_UNIT_RES_COST       1

// Gain from chopping trees.
#define BALANCE_CHOPPING_GAIN       5

// Mine building's cost.
#define BALANCE_MINE_COST           5

// Gain (in resources) from mine building.
#define BALANCE_MINE_GAIN           1

// First city's population bounds.
#define BALANCE_CITY_POPUL_MIN      180
#define BALANCE_CITY_POPUL_MAX      200

/*
    Definition for players colours.
*/
#define PLAYER_COLOURS_COUNT 5

/*
    Defines for nodes' types.
*/

// For map.
#define NODE_CELL          0

// For player.
#define NODE_PLAYER        1
#define NODE_UNIT          2
#define NODE_CITY          3

// For technologies.
#define NODE_TECHNOLOGY    4

/*
    Defines for edges' types.
*/

// For map.
#define EDGE_CELL_CITY     0
#define EDGE_CELL_UNIT     1
#define EDGE_CELL_RIGHT    2
#define EDGE_CELL_LEFT     3
#define EDGE_CELL_TOP      4
#define EDGE_CELL_BOTTOM   5
#define EDGE_CELL_WORMHOLE 6

// For players.
#define EDGE_NEXT_PLAYER   7

// For technologies.
#define EDGE_TECH_PROVIDES 8
#define EDGE_TECH_REQUIRES 9

/*
    Defines for technologies' array.
*/
#define TECH_NOT_AVAILABLE 0
#define TECH_AVAILABLE     1
#define TECH_RESEARCHED    2

/*
    Defines for units' array.
*/
#define UNIT_NOT_AVAILABLE 0
#define UNIT_AVAILABLE     1

/*
    Defines for cell's types.
*/
#define CELL_TYPE_WATER    1
#define CELL_TYPE_GRASS    2
#define CELL_TYPE_TREE     3
#define CELL_TYPE_HILL     4
#define CELL_TYPE_MOUNTAIN 5

/*
    Defines for resources.
*/
#define CELL_RES_COUNT     6
#define CELL_RES_NONE      0
#define CELL_RES_BRONZE    1
#define CELL_RES_IRON      2
#define CELL_RES_COAL      3
#define CELL_RES_GUNPOWDER 4
#define CELL_RES_HORSES    5
#define CELL_RES_MUSHROOMS 6

#define CELL_NO_MINE       0
#define CELL_MINE          1

/*
    Units priviligies.
*/
#define UNIT_PRVL_COUNT      4
#define UNIT_PRVL_NONE       0
#define UNIT_PRVL_BUILD_CITY 1
#define UNIT_PRVL_BUILD_MINE 2
#define UNIT_PRVL_CAN_FLOAT  3
#define UNIT_PRVL_CHOP_TREES 4

#endif
