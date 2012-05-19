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

#ifndef __VIEW_FOG_H
#define __VIEW_FOG_H

#include "../int_array/int_array.h"
#include "../dyn_array/dyn_array.h"

/*
    Struct of fog.
*/
typedef struct FogOfWar
{
    // Array of pointers to rows. Each row = IntArray with column elements.
    DynArray * rows;
} FogOfWar;

/*
    Creates fog of war.
*/
FogOfWar * createFog(int r, int c);

/*
    Destroys fog of war.
*/
void destroyFog(FogOfWar * fog);

/*
    Updates _one_ cell.
*/
void updateFogCell(FogOfWar * fog, int r, int c);

/*
    Updates area around cell (center_r, center_c).
*/
void updateFogArea(FogOfWar * fog, int center_r, int center_c);

/*
    Do player know this cell or not?
*/
int isKnownCell(FogOfWar * fog, int r, int c);

#endif
