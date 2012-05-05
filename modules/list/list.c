#include <stdlib.h>

#include "list.h"

List * listCreate()
{
    List * list = malloc(sizeof(List));
    list -> length = 0;
    list -> head = NULL;
    return list;
}

void listDestroy(List * list, void (* function)(void * data))
{
    ListElement * current = list -> head;

    for(int i = 0; i < list -> length; i++)
    {
        ListElement * next = current -> next;
        function(current -> data);
        free(current);
        current = next;
    }

    free(list);
}

void listPrepend(List * list, void * data)
{
    ListElement * elem = malloc(sizeof(ListElement));
    elem -> data = data;

    (list -> length)++;

    if(list -> head == NULL)
    {
        list -> head = elem;
        elem -> next = elem;
        elem -> prev = elem;
    }
    else
    {
        ListElement * head = list -> head;
        ListElement * prev = list -> head -> prev;

        prev -> next = elem;
        elem -> prev = prev;
        elem -> next = head;
        head -> prev = elem;
    }
}

void * listGetByN(List * list, int n)
{
    if(list -> head == NULL)
    {
        return NULL;
    }

    int goal = n;
    if(goal < 0)
    {
        goal += list -> length;
    }

    ListElement * result = list -> head;

    for(int i = 0; i < goal; i++)
    {
        result = result -> next;
    }

    return result -> data;
}
