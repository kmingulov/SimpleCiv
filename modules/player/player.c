#include <stdlib.h>

#include "player.h"

Player * createPlayer(char * name, IntArray * available_units, IntArray * available_techs)
{
    Player * player = malloc(sizeof(Player));

    player -> name = name;
    player -> gold = 100;
    player -> available_units = available_units;
    player -> available_techs = available_techs;

    player -> graph_map = NULL;
    player -> cities = listCreate();
    player -> units = listCreate();

    return player;
}

void destroyPlayer(Player * player)
{
    listDestroy(player -> cities, NULL);
    listDestroy(player -> units, NULL);
    iaDestroy(player -> available_units);
    iaDestroy(player -> available_techs);
    free(player -> name);
    free(player);
}
