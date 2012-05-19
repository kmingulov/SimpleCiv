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

#ifndef WORLD_PROPERTIES_H
#define WORLD_PROPERTIES_H

#include "../../modules/dyn_array/dyn_array.h"

/*
    Struct of world properties.
*/
typedef struct WorldProperties
{
    // Count of rows and columns in map.
    int map_r, map_c;

    // Players' count.
    int players_count;

    // And their names and default city's names.
    DynArray * player_names;
    DynArray * player_cities;
} WorldProperties;

#endif
