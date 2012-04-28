#ifndef DEFINITIONS
#define DEFINITIONS

/*
    Defines for nodes' types.
*/

// For map.
#define NODE_CELL          0

// For player.
#define NODE_PLAYER        1
#define NODE_CITIES_LIST   2
#define NODE_UNITS_LIST    3
#define NODE_TECH_TABLE    4

// For technologies.
#define NODE_TECHNOLOGY    5

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

#endif
