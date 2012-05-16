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

#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#define DYN_ARRAY_INCREMENT    5
#define DYN_ARRAY_POINTER_SIZE sizeof(int)

typedef struct DynArray
{
    int length;    // Length of dynamic array.
    int available; // How much elements we can add.
    void ** data;  // Array of pointers.
} DynArray;

/*
    Returns created dynamic array.
*/
DynArray * daCreate();

/*
    Destroy dynamic array. deleteFunc is deletion (for data) function.
*/
void daDestroy(DynArray * array, void (* deleteFunc)(void * data));

/*
    Expands array to another DYN_ARRAY_INCREMENT elements.
*/
void daExpand(DynArray * array);

/*
    Puts element in the end of array.
*/
void daPrepend(DynArray * array, void * data);

/*
    Gets element by index.
*/
void * daGetByIndex(DynArray * array, int index);

/*
    Gets last element in array.
*/
void * daGetLast(DynArray * array);

/*
    Searches for data in array. Returns index if found and -1 if not.
*/
int daSearchForData(DynArray * array, void * data);

/*
    Executes function for each element in array.
*/
void daForEach(DynArray * array, void (* function)(int index, void * data));

/*
    Removes _first_ element with pointer data. Will return 1, if nothing found, 
    and 0, if element succefully removed. deleteFunc is deletion (for data)
    function.
*/
int daRemoveByPointer(DynArray * array, void * data, void (* deleteFunc)(void * data));

#endif
