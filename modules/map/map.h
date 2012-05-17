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

#ifndef MAP_H
#define MAP_H

#include "../graph/graph.h"

/*
    Struct of whole map.
*/
typedef struct Map
{
    // Sizes (in rows and columns).
    unsigned int max_r;
    unsigned int max_c;

    // Head of the map.
    Node * head;
} Map;

/*
    Struct of one cell.
*/
typedef struct Cell
{
    // Type of territory.
    unsigned char territory;

    // Resources.
    unsigned char resources;

    // Is there mine or not.
    unsigned char mine;
} Cell;

/*
    Creates double circular row list from cells.
*/
Node * createRow(int l);

/*
    Merges two rows, created by createRow() function.
*/
void mergeRows(Node * n1, Node * n2);

/*
    Creates map with max_r rows and max_c columns.
*/
Map * createMap(unsigned int max_r, unsigned int max_c);

/*
    Destroys map. This functions doesn't use destroyGraph() function.
    It's _highly_ recommended to use this function instead of destroyGraph().
    Reason is simple — map is symmetric. Computational complexity of this
    algorithm is O(N), of destroyGraph() algorithm — O(N²).
*/
void destroyMap(Map * map);

/*
    Gets cell in row r, column c (assumed that map -> head is (0,0) point).
*/
Node * getMapCell(Map * map, int r, int c);

/*
    Gets cell in row r, column c away from cell.
*/
Node * getCell(Node * node, int r, int c);

#endif
