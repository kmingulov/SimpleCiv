#include <stdio.h>
#include <assert.h>
#include "../../modules/graph/graph.h"

void foreachFunc(Node * parent, Node * child, Edge * link)
{
    printf("%d\t%d\t%d\n", (int) parent, (int) child, link -> type);
}

void deleteFunc(void * data)
{
    free(data);
}

int main()
{
    int * data = malloc(sizeof(int));

    * data = 0;

    Node * head = createGraph(data);

    // Create and print simple graph.
    printf("Parent\t\tThis\t\tEdge type\n");
    for(int i = 1; i < 5; i++)
    {
        data = malloc(sizeof(int));
        * data = i;
        Node * child = addNode(head, i, data);
        addEdge(child, head, 0);
        for(int j = 11; j < 15; j++)
        {
            data = malloc(sizeof(int));
            * data = j;
            addNode(child, j, data);
        }
        foreachNeighbour(child, &foreachFunc);
        printf("\n");
    }
    foreachNeighbour(head, &foreachFunc);

    // Test for search.
    assert( *((int *) getNeighbour(head, 4) -> data) == 4 );
    assert( getNeighbour(head, 5) == NULL );

    // And destroy it.
    destroyGraph(head, &free);

    return 0;
}
