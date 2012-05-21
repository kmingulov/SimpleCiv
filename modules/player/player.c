/*

    SimpleCiv is simple clone of Civilization game, using ncurses library.
    Copyright (C) 2012 by K. Mingulov, A. Sapronov.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include <stdlib.h>
#include <string.h>

#include "../../game/world/definitions.h"
#include "../city/city.h"
#include "../unit/unit.h"
#include "../fog/fog.h"
#include "player.h"

Player * createPlayer(World * world, int id, IntArray * available_units, IntArray * available_techs)
{
    Player * player = malloc(sizeof(Player));

    // Basic.
    player -> name = (char *) daGetByIndex(world -> properties -> player_names, id);
    player -> colour = id % PLAYER_COLOURS_COUNT;
    player -> is_computer = 0;

    if(TEST_MODE)
    {
        player -> gold = 9000;
    }
    else
    {
        player -> gold = 0;
    }

    // Units and techs.
    player -> available_units = available_units;
    player -> available_techs = available_techs;
    player -> research = createResearch();

    // +1, to avoid incomprehensible constructs with id -+ 1 (1..CELL_RES_COUNT
    // are resources really, 0 is CELL_RES_NONE).
    player -> resources = iaLengthCreate(CELL_RES_COUNT + 1);

    // Cursor and map coordinates.
    player -> cur_r = 0;
    player -> cur_c = 0;
    player -> graph_map = world -> map -> head;
    player -> current_cell = NULL;
    player -> map_r = -1;
    player -> map_c = -1;

    // Create fog.
    player -> fog = createFog(world -> map -> max_r, world -> map -> max_c);

    // Units and cities lists.
    player -> cities = listCreate();
    player -> units = listCreate();

    // Create default city. createCity() function returns NULL, if nothing
    // created. Trying create city!
    char * city_name = (char *) daGetByIndex(world -> properties -> player_cities, id);
    City * city = NULL;
    while(city == NULL)
    {
        city = createCity(world, city_name, rand() % world -> properties -> map_r, rand() % world -> properties -> map_c, player);
    }

    // Create start unit (lumberjack).
    createUnit(world, city -> r, city -> c, 14, player);

    return player;
}

Player * createComputerPlayer(World * world)
{
    Player * player = malloc(sizeof(Player));

    // Basic.
    char * name = malloc(sizeof(char) * 8);
    player -> name = strcpy(name, "Neutral");
    player -> is_computer = 1;
    player -> colour = 5;

    // Units and cities lists.
    player -> cities = listCreate();
    player -> units = listCreate();

    // Generating units.
    int r, c, counter = 0;
    while(counter < 2 * world -> properties -> players_count)
    {
        r = rand() % world -> properties -> map_r;
        c = rand() % world -> properties -> map_c;
        Cell * cell = (Cell *) getMapCell(world -> map, r, c) -> data;
        if(cell -> territory != CELL_TYPE_WATER)
        {
            // Creating caravans.
            createUnit(world, r, c, 13, player);
            counter++;
        }
    }

    // Nulling everything else.
    player -> gold = 0;
    player -> graph_map = NULL;
    player -> current_cell = NULL;
    player -> cur_r = 0;
    player -> cur_c = 0;
    player -> map_r = 0;
    player -> map_c = 0;
    player -> available_units = NULL;
    player -> available_techs = NULL;
    player -> research = NULL;
    player -> resources = NULL;
    player -> fog = NULL;

    return player;
}

void destroyPlayer(void * data)
{
    Player * player = (Player *) data;

    listDestroy(player -> cities, NULL);
    listDestroy(player -> units, NULL);

    if(player -> available_units != NULL)
    {
        iaDestroy(player -> available_units);
    }

    if(player -> available_units != NULL)
    {
        iaDestroy(player -> available_techs);
    }

    destroyResearch(player -> research);

    if(player -> fog != NULL)
    {
        destroyFog(player -> fog);
    }

    if(player -> resources != NULL)
    {
        iaDestroy(player -> resources);
    }

    free(player -> name);
    free(player);
}
