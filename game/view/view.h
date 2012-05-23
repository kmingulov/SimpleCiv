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

    ****************************************************************************

    Ncurses has «memory leaks». Read more at:
    http://invisible-island.net/ncurses/ncurses.faq.html#config_leaks

*/

#ifndef VIEW_H
#define VIEW_H

#include <curses.h>

#include "../../modules/graph/graph.h"
#include "../../modules/list/list.h"
#include "../../modules/map/map.h"
#include "../world/world.h"

#include "../../modules/widgets/curses_draws.h"
#include "../../modules/widgets/curses_chooser.h"
#include "../../modules/widgets/curses_textbox.h"

#include "definitions.h"

/*
    View struct, which contains general settings of view.
*/
typedef struct View
{
    // Number of rows and columns and distance between left edge of screen and
    // sidebar (in columns).
    int rows, columns, sidebar;

    // Cursor coordinates (in the ncurses).
    int cur_r, cur_c;
    // Cursor coordinates (in the world).
    int map_r, map_c;

    // Current cell.
    Node * current_cell;

    // Current chooser.
    Chooser * chooser;

    // Current textbox.
    Textbox * textbox;
} View;

/*
    Functions of initialization and deinitialization of View.
*/
View * createView(World * world);
void destroyView(View * view);

/*
    Focus on the (r, c) cell of the map.
*/
void focusOn(World * world, View * view, int r, int c);

/*
    Draws basic view (for map).
*/
void drawGeneralView(World * world, View * view);

/*
    Draws tech view.
*/
void drawTechView(World * world, View * view);

/*
    Draws city view.
*/
void drawCityView(World * world, View * view);

/*
    Draws player info.
*/
void drawPlayerInfo(World * world, View * view);

/*
    Draws cell info.
*/
void drawCellInfo(World * world, View * view);

/*
    Draws map.
*/
void drawMap(World * world, View * view);

/*
    Event handling. Returns 0 if game need to terminate, else 1.
*/
int viewProcess(World * world, View * view, List * list);

#endif
