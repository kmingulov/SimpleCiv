#include <stdlib.h>
#include <math.h>

#include "../unit/unit_common_info.h"
#include "../unit/unit.h"
#include "../map/map.h"
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

    // Woohoo! Adding resources to player.
    IntArray * array = player -> resources;
    for(int i = 0; i < 9; i++)
    {
        Cell * c = getMapCell(world -> map, coord[i][0], coord[i][1]) -> data;
        unsigned char res = c -> resources;
        if(res != CELL_RES_NONE)
        {
            array -> data[res] += 1;
        }
    }

    // Allocate some memory.
    City * city = malloc(sizeof(City));
    Node * node = createGraph(NODE_CITY, city);

    // Basics.
    city -> name = name;
    city -> population = rand() % 100 + 100;
    city -> age = 0;
    city -> hiring = createHiring();

    // Owner info.
    city -> owner = player;
    listPrepend(player -> cities, city);

    // Cell info.
    city -> r = r;
    city -> c = c;
    addEdge(getMapCell(world -> map, r, c), node, EDGE_CELL_CITY);

    return city;
}

void developCity(World * world, void * data)
{
    City * city = (City *) data;

    // TODO Add resources dependence in formula.
    float n = (float) city -> population;

    // Random number.
    float r = (float) (rand() % 100 + 1) / 100;

    // Increase population.
    n += 40.0f * r / 3.14f / (1.0f + ((float) city -> age * city -> age) / 10000);
    city -> population = ceil(n);

    // Increase age.
    (city -> age)++;

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
            player -> gold -= city -> hiring -> delta;
            city -> hiring -> turns += 1;
            if(city -> hiring -> turns == u_info -> hiring_turns)
            {
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
    free(city -> hiring);

    free(data);
}
