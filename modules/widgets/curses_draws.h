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

#ifndef CURSES_DRAWS_H
#define CURSES_DRAWS_H

/*
    Clears block from (start_r, start_c) to (start_r + r, start_c + c) point.
*/
void clearBlock(int start_r, int start_c, int r, int c);

/*
    Draws box (start_r, start_c) to (start_r + r, start_c + c) point.
*/
void drawBox(int start_r, int start_c, int r, int c);

/*
    Draws vertical line from (start_r, c) to (start_r + r, c) point
*/
void drawVertLine(int start_r, int r, int c);

/*
    Draws horizontal line from (r, start_c) to (r, start_c + c) point
*/
void drawHorizLine(int start_r, int r, int c);

/*
    Put char string into the middle/right/left of row. Syntax is similar to
    printf function.
*/
void putInMiddle(int start_r, int start_c, int length, const char * format, ...);
void putInRight(int start_r, int start_c, int length, const char * format, ...);
void putInLeft(int start_r, int start_c, int length, const char * format, ...);

#endif
