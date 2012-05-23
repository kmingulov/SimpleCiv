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

#ifndef CURSES_CHOOSER_H
#define CURSES_CHOOSER_H

#include "../../game/world/world.h"

#include "../int_array/int_array.h"
#include "../city/city.h"

#include "curses_textbox.h"

/*
    Struct of view chooser (for some menus).
*/
typedef struct Chooser
{
    // Textbox with lines.
    Textbox * text;

    // Array of ids.
    IntArray * ids;

    // Current id.
    int current;

    // First row of the list with items.
    int start_r;
} Chooser;

/*
    Creates new chooser.
*/
Chooser * createChooser(int start_r, int start_c, int r, int c);

/*
    Adds non-choosable bold string.
    Return length of added strings.
*/

/*
    Functions of creation chooser.
*/
Chooser * createTechChooser(World * world);
Chooser * createUnitChooser(World * world, City * city);

/*
    Destroys chooser.
*/
void destroyChooser(Chooser * chooser);

#endif
