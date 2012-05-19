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

#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include "../dyn_array/dyn_array.h"
#include "../int_array/int_array.h"

/*
    Trim all spaces (checked by isspace() function) at the begin and at the end
    of string.
*/
void strTrimSpaces(char * str);

/*
    Split string to DynArray by delimiter.
*/
DynArray * strSplit(char delimiter, char * str);

/*
    Split string to IntArray, converts each element to int by function.
*/
IntArray * strSplitAndConvert(char delimiter, char * str, int (* function)(const char * data));

/*
    Split string to IntArray by delimiter (convertes each element to integer by
    atoi() function).
*/
IntArray * strSplitToInts(char delimiter, char * str);

#endif
