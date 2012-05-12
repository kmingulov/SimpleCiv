#include <math.h>
#include <stdlib.h>

#include "city.h"

City * createCity(World * world, char * name, unsigned int r, unsigned int c, Player * player)
{
    // Cell (r,c) already have a city.
    if(getNeighbour( getCell(world -> graph_map, r, c), EDGE_CELL_CITY ) != NULL)
    {
        return NULL;
    }

    // Checking that cells are not water.
    int coord[][2] = {{r, c}, {r + 1, c}, {r - 1, c}, {r, c - 1}, {r, c + 1},
        {r + 1, c + 1}, {r - 1, c + 1}, {r + 1, c - 1}, {r - 1, c - 1}};
    for(int i = 0; i < 9; i++)
    {
        Cell * c = getCell(world -> graph_map, coord[i][0], coord[i][1]) -> data;
        if(c -> territory == CELL_TYPE_WATER)
        {
            return NULL;
        }
    }

    // Woohoo! Adding resources to player.
    IntArray * array = player -> resources;
    for(int i = 0; i < 9; i++)
    {
        Cell * c = getCell(world -> graph_map, coord[i][0], coord[i][1]) -> data;
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
    addEdge(getCell(world -> graph_map, r, c), node, EDGE_CELL_CITY);

    return city;
}

void developCity(void * data)
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
    player -> gold += ceil((float) 20.0f * exp(log((float) n / 100000.0f) / 7.0f) );
}
