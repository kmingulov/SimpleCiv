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
#include <math.h>

#include "../unit/unit_common_info.h"
#include "../unit/unit.h"
#include "../map/map.h"
#include "../fog/fog.h"
#include "city.h"

City * createCity(World * world, char * name, int r, int c, Player * player)
{
    // Cell (r,c) already have a city.
    if(getNeighbour( getMapCell(world -> map, r, c), EDGE_CELL_CITY ) != NULL)
    {
        return NULL;
    }

    // Checking that there is one non-water cell.
    int coord[][2] = {{r + 1, c}, {r - 1, c}, {r, c - 1}, {r, c + 1},
        {r + 1, c + 1}, {r - 1, c + 1}, {r + 1, c - 1}, {r - 1, c - 1}, {r, c}};
    int found = 0;
    for(int i = 0; i < 8; i++)
    {
        Cell * c = getMapCell(world -> map, coord[i][0], coord[i][1]) -> data;
        if(c -> territory != CELL_TYPE_WATER)
        {
            found = 1;
            break;
        }
    }
    if(found == 0 || ((Cell *) getMapCell(world -> map, r, c) -> data) -> territory == CELL_TYPE_WATER)
    {
        return 0;
    }

    // Allocate some memory.
    City * city = malloc(sizeof(City));
    Node * node = createGraph(NODE_CITY, city);

    // Add resources to player and increment value of city -> res_count.
    IntArray * array = player -> resources;
    city -> res_count = 0;
    for(int i = 0; i < 9; i++)
    {
        Cell * c = getMapCell(world -> map, coord[i][0], coord[i][1]) -> data;
        unsigned char res = c -> resources;
        if(res != CELL_RES_NONE)
        {
            array -> data[res] += 1;
            city -> res_count += 1;
        }
    }

    // Basics.
    city -> name = name;
    // Sets population from interval (min, max).
    city -> population = rand() % (BALANCE_CITY_POPUL_MAX - BALANCE_CITY_POPUL_MIN) + BALANCE_CITY_POPUL_MIN;
    city -> age = 0;
    city -> hiring = createHiring();

    // Owner info.
    city -> owner = player;
    listPrepend(player -> cities, city);

    // Cell info.
    city -> r = r;
    city -> c = c;
    addEdge(getMapCell(world -> map, r, c), node, EDGE_CELL_CITY);

    // Update fog.
    revealFogRadius(player -> fog, r, c, BALANCE_CITY_VIEW_RADIUS);

    return city;
}

void developCity(World * world, void * data)
{
    City * city = (City *) data;

    // Get population.
    float n = (float) city -> population;

    // Random number.
    float r = (float) (rand() % 100 + 1) / 100;

    // Increase population.
    n += 40.0f * sqrt(city -> res_count + 1) * r / 3.14f / (1.0f + ((float) city -> age * city -> age) / 10000);
    city -> population = ceil(n);

    // Increase age.
    city -> age += 1;

    // Increase owner's money.
    Player * player = city -> owner;
    player -> gold += ceil((float) 10.0f * exp(log((float) n / 100000.0f) / 7.0f) );

    // Process hiring. (Player must have enough money.)
    if(city -> hiring -> id != -1 && player -> gold >= city -> hiring -> delta)
    {
        // There is other units?
        Node * n = getMapCell(world -> map, city -> r, city -> c);
        n = getNeighbour(n, EDGE_CELL_UNIT);
        // Getting unit info.
        UnitCommonInfo * u_info = (UnitCommonInfo *) daGetByIndex(world -> units_info, city -> hiring -> id);
        // We cannot process, if there is another unit and on this turn unit
        // must appear. Note: written so for one reason — it's more clear so.
        if(n != NULL && city -> hiring -> turns == u_info -> hiring_turns - 1)
        {
            // nothing
        }
        else
        {
            // Continue hiring.
            player -> gold -= city -> hiring -> delta;
            city -> hiring -> turns += 1;
            // It's final turn in hiring.
            if(city -> hiring -> turns == u_info -> hiring_turns)
            {
                // Create unit and delete all data about previous hiring.
                createUnit(world, city -> r, city -> c, city -> hiring -> id, city -> owner);
                city -> hiring -> id = -1;
                city -> hiring -> turns = 0;
                city -> hiring -> delta = 0;
            }
        }
    }
}

void destroyCityNodeData(unsigned char type, void * data)
{
    City * city = (City *) data;

    free(city -> name);
    destroyHiring(city -> hiring);

    free(data);
}
