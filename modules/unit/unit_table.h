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

#ifndef UNIT_TABLE_H
#define UNIT_TABLE_H

#include "../int_array/int_array.h"
#include "../dyn_array/dyn_array.h"
#include "../player/player.h"

#include "unit_common_info.h"

/*
    Creates unit table.
*/
IntArray * createUnitTable(IntArray * tech_table, DynArray * techs_info, DynArray * units_info);

/*
    Updates unit table.
*/
void updateUnitTable(IntArray * unit_table, IntArray * tech_table, DynArray * techs_info);

/*
    Checkes available this unit or no.
    Looks for player's resources (function updateUnitTable() doesn't do this).
    Returns 0 if available, 1 if no.
*/
int checkUnitForResources(UnitCommonInfo * u_info, Player * player);

#endif
