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

    // Cell (r,c) is a water :O
    if(((Cell *) getCell(world -> graph_map, r, c) -> data) -> territory == CELL_TYPE_WATER)
    {
        return NULL;
    }

    // Allocate some memory.
    City * city = malloc(sizeof(City));
    Node * node = createGraph(NODE_CITY, city);

    // Basics.
    city -> name = name;
    city -> population = rand() % 100 + 100;
    city -> age = 0;

    // Owner info.
    city -> owner = player;
    listPrepend(player -> cities, city);

    // Cell info.
    city -> r = r;
    city -> c = c;
    addEdge(getCell(world -> graph_map, r, c), node, EDGE_CELL_CITY);

    return city;
}

void developCity(City * city)
{
    // TODO Add resources dependence in formula.
    double n = (double) city -> population;

    // Random number.
    double r = (double) (rand() % 100 + 1) / 100;

    // Increase population.
    n += 20.0f * r / 3.14f / (1.0f + ((double) city -> age * city -> age) / 10000);
    city -> population = ceil(n);

    // Increase age.
    (city -> age)++;
}
