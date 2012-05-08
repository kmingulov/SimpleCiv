#include <stdlib.h>

#include "../../game/world/definitions.h"
#include "player.h"

Player * createPlayer(char * name, IntArray * available_units, IntArray * available_techs)
{
    Player * player = malloc(sizeof(Player));

    player -> name = name;
    player -> gold = 100;

    player -> available_units = available_units;
    player -> available_techs = available_techs;

    // +1, to avoid incomprehensible constructs with id -+ 1 (1..CELL_RES_COUNT
    // are resources really).
    player -> resources = iaLengthCreate(CELL_RES_COUNT + 1);

    player -> cur_r = 0;
    player -> cur_c = 0;

    player -> graph_map = NULL;
    player -> current_cell = NULL;

    player -> map_r = -1;
    player -> map_c = -1;

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
    iaDestroy(player -> resources);
    free(player -> name);
    free(player);
}
