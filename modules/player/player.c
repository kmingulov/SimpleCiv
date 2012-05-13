#include <stdlib.h>

#include "../../game/world/definitions.h"
#include "player.h"

Player * createPlayer(char * name, IntArray * available_units, IntArray * available_techs)
{
    Player * player = malloc(sizeof(Player));

    player -> name = name;
    player -> colour = 0;
    player -> gold = 0;

    player -> available_units = available_units;
    player -> available_techs = available_techs;

    player -> research = createResearch();

    // +1, to avoid incomprehensible constructs with id -+ 1 (1..CELL_RES_COUNT
    // are resources really, 0 is CELL_RES_NONE).
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

    destroyResearch(player -> research);

    iaDestroy(player -> resources);

    free(player -> name);
    free(player);
}
