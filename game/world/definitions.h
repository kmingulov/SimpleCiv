#ifndef GRAPH_DEFINITIONS
#define GRAPH_DEFINITIONS

/*
    Defines for nodes' types.
*/

// For map.
#define NODE_CELL          1

// For player.
#define NODE_PLAYER        2
#define NODE_CITIES_LIST   3
#define NODE_UNITS_LIST    4
#define NODE_TECH_TABLE    5

// For technologies.
#define NODE_TECHNOLOGY    6

/*
    Defines for edges' types.
*/

// For map.
#define EDGE_CELL_CITY     1
#define EDGE_CELL_UNIT     2
#define EDGE_CELL_RIGHT    3
#define EDGE_CELL_LEFT     4
#define EDGE_CELL_TOP      5
#define EDGE_CELL_BOTTOM   6

// For players.
#define EDGE_NEXT_PLAYER   7

// For technologies.
#define EDGE_TECH_PROVIDES 8
#define EDGE_TECH_REQUIRES 9

#endif
