#include "graph.h"

Node * addNeighbour(Node * parent, int edge_type, void * data)
{
    Node * child = malloc(sizeof(Node));
    child -> data = data;
    child -> neighbours = daCreate();
    
    if(parent != NULL)
    {
        addEdge(parent, child, edge_type);
    }

    return child;
}

void addEdge(Node * node1, Node * node2, int edge_type)
{
    // Creating edge.
    Edge * edge = malloc(sizeof(Edge));
    edge -> type = edge_type;
    edge -> target = node2;
    // Linking node1 and node2.
    daPrepend(node1 -> neighbours, edge);
}

Node * createGraph(void * data)
{
    return addNeighbour(NULL, 0, data);
}

void destroyGraph(Node * head, void (* deleteFunc)(void * data))
{
    // TODO Here I want to write DFS algorithm (Depth-first search).
    // I really don't know how write it more better. There is only one idea I
    // have: use two arrays (DynArray * pointers, * status). One will contains
    // pointers of nodes, other — information, visited this node or no.
    // Or use one array but with another struct (pointer to Node  and status).
}

void foreachNeighbour(Node * parent, void (* function)(Node * parent, Node * child, Edge * link))
{
    // We doing it all manually (not through DynArray module), because ISO C
    // forbids nested functions.
    DynArray * array = parent -> neighbours;
    for(int i = 0; i < array -> length; i++)
    {
        function(parent, ((Edge *) array -> data[i]) -> target, array -> data[i]);
    }
}
