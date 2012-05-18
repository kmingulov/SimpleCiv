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
#include "technology_parse_info.h"
#include "technology.h"

TechnologyParseInfo * createTechnologyParseInfo()
{
    // Creating new data.
    TechnologyParseInfo * data = malloc(sizeof(TechnologyParseInfo));
    Technology * tech = malloc(sizeof(Technology));

    // Creating new node.
    data -> tech_in_tree = addNode(NULL, 0, NODE_TECHNOLOGY, tech);

    // NULLing all pointers (if something isn't defined in xml-file).
    data -> provides_technologies = NULL;
    tech -> name = NULL;
    tech -> requires_resources = NULL;
    tech -> provides_units = NULL;

    // Returning result.
    return data;
}

void destroyTechnologyParseInfo(void * data)
{
    TechnologyParseInfo * t = (TechnologyParseInfo *) data;
    if(t -> provides_technologies != NULL)
    {
        iaDestroy(t -> provides_technologies);
    }
    free(t);
}
