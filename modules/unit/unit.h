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

#ifndef UNIT_H
#define UNIT_H

#include "../../game/world/world.h"

#include "../int_array/int_array.h"
#include "../dyn_array/dyn_array.h"
#include "../player/player.h"

/*
    This is struct of real unit, who live in our world.
*/
typedef struct Unit
{
    unsigned char unit_id;   // Unit id in units' info table.
    Player * owner;          // Owner of this unit.
    int r, c;                // X and Y coordinates.
    unsigned int health;     // Current health.
    unsigned int moves;      // Available moves.
} Unit;

/*
    Creates new unit in world in row r, column c. Id of unit is unit_id and
    owner is player.
*/
Unit * createUnit(World * world, unsigned int r, unsigned int c, unsigned char unit_id, Player * player);

/*
    Destroys unit's node's data.
*/
void destroyUnitNodeData(unsigned char type, void * data);

/*
    Destroys unit.
*/
void destroyUnit(World * world, Unit * unit);

/*
    Figth between two units.
*/
void unitsFight(World * world, Unit ** unit1, Unit ** unit2);

/*
    Developes units at the end of a course.
*/
void developUnit(void * data, DynArray * info);

void unitMotion(World * world, Node * current_cell, Node * destination, int direction, Unit * unit, Edge * edge);

/*
    Moves unit. Returns 0 if moved succefully, 1 if there was a fight, 2 if
    player win the game, 3 if failed.
*/
int moveUnit(World * world, Node * current_cell, int direction);

#endif
