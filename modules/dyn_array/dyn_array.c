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

#include <string.h>
#include <stdlib.h>

#include "dyn_array.h"

DynArray * daCreate()
{
    DynArray * array = malloc(sizeof(DynArray));

    array -> length = 0;
    array -> available = DYN_ARRAY_INCREMENT;
    array -> data = malloc(DYN_ARRAY_POINTER_SIZE * array -> available);

    return array;
}

void daDestroy(DynArray * array, void (* deleteFunc)(void * data))
{
    for(int i = 0; i < array -> length; i++)
    {
        // deleteFunc == NULL means that user don't want to delete his data.
        if(deleteFunc != NULL)
        {
            deleteFunc(array -> data[i]);
        }
    }

    free(array -> data);
    free(array);
}

void daExpand(DynArray * array)
{
    // Expanding array.
    array -> available += DYN_ARRAY_INCREMENT;
    // Allocating new memory.
    void ** new_data = malloc(DYN_ARRAY_POINTER_SIZE * (array -> length + array -> available));
    // Coping old data.
    memcpy(new_data, array -> data, DYN_ARRAY_POINTER_SIZE * array -> length);
    // Deleting all data and remembering pointer.
    free(array -> data);
    array -> data = new_data;
}

void daPrepend(DynArray * array, void * data)
{
    if(array -> available == 0)
    {
        daExpand(array);
    }

    array -> data[array -> length] = data;

    array -> available--;
    array -> length++;
}

void * daGetByIndex(DynArray * array, int index)
{
    // Max index = array -> length - 1. Index cannot be over max index.
    if(index > array -> length - 1 || index < 0)
    {
        return NULL;
    }

    return array -> data[index];
}

void * daGetLast(DynArray * array)
{
    return array -> data[array -> length - 1];
}

int daSearchForData(DynArray * array, void * data)
{
    int i;

    for(i = 0; i < array -> length; i++)
    {
        if(array -> data[i] == data)
        {
            break;
        }
    }

    if(i != array -> length)
    {
        return i;
    }

    return -1;
}

void daForEach(DynArray * array, void (* function)(int index, void * data))
{
    for(int i = 0; i < array -> length; i++)
    {
        function(i, array -> data[i]);
    }
}

int daRemoveByPointer(DynArray * array, void * data, void (* deleteFunc)(void * data))
{
    int index = 0;

    // Searching for data.
    // Max index = array -> length - 1, so index had to be less than max index.
    while(index <= array -> length - 1 && array -> data[index] != data)
    {
        index++;
    }

    // Nothing found.
    if(index == array -> length)
    {
        return 1;
    }

    // Deleting data.
    if(deleteFunc != NULL)
    {
        deleteFunc(array -> data[index]);
    }

    // Moving all elements.
    for(int i = index; i < array -> length - 1; i++)
    {
        array -> data[i] = array -> data[i + 1];
    }

    array -> length--;
    array -> available++;

    // We don't use function same as daExpand() because in our need there is no
    // reason for this (we don't use remove so often).

    // All done.
    return 0;
}
