#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../modules/list/list.h"

int main()
{
    List * l = listCreate();

    assert(listGetByN(l, 0) == NULL);

    for(int i = 0; i < 3; i++)
    {
        int * d = malloc(sizeof(int));
        * d = i;
        listPrepend(l, d);
    }

    ListElement * head = l -> head;

    assert(head -> prev -> next == head);
    assert(head -> next -> prev == head);
    assert(head -> next -> next -> next == head);
    assert(head -> prev -> prev -> prev == head);

    assert( * ((int *) listGetByN(l, 1)) == 1);
    assert( * ((int *) listGetByN(l, 3)) == 0);
    assert( * ((int *) listGetByN(l, -1)) == 2);

    assert( listGetByN(l, 0) == head -> data);
    assert( listGetByN(l, 1) == head -> next -> data);
    assert( listGetByN(l, 1) == head -> prev -> prev -> data);
    assert( listGetByN(l, 2) == head -> next -> next -> data);
    assert( listGetByN(l, 2) == head -> prev -> data);

    listDestroy(l, &free);

    return 0;
}
