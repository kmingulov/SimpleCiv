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
#include "technology_table.h"

IntArray * createTechnologyTable(DynArray * techs_info)
{
    IntArray * result = iaLengthCreate(techs_info -> length);
    for(int i = 0; i < result -> length; i++)
    {
        // Getting node of technology.
        Node * tech = (Node *) daGetByIndex(techs_info, i);

        // If there is no «require» edges, set this technology to already
        // researched.
        if(getNeighbour(tech, EDGE_TECH_REQUIRES) == NULL)
        {
            iaSetByIndex(result, i, TECH_RESEARCHED);
        }
        else
        {
            iaSetByIndex(result, i, TECH_NOT_AVAILABLE);
        }
    }

    for(int i = 0; i < result -> length; i++)
    {
        if(iaGetByIndex(result, i) == TECH_RESEARCHED)
        {
            updateTechnologyTable(result, daGetByIndex(techs_info, i));
        }
    }
    

    return result;
}

void updateTechnologyTable(IntArray * tech_table, Node * tech)
{
    // Getting technology.
    Technology * t = (Technology *) tech -> data;

    // Marking technology as researched.
    iaSetByIndex(tech_table, t -> id, TECH_RESEARCHED);

    DynArray * edges = tech -> edges;
    for(int i = 0; i < edges -> length; i++)
    {
        Edge * edge = (Edge *) daGetByIndex(edges, i);
        // Checking only for «provides» edges.
        if(edge -> type == EDGE_TECH_PROVIDES)
        {
            // Getting target's edges.
            DynArray * t_edges = edge -> target -> edges;
            unsigned char success = 1;
            for(int j = 0; j < t_edges -> length; j++)
            {
                Edge * t_edge = (Edge *) daGetByIndex(t_edges, j);
                // Checking only for «requires» edges.
                if(t_edge -> type == EDGE_TECH_REQUIRES)
                {
                    Technology * t = (Technology *) t_edge -> target -> data;
                    // If technology already researched, go on! If no, break.
                    if(iaGetByIndex(tech_table, t -> id) != TECH_RESEARCHED)
                    {
                        success = 0;
                        break;
                    }
                }
            }
            // Player can research this technology.
            if(success == 1)
            {
                int id = ((Technology *) edge -> target -> data) -> id;
                iaSetByIndex(tech_table, id, TECH_AVAILABLE);
            }
        }
    }
}

int checkForResources(Technology * tech, Player * player)
{
    // Checking for resources.
    if(tech -> requires_resources == NULL)
    {
        // Nothing requires. Great.
        return 1;
    }

    // Checking for each resource.
    char okay = 1;
    for(int i = 0; i < tech -> requires_resources -> length; i++)
    {
        // Getting resource id.
        int id = iaGetByIndex(tech -> requires_resources, i);
        // Does player have this resources?
        if(iaGetByIndex(player -> resources, id) == 0)
        {
            // Sad but true.
            okay = 0;
            break;
        }
    }

    // You're lucky man.
    if(okay == 1)
    {
        return 1;
    }

    return 0;
}
