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

#ifndef TECHNOLOGY_H
#define TECHNOLOGY_H

#include "../dyn_array/dyn_array.h"
#include "../int_array/int_array.h"
#include "../graph/graph.h"

/*
    This is struct of technology. It only for technology tree (common for _all_
    players).
    Each player will have table with technologies' id and value (see definitions
    in game/model/definitions.h).
*/
typedef struct Technology
{
    // Id and name of technology.
	int id;
    char * name;

    // How many turns have to spend on researching this technology.
    int turns;

    // Required resources.
    IntArray * requires_resources;

    // Provided units.
    IntArray * provides_units;
} Technology;

/*
    Destroys Node with technology.
*/
void destroyTechnology(void * data);

/*
    Creates edges in technology tree.
*/
Node * createEdgesInTechnologyTree(DynArray * techs_data);

#endif
