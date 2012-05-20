/*

    SimpleCiv is simple clone of Civilization game, using ncurses library.
    Copyright (C) 2012 by K. Mingulov, A. Sapronov.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

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
        if(function != NULL)
        {
            function(current -> data);
        }
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

void * listGetHead(List * list)
{
    return listGetByN(list, 0);
}

ListElement * getListElementByPointer(List * list, void * data)
{
    ListElement * current = list -> head;

    for(int i = 0; i < list -> length; i++)
    {
        if(current -> data == data)
        {
            return current;
        }
        current = current -> next;
    }

    return NULL;
}

int listDeleteByPointer(List * list, void * data, void (* function)(void * data))
{
    ListElement * current = list -> head;

    if(current -> data == data)
    {
        ListElement * prev = current -> prev;
        ListElement * next = current -> next;

        prev -> next = next;
        next -> prev = prev;

        if(function != NULL)
        {
            function(current -> data);
        }
        free(current);

        list -> length--;
        if(list -> length == 0)
        {
            // No more elements.
            list -> head = NULL;
        }
        else
        {
            list -> head = next;
        }

        return 0;
    }

    for(int i = 0; i < list -> length; i++)
    {
        if(current -> data == data)
        {
            ListElement * prev = current -> prev;
            ListElement * next = current -> next;

            prev -> next = next;
            next -> prev = prev;

            if(function != NULL)
            {
                function(current -> data);
            }
            free(current);

            list -> length--;

            return 0;
        }
        current = current -> next;
    }

    return 1;
}

void listForEach(List * list, void (* function)(void * data))
{
    ListElement * current = list -> head;

    for(int i = 0; i < list -> length; i++)
    {
        ListElement * next = current -> next;
        function(current -> data);
        current = next;
    }
}

void listScrollNext(List * list)
{
    list -> head = list -> head -> next;
}
