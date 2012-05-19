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
#include <ctype.h>

#include "string_functions.h"

void strTrimSpaces(char * str)
{
    int start = 0;
    int finish = strlen(str) - 1;

    while(isspace(str[start]) && start <= finish)
    {
        start++;
    }

    while(isspace(str[finish]) && finish > start)
    {
        finish--;
    }

    for(int i = 0; i < strlen(str) - start; i++)
    {
        str[i] = str[i + start];
    }

    str[finish - start + 1] = '\0';
}

DynArray * strSplit(char delimiter, char * str)
{
    if(str == NULL)
    {
        return NULL;
    }

    // Creating array
    DynArray * array = daCreate();

    // Copying buffer. Maximal size of result is length of string str (including
    // 0-determinant).
    char * buffer = malloc((strlen(str) + 1) * sizeof(char));

    // Current index (in str string).
    int index = 0;

    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] != delimiter)
        {
            // Add char to the buffer.
            buffer[index++] = str[i];
        }

        // If this end of string or delimiter was found and length of
        // buffer != 0 add new string to the array.
        if((i == strlen(str) - 1 || str[i] == delimiter) && index != 0)
        {
            // Add 0 determinant.
            buffer[index] = '\0';
            // Save buffer contents to new string.
            char * new_str = malloc((strlen(buffer) + 1) * sizeof(char));
            memcpy(new_str, buffer, sizeof(char) * (strlen(buffer) + 1));
            // Add string to the array.
            daPrepend(array, new_str);
            index = 0;
        }
    }

    // Free buffer.
    free(buffer);

    return array;
}

IntArray * strSplitAndConvert(char delimiter, char * str, int (* function)(const char * data))
{
    // Auxiliary array.
    DynArray * array = strSplit(delimiter, str);

    // Failed.
    if(array == NULL)
    {
        return NULL;
    }

    // Create an array.
    IntArray * result = iaCreate();

    for(int i = 0; i < array -> length; i++)
    {
        char * tmp = daGetByIndex(array, i);
        iaPrepend(result, function(tmp));
    }

    // Free the auxiliary array.
    daDestroy(array, &free);

    // All done.
    return result;
}

IntArray * strSplitToInts(char delimiter, char * str)
{
    return strSplitAndConvert(delimiter, str, &atoi);
}
