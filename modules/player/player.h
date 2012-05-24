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

#ifndef PLAYER_H
#define PLAYER_H

#include "../../game/world/world.h"

#include "../list/list.h"
#include "../technology/technology_research.h"
#include "../graph/graph.h"
#include "../int_array/int_array.h"
#include "../fog/fog.h"

typedef struct Player
{
    // Name and color of player, used only for gamer's convenience.
    char * name;
    unsigned char colour;

    // Gold.
    int gold;

    // Head of map, which player see.
    Node * graph_map;
    Node * current_cell;

    // Cursor coordinates (in the ncurses).
    int cur_r, cur_c;

    // Cursor coordinates (in the world).
    int map_r, map_c;

    // Lists of player's units (type: Unit, not UnitCommonInfo!) and cities.
    List * units;
    List * cities;

    // Arrays of available units and technologies.
    IntArray * available_units;
    IntArray * available_techs;

    // Current player's researching.
    TechnologyResearch * research;

    // Array of player's resources.
    IntArray * resources;

    FogOfWar * fog;
} Player;

/*
    Creates new player.
*/
Player * createPlayer(World * world, int id, IntArray * available_units, IntArray * available_techs);

/*
    Destroys player.
*/
void destroyPlayer(void * data);

#endif
