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

#ifndef VIEW_TEXTBOX_H
#define VIEW_TEXTBOX_H

#include "../../modules/widgets/curses_textbox.h"
#include "../../modules/unit/unit.h"
#include "../../modules/unit/unit_common_info.h"

#include "../world/world.h"
#include "view.h"

/*
    Information adders for ViewTextbox.
*/
void addHelpInfoToTextbox(Textbox * tb);
void addUnitInfoToTextbox(Textbox * tb, World * world, View * view);
void addWinInfoToTextbox(Textbox * tb);

#endif
