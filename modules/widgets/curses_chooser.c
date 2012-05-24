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

#include "../player/player.h"
#include "../technology/technology.h"
#include "../technology/technology_table.h"
#include "../unit/unit_common_info.h"
#include "../unit/unit_table.h"

#include "curses_chooser.h"

Chooser * createTechChooser(World * world)
{
    Chooser * chooser = malloc(sizeof(Chooser));

    // Initiale values.
    chooser -> ids = iaCreate();
    chooser -> current = -1;
    chooser -> start_r = -1;

    // Get player.
    Player * player = (Player *) listGetHead(world -> players);

    // Add techs to chooser, during this calc count of them.
    int count = 0;
    for(int i = 0; i < player -> available_techs -> length; i++)
    {
        int value = iaGetByIndex(player -> available_techs, i);
        // Tech is available.
        if(value == TECH_AVAILABLE)
        {
            Technology * tech = (Technology *) ((Node *) daGetByIndex(world -> techs_info, i)) -> data;
            // Add to array, if player have enough resources.
            if(checkTechForResources(tech, player) == 0)
            {
                iaPrepend(chooser -> ids, tech -> id);
            }

            // It is current research?
            if(tech -> id == player -> research -> id)
            {
                chooser -> current = count - 1;
            }
        }
    }

    return chooser;
}

Chooser * createUnitChooser(World * world, City * city)
{
    Chooser * chooser = malloc(sizeof(Chooser));

    // Initiale values.
    chooser -> ids = iaCreate();
    chooser -> current = -1;
    chooser -> start_r = -1;

    // Get player.
    Player * player = (Player *) listGetHead(world -> players);

    // Add units to chooser, during this calc count of them.
    int count = 0;
    for(int i = 0; i < player -> available_units -> length; i++)
    {
        int value = iaGetByIndex(player -> available_units, i);
        // Unit is available.
        if(value == UNIT_AVAILABLE)
        {
            UnitCommonInfo * u_info = daGetByIndex(world -> units_info, i);
            // Add to array, if player have enough resources.
            if(checkUnitForResources(u_info, player) == 0)
            {
                iaPrepend(chooser -> ids, i);
            }
            
            // It is current hiring?
            if(i == city -> hiring -> id)
            {
                chooser -> current = count;
            }
        }
    }

    return chooser;
}

void destroyChooser(Chooser * chooser)
{
    iaDestroy(chooser -> ids);
    free(chooser);
}
