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
#include "../unit/unit.h"
#include "../city/city.h"
#include "map.h"

Node * createRow(int l)
{
    Cell * head = malloc(sizeof(Cell));
    head -> territory = 0;
    head -> resources = 0;
    head -> mine = 0;

    // Creating row.
    Node * row_head = createGraph(NODE_CELL, head);
    Node * previous = row_head;

    for(int i = 0; i < l - 1; i++)
    {
        // Creating new cell.
        Cell * temp = malloc(sizeof(Cell));
        temp -> territory = 0;
        temp -> resources = 0;
        temp -> mine = 0;
        // Adding this cell to row (+ edge from previous to new).
        Node * new = addNode(previous, EDGE_CELL_RIGHT, NODE_CELL, temp);
        // Adding edge (from new to previous).
        addEdge(new, previous, EDGE_CELL_LEFT);
        // Going on.
        previous = new;
    }

    // Add last edges.
    addEdge(previous, row_head, EDGE_CELL_RIGHT);
    addEdge(row_head, previous, EDGE_CELL_LEFT);

    return row_head;
}

void mergeRows(Node * n1, Node * n2)
{
    Node * x1 = n1;
    Node * x2 = n2;

    do
    {
        addEdge(x1, x2, EDGE_CELL_BOTTOM);
        addEdge(x2, x1, EDGE_CELL_TOP);
        x1 = getNeighbour(x1, EDGE_CELL_RIGHT);
        x2 = getNeighbour(x2, EDGE_CELL_RIGHT);
    } while (x1 != n1 || x2 != n2);
}

Map * createMap(unsigned int max_r, unsigned int max_c)
{
    Map * map = malloc(sizeof(Map));

    map -> max_r = max_r;
    map -> max_c = max_c;

    Node * head = createRow(max_c);
    Node * row = head;

    for(int i = 0; i < max_r - 1; i++)
    {
        // Creating new row.
        Node * new_row = createRow(max_c);
        // Merging two rows.
        mergeRows(row, new_row);
        // Going on.
        row = new_row;
    }

    mergeRows(row, head);

    map -> head = head;

    return map;
}

/*
    Auxiliary function for units and cities deletion.
*/
void destroyUnitsAndCities(Node * parent, Node * child, Edge * edge)
{
    if(edge -> type == EDGE_CELL_UNIT)
    {
        destroyNode(child, &destroyUnitNodeData);
    }
    else if(edge -> type == EDGE_CELL_CITY)
    {
        destroyNode(child, destroyCityNodeData);
    }
}

/*
    Auxiliary function for cell deletion.
*/
void destroyCell(unsigned char type, void * data)
{
    free(data);
}

void destroyMap(Map * map)
{
    Node * current = map -> head;
    Node * next_row = current;

    for(int i = 0; i < map -> max_r; i++)
    {
        next_row = getNeighbour(next_row, EDGE_CELL_BOTTOM);
        for(int j = 0; j < map -> max_c; j++)
        {
            // Destroing units and cities.
            foreachNeighbour(current, &destroyUnitsAndCities);
            // Getting next.
            Node * next = getNeighbour(current, EDGE_CELL_RIGHT);
            // Removing this node and all it's edges.
            destroyNode(current, &destroyCell);
            // Going on.
            current = next;
        }
        current = next_row;
        // At first next_row = getNeighbour(next_row, EDGE_CELL_BOTTOM); was
        // here, but it was moved because at final step we deleted all map and
        // have no cell to getNeighbour() => segmentation fault.
    }

    free(map);
}

Node * getMapCell(Map * map, int r, int c)
{
    return getCell(map -> head, r, c);
}

Node * getCell(Node * node, int r, int c)
{
    Node * result = node;

    if(r > 0)
    {
        for(int i = 0; i < r; i++)
        {
            result = getNeighbour(result, EDGE_CELL_BOTTOM);
        }
    }
    else
    {
        for(int i = 0; i > r; i--)
        {
            result = getNeighbour(result, EDGE_CELL_TOP);
        }
    }

    if(c > 0)
    {
        for(int i = 0; i < c; i++)
        {
            result = getNeighbour(result, EDGE_CELL_RIGHT);
        }
    }
    else
    {
        for(int i = 0; i > c; i--)
        {
            result = getNeighbour(result, EDGE_CELL_LEFT);
        }
    }

    return result;
}
