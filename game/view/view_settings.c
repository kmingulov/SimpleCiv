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

#include "view_settings.h"

void initPlayerSettings(World * world, View * view, Player * player)
{
    // Get player's city.
    City * city = (City *) listGetHead(player -> cities);

    // Focus on this city.
    player -> cur_r = view -> rows / 2;
    player -> cur_c = view -> sidebar / 2;
    player -> map_r = city -> r;
    player -> map_c = city -> c;
    player -> current_cell = getMapCell(world -> map, city -> r, city -> c);
    player -> graph_map = getCell(player -> current_cell, 1 - player -> cur_r, 1 - player -> cur_c);
}

void loadPlayerSettings(View * view, Player * player)
{
    // Load player's settings.
    view -> cur_r = player -> cur_r;
    view -> cur_c = player -> cur_c;
    view -> map_r = player -> map_r;
    view -> map_c = player -> map_c;
    view -> current_cell = player -> current_cell;
}
