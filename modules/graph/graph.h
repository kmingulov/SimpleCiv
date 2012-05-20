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

#ifndef GRAPH_H
#define GRAPH_H

#include "../dyn_array/dyn_array.h"

typedef struct Node
{
    // Type of this node.
    unsigned char type;

    // Data of this node.
    void * data;

    // Edges to neighbours.
    DynArray * edges;
} Node;

typedef struct Edge
{
    // Type of this edge.
    unsigned char type;

    // Target.
    struct Node * target;
} Edge;

/*
    Adds neighbour (with node_type and data) to node. Edge will have type
    edge_type. This function will _create_ new Node in graph. To link two nodes
    use addEdge() function instead.
    Returns pointer to new node. If parent == NULL creates new graph.
*/
Node * addNode(Node * parent, unsigned char edge_type, unsigned char node_type, void * data);

/*
    Adds Edge from node1 to node2, edge_type is type of the edge.
*/
void addEdge(Node * node1, Node * node2, unsigned char edge_type);

/*
    Destroys _first_ found edge from node parent with edge_type.
*/
void destroyEdge(Node * parent, unsigned char edge_type);

/*
    Creates new graph.
*/
Node * createGraph(unsigned char node_type, void * data);

/*
    Destroys node and all it's edges (node -> edges array). This function won't
    delete edges to this node! Use carefully!
*/
void destroyNode(Node * target, void (* deleteFunc)(unsigned char type, void * data));

/*
    Runs function for each neighbour of Node parent.
*/
void foreachNeighbour(Node * parent, void (* function)(Node * parent, Node * child, Edge * edge));

/*
    Returns _first_ neighbour-node with edge_type. Returns NULL, if nothing
    found.
*/
Node * getNeighbour(Node * parent, unsigned char edge_type);

#endif
