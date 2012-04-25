#ifndef GRAPH
#define GRAPH

#include "../dyn_array/dyn_array.h"

typedef struct Node
{
    // Type of this node.
    // TODO Maybe do something more good? Or char type, where types are 0..99,
    // and +100, if there is color. I.e. type == 1 means that type is 1 and
    // color is 0, type == 101 means that type is 1 and color is 1.
    int type;
    // Color of this node. Used for graph traversal. 0 is white, 1 is black.
    char color;
    // Data of this node.
    void * data;
    // Edges to neighbours.
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
Node * addNode(Node * parent, int edge_type, int node_type, void * data);

/*
    Adds Edge from node1 to node2, edge_type is type of the edge.
*/
void addEdge(Node * node1, Node * node2, int edge_type);

/*
    Creates new graph.
*/
Node * createGraph(int node_type, void * data);

/*
    Destroys graph. deleteFunc is deletion function for data.
    All our structs (DynArray in struct Node and target in struct Edge) will be
    destroyed by free() function.
*/
void destroyGraph(Node * head, void (* deleteFunc)(int type, void * data));

/*
    Runs function for each neighbour of Node parent.
*/
void foreachNeighbour(Node * parent, void (* function)(Node * parent, Node * child, Edge * link));

/*
    Returns _first_ node with edge_type. Returns NULL, if nothing found.
*/
Node * getNeighbour(Node * parent, int edge_type);

#endif
