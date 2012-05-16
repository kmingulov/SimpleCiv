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

#ifndef INT_ARRAY_H
#define INT_ARRAY_H

#define INT_ARRAY_INCREMENT 5

/*
    This struct seems like a DynArray struct. But DynArray uses pointers to
    data, this is just a dynamical array of ints.
*/
typedef struct IntArray
{
    int length;    // Length of dynamic array.
    int available; // How much elements we can add.
    int * data;    // Data.
} IntArray;

/*
    Creates array.
*/
IntArray * iaCreate();

/*
    Copies the array.
*/
IntArray * iaCopy(IntArray * array);

/*
    Creates an array with length.
*/
IntArray * iaLengthCreate(int length);

/*
    Destroys array.
*/
void iaDestroy(IntArray * array);

/*
    Expands array with another INT_ARRAY_INCREMENT elements.
*/
void iaExpand(IntArray * array);

/*
    Adds n to the array.
*/
void iaPrepend(IntArray * array, int n);

/*
    Returns element #index.
    NOTE: This functions doesn't check is index out of bounds! Please, check it
    manually!
*/
int iaGetByIndex(IntArray * array, int index);

/*
    Sets element #index value to value.
*/
void iaSetByIndex(IntArray * array, int index, int value);

/*
    Increment value of #index element by value.
*/
void iaIncrementByIndex(IntArray * array, int index, int value);

/*
    Returns first found positions of value in the array.
    Returns -1 if nothing found.
*/
int iaSearchForData(IntArray * array, int value);

#endif
