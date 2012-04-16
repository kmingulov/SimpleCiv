#ifndef GRAPH
#define GRAPH

#include "../dyn_array/dyn_array.h"

typedef struct Node
{
    void * data;
    DynArray * neighbours;
} Node;

typedef struct Edge
{
    int type;
    struct Node * target;
} Edge;

/*
    Adds neighbour (with edge_type and data) to node. This function will
    _create_ new Node in graph. To link two nodes use addEdge() function
    instead.
    Returns pointer to new node. If parent == NULL creates new graph.
*/
Node * addNeighbour(Node * parent, int edge_type, void * data);

/*
    Adds Edge from node1 to node2, edge_type is type of the edge.
*/
void addEdge(Node * node1, Node * node2, int edge_type);

/*
    Creates new graph.
*/
Node * createGraph(void * data);

/*
    Destroys graph.
*/
void destroyGraph(Node * head, void (* deleteFunc)(void * data));

/*
    Runs function for each neighbour of Node parent.
*/
void foreachNeighbour(Node * parent, void (* function)(Node * parent, Node * child, Edge * link));

#endif
