#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../modules/graph/graph.h"

#define NODE_TYPE 126

void foreachFunc(Node * parent, Node * child, Edge * link)
{
    printf("%d\t%d\t%d\t\t%d\n", (int) parent, (int) child, child -> type, link -> type);
}

void deleteFunc(unsigned char type, void * data)
{
    free(data);
}

int main()
{
    int * data = malloc(sizeof(int));

    * data = 0;

    Node * head = createGraph(NODE_TYPE, data);

    // Create and print simple graph.
    printf("Parent\t\tThis\t\tData type\tEdge type\n");
    for(int i = 1; i < 5; i++)
    {
        data = malloc(sizeof(int));
        * data = i;
        Node * child = addNode(head, i, NODE_TYPE, data);
        addEdge(child, head, 0);
        for(int j = 11; j < 15; j++)
        {
            data = malloc(sizeof(int));
            * data = j;
            addNode(child, j, NODE_TYPE, data);
        }
        foreachNeighbour(child, &foreachFunc);
        printf("\n");
    }
    foreachNeighbour(head, &foreachFunc);

    // Test for search.
    assert( *((int *) getNeighbour(head, 4) -> data) == 4 );
    assert( getNeighbour(head, 5) == NULL );

    // Auxiliary array for deletion.
    DynArray * deleted = daCreate();

    // Destroing graph.
    destroyGraph(head, deleted, &deleteFunc);

    // Add auxiliary array.
    daDestroy(deleted, NULL);

    return 0;
}
