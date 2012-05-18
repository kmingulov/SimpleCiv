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

#include <stdlib.h>

#include "unit_common_info.h"

UnitCommonInfo * createUnitCommonInfo()
{
    UnitCommonInfo * unit = malloc(sizeof(UnitCommonInfo));

    unit -> name = NULL;
    unit -> max_health = 0;
    unit -> max_damage = 0;
    unit -> max_moves = 0;
    unit -> hiring_turns = 0;
    unit -> gold_drop = 0;
    unit -> privileges = NULL;
    unit -> resources = NULL;

    return unit;
}

void destroyUnitCommonInfo(void * data)
{
    UnitCommonInfo * unit = (UnitCommonInfo *) data;

    free(unit -> name);

    if(unit -> privileges != NULL)
    {
        iaDestroy(unit -> privileges);
    }

    if(unit -> resources != NULL)
    {
        iaDestroy(unit -> resources);
    }

    free(unit);
}
