#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../modules/list/list.h"

void foreach(void * data)
{
    printf("%d\n", * ((int *) data));
}

int main()
{
    List * l = listCreate();

    assert(listGetByN(l, 0) == NULL);

    int * data = NULL;

    for(int i = 0; i < 3; i++)
    {
        data = malloc(sizeof(int));
        * data = i;
        listPrepend(l, data);
    }

    listForEach(l, &foreach);

    ListElement * head = l -> head;

    assert( getListElementByPointer(l, data) == head -> prev );

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
