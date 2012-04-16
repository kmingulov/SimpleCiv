#include <stdio.h>
#include "../../modules/graph/graph.h"

void foreachFunc(Node * parent, Node * child, Edge * link)
{
    printf("%d\t%d\t%d\n", (int) parent, (int) child, link -> type);
}

int main()
{
    int * data = malloc(sizeof(int));

    * data = 0;

    Node * head = createGraph(data), * child;

    for(int i = 1; i < 3; i++)
    {
        data = malloc(sizeof(int));
        * data = i;
        child = addNeighbour(head, i, data);
    }

    addEdge(child, head, 0);

    for(int i = 1; i < 3; i++)
    {
        data = malloc(sizeof(int));
        * data = i;
        addNeighbour(child, i, data);
    }

    // Test for "foreach".
    printf("Parent\t\tThis\t\tEdge type\n");
    foreachNeighbour(head, &foreachFunc);
    printf("\n");
    foreachNeighbour(child, &foreachFunc);

    return 0;
}
