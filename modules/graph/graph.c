#include "graph.h"

Node * addNode(Node * parent, int edge_type, void * data)
{
    Node * child = malloc(sizeof(Node));
    child -> color = 0;
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
    return addNode(NULL, 0, data);
}

void destroyGraph(Node * head, void (* deleteFunc)(void * data))
{
    // TODO Okay I found, that I can put a char in struct and use it. So let it
    // be so (maybe for a time, I don't know).

    // "Paint" this node.
    head -> color = 1;
    // Delete data.
    deleteFunc(head -> data);

    // Pass array of neighbours.
    DynArray * array = head -> neighbours;
    for(int i = 0; i < array -> length; i++)
    {
        Node * target = ((Edge *) array -> data[i]) -> target;
        // Run this function for non-deleted node.
        if(target -> color == 0)
        {
            destroyGraph(target, deleteFunc);
        }
    }

    // Destroy array of neighbours.
    daDestroy(array, &free);

    // Destroy this element.
    free(head);
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

Node * getNeighbour(Node * parent, int edge_type)
{
    DynArray * array = parent -> neighbours;
    int i = 0;
    while( i < array -> length && ((Edge *) array -> data[i]) -> type != edge_type )
    {
        i++;
    }

    if(i == array -> length)
    {
        return NULL;
    }

    return ((Edge *) array -> data[i]) -> target;
}
