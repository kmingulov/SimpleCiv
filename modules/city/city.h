#ifndef CITY
#define CITY

#include "../../game/world/world.h"

#include "../player/player.h"

typedef struct City
{
    // Name of the city.
    char * name;

    // Owner of this city.
    Player * owner;
    unsigned int r, c;

    // Current population.
    unsigned int population;

    // Age.
    unsigned int age;
} City;

/*
    Creates a city in row r, column c. Player is owner of the city.
*/
City * createCity(World * world, char * name, unsigned int r, unsigned int c, Player * player);

/*
    Developes the city.
*/
void developCity(void * data);

#endif
