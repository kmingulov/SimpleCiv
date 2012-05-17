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

#include "graph.h"

Node * addNode(Node * parent, unsigned char edge_type, unsigned char node_type, void * data)
{
    // Creating new node.
    Node * child = malloc(sizeof(Node));
    child -> type = node_type;
    child -> color = 0;
    child -> data = data;
    child -> edges = daCreate();

    // If parent isn't null linking two nodes.
    if(parent != NULL)
    {
        addEdge(parent, child, edge_type);
    }

    return child;
}

void addEdge(Node * node1, Node * node2, unsigned char edge_type)
{
    // Creating edge.
    Edge * edge = malloc(sizeof(Edge));
    edge -> type = edge_type;
    edge -> target = node2;
    // Linking node1 and node2.
    daPrepend(node1 -> edges, edge);
}

void destroyEdge(Node * parent, unsigned char edge_type)
{
    DynArray * edges = parent -> edges;
    // Search for edge with edge_type.
    for(int i = 0; i < edges -> length; i++)
    {
        Edge * edge = daGetByIndex(edges, i);
        if(edge -> type == edge_type)
        {
            // Destroy edge.
            daRemoveByPointer(edges, edge, &free);
            break;
        }
    }
}

Node * createGraph(unsigned char node_type, void * data)
{
    return addNode(NULL, 0, node_type, data);
}

void destroyNode(Node * target, void (* deleteFunc)(unsigned char type, void * data))
{
    daDestroy(target -> edges, &free);

    if(deleteFunc != NULL)
    {
        deleteFunc(target -> type, target -> data);
    }

    free(target);
}

void destroyGraph(Node * head, DynArray * deleted, void (* deleteFunc)(unsigned char type, void * data))
{
    // «Painting» this node.
    head -> color = 1;

    // Deleting data.
    deleteFunc(head -> type, head -> data);
    daPrepend(deleted, head);

    // Passing array of edges.
    DynArray * array = head -> edges;
    for(int i = 0; i < array -> length; i++)
    {
        // Target.
        Node * target = ((Edge *) daGetByIndex(array, i)) -> target;
        // Searching is this node deleted or not yet.
        if(daSearchForData(deleted, target) == -1)
        {
            destroyGraph(target, deleted, deleteFunc);
        }
    }

    // Destroy array of edges.
    daDestroy(array, &free);

    // Destroy this element.
    free(head);
}

void foreachNeighbour(Node * parent, void (* function)(Node * parent, Node * child, Edge * edge))
{
    DynArray * array = parent -> edges;
    for(int i = 0; i < array -> length; i++)
    {
        function(parent, ((Edge *) daGetByIndex(array, i)) -> target, daGetByIndex(array, i));
    }
}

Node * getNeighbour(Node * parent, unsigned char edge_type)
{
    if(parent == NULL)
    {
        return NULL;
    }

    // Searching node.
    DynArray * array = parent -> edges;
    int i = 0;
    while( i < array -> length && ((Edge *) daGetByIndex(array, i)) -> type != edge_type )
    {
        i++;
    }

    // Nothing found.
    if(i == array -> length)
    {
        return NULL;
    }

    // Returning result.
    return ((Edge *) daGetByIndex(array, i)) -> target;
}
