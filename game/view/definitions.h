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

#ifndef VIEW_DEFINITIONS_H
#define VIEW_DEFINITIONS_H

/*
    True false definitions.
*/
#ifndef true
    #define true                        1
#endif

#ifndef false
    #define false                       0
#endif

/*
    Key definitions.
*/
#ifdef WIN32
    #define KEY_ENTER_FIXED             (int) '\r'
#else
    #define KEY_ENTER_FIXED             (int) '\n'
#endif

#define KEY_SPACE                       32

/*
    Definition for init_pair() function.
*/
#define PLAYER_COLOURS_START            30

/*
    View process definitions.
*/
#define VIEW_REDRAW_ALL                 0
#define VIEW_REDRAW_INFO                1
#define VIEW_REDRAW_MAP                 2
#define VIEW_REDRAW_TECH_DIALOG         4
#define VIEW_REDRAW_CITY_DIALOG         5
#define VIEW_REDRAW_TEXTBOX             6

#define VIEW_MOVE_CURSOR_RIGHT          7
#define VIEW_MOVE_CURSOR_LEFT           8
#define VIEW_MOVE_CURSOR_TOP            9
#define VIEW_MOVE_CURSOR_BOTTOM         10

#define VIEW_CHOOSER_MOVE_CURSOR_TOP    11
#define VIEW_CHOOSER_MOVE_CURSOR_BOTTOM 12

#define VIEW_ESCAPE                     13

/*
    Interface definitions.
*/
#define SIDEBAR_PLAYER_BLOCK            0
#define SIDEBAR_CELL_BLOCK              9

#endif
