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

#ifndef MODEL_H
#define MODEL_H

#include "../../modules/dyn_array/dyn_array.h"
#include "../../modules/player/player.h"
#include "../../modules/graph/graph.h"
#include "../../modules/map/map.h"
#include "definitions.h"
#include "world_properties.h"

/*
    Struct of world.
*/
typedef struct World
{
    // Properties.
    WorldProperties * properties;

    // Game map.
    Map * map;

    // Game graph.
    Node * graph_players;

    // Computer player.
    Player * computer;

    // Technology tree. Type of each node is struct Technology.
    Node * tech_tree;

    // Common info about technologies and units.
    DynArray * units_info; // Type — UnitCommonInfo.
    DynArray * techs_info; // Type — Node (in tech tree).
} World;

/*
    Creates world.
*/
World * createWorld();

/*
    Destroys world.
*/
void destroyWorld(World * world);

#endif
