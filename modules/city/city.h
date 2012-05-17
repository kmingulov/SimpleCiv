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

#ifndef CITY
#define CITY

#include "../../game/world/world.h"
#include "../player/player.h"
#include "../unit/unit_hiring.h"

typedef struct City
{
    // Name of the city.
    char * name;

    // Owner of this city.
    Player * owner;
    int r, c;

    // Current population.
    unsigned int population;

    // Age.
    unsigned int age;

    // Resources count.
    unsigned char res_count;

    // Current hiring in the city.
    UnitHiring * hiring;
} City;

/*
    Creates a city in row r, column c. Player is owner of the city.
*/
City * createCity(World * world, char * name, int r, int c, Player * player);

/*
    Developes the city.
*/
void developCity(World * world, void * data);

/*
    Destroys city node's data.
*/
void destroyCityNodeData(unsigned char type, void * data);

#endif
