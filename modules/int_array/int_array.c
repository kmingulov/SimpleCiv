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
#include <string.h>

#include "int_array.h"

IntArray * iaCreate()
{
    IntArray * array = malloc(sizeof(IntArray));

    array -> length = 0;
    array -> available = INT_ARRAY_INCREMENT;
    array -> data = malloc(sizeof(int) * array -> available);

    return array;
}

IntArray * iaCopy(IntArray * array)
{
    IntArray * copy = malloc(sizeof(IntArray));

    copy -> length = array -> length;
    copy -> available = array -> available;
    copy -> data = malloc(sizeof(int) * (copy -> length + copy -> available));
    memcpy(copy -> data, array -> data, sizeof(int) * copy -> length);

    return copy;
}

IntArray * iaLengthCreate(int length)
{
    IntArray * array = malloc(sizeof(IntArray));

    array -> length = length;
    array -> available = 0;
    array -> data = calloc(length, sizeof(int));

    return array;
}

void iaDestroy(IntArray * array)
{
    free(array -> data);
    free(array);
}

void iaExpand(IntArray * array)
{
    // Expanding array.
    array -> available += INT_ARRAY_INCREMENT;
    // Allocating new memory.
    void * new_data = malloc(sizeof(int) * (array -> length + array -> available));
    // Coping old data.
    memcpy(new_data, array -> data, sizeof(int) * array -> length);
    // Deleting old data and remembering pointer.
    free(array -> data);
    array -> data = new_data;
}

void iaPrepend(IntArray * array, int n)
{
    if(array -> available == 0)
    {
        iaExpand(array);
    }

    array -> data[array -> length] = n;

    array -> available--;
    array -> length++;
}

int iaGetByIndex(IntArray * array, int index)
{
    return array -> data[index];
}

void iaSetByIndex(IntArray * array, int index, int value)
{
    array -> data[index] = value;
}

void iaIncrementByIndex(IntArray * array, int index, int value)
{
    array -> data[index] += value;
}

int iaSearchForData(IntArray * array, int value)
{
    for(int i = 0; i < array -> length; i++)
    {
        if(iaGetByIndex(array, i) == value)
        {
            return i;
        }
    }

    return -1;
}
