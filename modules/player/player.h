#ifndef PLAYERS
#define PLAYERS

#include "../graph/graph.h"

typedef struct Player
{
    // _Unique_ number of this player. Probably, it will be used for game saves.
    int id;

    // Name of player, used only for gamer's convenience.
    char * name;

    // Head of map, which player see.
    Node * graph_map;

    // Array of player's units (type: Unit, not UnitCommonInfo!) and cities.
    //List * units;
    //List * cities;

    // Arrays of available units and technologies.
    IntArray * available_units;
    IntArray * available_techs;
} Player;

#endif
