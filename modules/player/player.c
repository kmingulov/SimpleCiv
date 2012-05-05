#include <stdlib.h>

#include "player.h"

Player * createPlayer(char * name, IntArray * available_units, IntArray * available_techs)
{
    Player * player = malloc(sizeof(Player));

    player -> name = name;
    player -> available_units = available_units;
    player -> available_techs = available_techs;

    // player -> graph_map = ?
    // player -> cities = ?
    // player -> units = ?

    return player;
}
