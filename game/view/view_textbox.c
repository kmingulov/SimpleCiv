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

#include "view_textbox.h"

/*
    Some consts for drawing.
*/
const char VIEW_RES_NAMES[][16] = {"Bronze", "Iron", "Coal", "Gunpowder",
    "Horses", "Mushrooms"};

const int VIEW_RES_VALUES[] = {CELL_RES_BRONZE, CELL_RES_IRON, CELL_RES_COAL,
    CELL_RES_GUNPOWDER, CELL_RES_HORSES, CELL_RES_MUSHROOMS};

const char VIEW_PRVL_NAMES[][16] = {"Building city", "Building mine",
    "Can float", "Choping trees"};

const int VIEW_PRVL_VALUES[] = {UNIT_PRVL_BUILD_CITY, UNIT_PRVL_BUILD_MINE,
    UNIT_PRVL_CAN_FLOAT, UNIT_PRVL_CHOP_TREES};

void addHelpInfoToTextbox(Textbox * tb)
{
    addBoldString(tb, "Help");
    addString(tb, "Use up/down arrow keys to scroll this text.");
    addString(tb, "Press q to hide this help.");
    addString(tb, "");

    // Map window.
    addBoldString(tb, "Map:");
    addString(tb, "Arrow keys       Move unit/cursor.");
    addString(tb, "Enter            End turn.");
    addString(tb, "Space            Choose unit to move or open city hiring dialog.");
    addString(tb, "c                Create city (if settler is selected).");
    addString(tb, "b                Cut the forest (if lumberjack is selected).");
    addString(tb, "m                Build a mine (if miner is selected).");
    addString(tb, "t                Open research dialog.");
    addString(tb, "h                Show this help.");
    addString(tb, "i                Show unit information.");
    addString(tb, "n                Show next unit (if selected) or next city.");
    addString(tb, "q                Quit game.");
    addString(tb, "");

    // Hiring dialog.
    addBoldString(tb, "Hiring dialog:");
    addString(tb, "Up/down keys     Choose unit.");
    addString(tb, "Enter            Start hiring (will terminate current hiring).");
    addString(tb, "q                Quit to map.");
    addString(tb, "");

    // Research dialog.
    addBoldString(tb, "Research dialog:");
    addString(tb, "Up/down keys     Choose technology.");
    addString(tb, "Enter            Start research (will terminate current research).");
    addString(tb, "q                Quit to map.");
    addString(tb, "");
}

void addUnitInfoToTextbox(Textbox * tb, World * world, View * view)
{
    // Getting unit.
    Node * n = getNeighbour(view -> current_cell, EDGE_CELL_UNIT);
    Unit * u = (Unit *) n -> data;
    UnitCommonInfo * u_info = (UnitCommonInfo *) daGetByIndex(world -> units_info, u -> unit_id);

    addBoldString(tb, u_info -> name);
    addString(tb, "");

    addString(tb, "Symbol       %c", u_info -> c);
    addString(tb, "");

    addString(tb, "Health       %d", u_info -> max_health);
    addString(tb, "Damage       %d", u_info -> max_damage);
    addString(tb, "Moves        %d", u_info -> max_moves);
    addString(tb, "");

    addString(tb, "Hiring turns %d", u_info -> hiring_turns);
    addString(tb, "");

    addString(tb, "Gold drop    %d", u_info -> gold_drop);
    addString(tb, "");

    addString(tb, "Requires for hiring:");
    if(u_info -> resources == NULL || u_info -> resources -> length == 0)
    {
        addString(tb, "    Nothing");
    }
    else
    {
        for(int i = 0; i < u_info -> resources -> length; i++)
        {
            int r = iaGetByIndex(u_info -> resources, i);
            for(int j = 0; j < CELL_RES_COUNT; j++)
            {
                if(VIEW_RES_VALUES[j] == r)
                {
                    addString(tb, "    %s", VIEW_RES_NAMES[j]);
                    break;
                }
            }
        }
    }

    addString(tb, "");

    addString(tb, "Privileges:");
    if(u_info -> privileges == NULL || u_info -> privileges -> length == 0)
    {
        addString(tb, "    Nothing");
    }
    else
    {
        for(int i = 0; i < u_info -> privileges -> length; i++)
        {
            int r = iaGetByIndex(u_info -> privileges, i);
            for(int j = 0; j < UNIT_PRVL_COUNT; j++)
            {
                if(VIEW_PRVL_VALUES[j] == r)
                {
                    addString(tb, "    %s", VIEW_PRVL_NAMES[j]);
                    break;
                }
            }
        }
    }
}

void addWinInfoToTextbox(Textbox * tb)
{
    addBoldString(tb, "       Congratulations!       ");
    addString(tb,     "           You win!           ");
    addString(tb,     "You can continue game or quit.");
    addString(tb,     "");
    addString(tb,     "(press q to hide this message)");
}
