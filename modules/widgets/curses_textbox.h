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

#ifndef CURSES_TEXTBOX_H
#define CURSES_TEXTBOX_H

#include "../dyn_array/dyn_array.h"
#include "../int_array/int_array.h"

typedef struct Textbox
{
    // Start point.
    int start_r, start_c;

    // Sizes.
    int r, c;

    // Page count.
    int pages_count;

    // Current page.
    int current_page;

    // Lines per page.
    int lines_per_page;

    // Array of char strings.
    DynArray * lines;

    // Array of line's properties: bold or not.
    IntArray * properties;
} Textbox;

/*
    Creates new textbox.
*/
Textbox * createTextbox(int start_r, int start_c, int r, int c);

/*
    Adds formatted string to textbox (bold or not).
*/
void addString(Textbox * tb, const char * format, ...);
void addBoldString(Textbox * tb, const char * format, ...);

/*
    Draws textbox.
*/
void drawTextbox(Textbox * tb);

/*
    Destroys textbox.
*/
void destroyTextbox(Textbox * textbox);

#endif
