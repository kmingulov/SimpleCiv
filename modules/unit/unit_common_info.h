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

#ifndef UNIT_COMMON_INFO_H
#define UNIT_COMMON_INFO_H

#include "../int_array/int_array.h"

/*
    This is struct of unit. It's really similar to technology struct (see
    modules/technology/technology.h file).
    This struct for units' info table (common for all players).
    Each player also will have table with technologies' id and value.
    Also there will be a common for all players table with these values: hp,
    damage, etc.
*/
typedef struct UnitCommonInfo
{
    // Unit's name.
    char * name;

    // Unit's char.
    char c;

    // Stats.
    unsigned int max_health;
    unsigned int max_damage;
    unsigned int max_moves;
    unsigned int hiring_turns;
    unsigned int gold_drop;

    // Privileges and required resources.
    IntArray * privileges;
    IntArray * resources;
} UnitCommonInfo;

/*
    Creates UnitCommonInfo.
*/
UnitCommonInfo * createUnitCommonInfo();

/*
    Destroys UnitCommonInfo variable.
*/
void destroyUnitCommonInfo(void * data);

#endif
