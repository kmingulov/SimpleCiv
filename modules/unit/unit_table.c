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

#include "../../game/world/definitions.h"
#include "../technology/technology.h"
#include "unit_table.h"

IntArray * createUnitTable(IntArray * tech_table, DynArray * techs_info, DynArray * units_info)
{
    IntArray * result = iaLengthCreate(units_info -> length);

    updateUnitTable(result, tech_table, techs_info);

    return result;
}

void updateUnitTable(IntArray * unit_table, IntArray * tech_table, DynArray * techs_info)
{
    for(int i = 0; i < tech_table -> length; i++)
    {
        // If technology already researched, unit is available.
        if( iaGetByIndex(tech_table, i) == TECH_RESEARCHED )
        {
            IntArray * units = ((Technology *) ((Node *) daGetByIndex(techs_info, i)) -> data) -> provides_units;
            if(units != NULL)
            {
                // Marking all provided units as available.
                for(int j = 0; j < units -> length; j++)
                {
                    int id = iaGetByIndex(units, j);
                    iaSetByIndex(unit_table, id, UNIT_AVAILABLE);
                }
            }
        }
    }
}

int checkUnitForResources(UnitCommonInfo * u_info, Player * player)
{
    if(u_info -> resources == NULL)
    {
        return 0;
    }

    // Checking for each resource.
    for(int j = 0; j < u_info -> resources -> length; j++)
    {
        // Getting resource id.
        int id = iaGetByIndex(u_info -> resources, j);
        // Does player have this resources?
        if(iaGetByIndex(player -> resources, id) == 0)
        {
            // Sad but true.
            return 1;
        }
    }

    return 0;
}
