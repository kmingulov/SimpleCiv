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

#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include "../graph/graph.h"
#include "../map/map.h"

/*
    Recursive algorithm to generate random landscape.
        c — point, from where we begin create landscape.
        k — magic coef, that means how many cells we will fill.
        required — value, what we need to fill this cell.
        fill — value, with that we will fill this cell.
*/
void generateLandscape(Node * c, long long k, char required, char fill);

/*
    Function generate random landscape and put it in "map".
    Uses generateLandscape function.
*/
void generateMap(Map * map);

#endif
