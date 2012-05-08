#ifndef PLAYERS
#define PLAYERS

#include "../list/list.h"
#include "../graph/graph.h"
#include "../int_array/int_array.h"

typedef struct Player
{
    // Name of player, used only for gamer's convenience.
    char * name;

    // Gold.
    int gold;

    // Head of map, which player see.
    Node * graph_map;
    Node * current_cell;
    // Cursor coordinates (in the ncurses).
    int cur_r, cur_c;
    // Cursor coordinates (in the world).
    int map_r, map_c;

    // Lists of player's units (type: Unit, not UnitCommonInfo!) and cities.
    List * units;
    List * cities;

    // Arrays of available units and technologies.
    IntArray * available_units;
    IntArray * available_techs;

    // Array of player's resources.
    IntArray * resources;
} Player;

/*
    Creates new player.
*/
Player * createPlayer(char * name, IntArray * available_units, IntArray * available_techs);

/*
    Destroys player.
*/
void destroyPlayer(Player * player);

#endif
