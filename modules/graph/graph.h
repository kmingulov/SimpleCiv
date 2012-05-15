#ifndef GRAPH
#define GRAPH

#include "../dyn_array/dyn_array.h"

typedef struct Node
{
    // Type of this node.
    unsigned char type;
    // Color of this node. Used for graph traversal. 0 is white, 1 is black.
    unsigned char color;
    // Data of this node.
    void * data;
    // Edges to neighbours.
    DynArray * edges;
} Node;

typedef struct Edge
{
    unsigned char type;
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
void destroyNode(Node * target);

/*
    Destroys graph. deleteFunc is deletion function for data. unsigned char type
    is required for user, who need to know, what type of data he received.
    DynArray deleted is array of pointers to already deleted nodes.
    All module structs (DynArray in struct Node and target in struct Edge) will
    be destroyed by free() function.
*/
void destroyGraph(Node * head, DynArray * deleted, void (* deleteFunc)(unsigned char type, void * data));

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
