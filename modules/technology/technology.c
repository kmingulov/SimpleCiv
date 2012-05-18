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
#include "../graph/graph.h"

#include "technology.h"
#include "technology_parse_info.h"

void destroyTechnology(void * data)
{
    // Getting node.
    Node * n = (Node *) data;
    daDestroy(n -> edges, &free);

    // Getting technology.
    Technology * t = (Technology *) n -> data;

    if(t -> name != NULL)
    {
        free(t -> name);
    }

    if(t -> requires_resources != NULL)
    {
        iaDestroy(t -> requires_resources);
    }

    if(t -> provides_units != NULL)
    {
        iaDestroy(t -> provides_units);
    }

    free(t);
    free(n);
}

Node * createEdgesInTechnologyTree(DynArray * techs_data)
{
    // Passing each technology.
    for(int i = 0; i < techs_data -> length; i++)
    {
        TechnologyParseInfo * current = (TechnologyParseInfo *) daGetByIndex(techs_data, i);
        IntArray * provides = current -> provides_technologies;
        // For each neighbour creating two edges (TECH_PROVIDES and
        // TECH_REQUIRES).
        if(provides != NULL)
        {
            for(int j = 0; j < provides -> length; j++)
            {
                // Getting neighbour.
                int id = iaGetByIndex(provides, j);
                TechnologyParseInfo * neighbour = (TechnologyParseInfo *) daGetByIndex(techs_data, id);
                // Creating two edges.
                addEdge(current -> tech_in_tree, neighbour -> tech_in_tree, EDGE_TECH_PROVIDES);
                addEdge(neighbour -> tech_in_tree, current -> tech_in_tree, EDGE_TECH_REQUIRES);
            }
        }
    }

    // Returning first technology.
    return ((TechnologyParseInfo *) daGetByIndex(techs_data, 0)) -> tech_in_tree;
}
