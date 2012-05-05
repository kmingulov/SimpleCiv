#ifndef PLAYERS
#define PLAYERS

#include "../graph/graph.h"
#include "../int_array/int_array.h"

typedef struct Player
{
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

/*
    Creates new player.
*/
Player * createPlayer(char * name, IntArray * available_units, IntArray * available_techs);

#endif
