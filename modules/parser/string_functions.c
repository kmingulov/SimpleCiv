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

DynArray * strSplit(char delimiter, char * str, int max_length)
{
    if(str == NULL)
    {
        return NULL;
    }

    // Creating array
    DynArray * array = daCreate();

    char * new_name = malloc(sizeof(char) * max_length);
    int index = 0;
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] != delimiter)
        {
            if(index < max_length - 1)
            {
                new_name[index++] = str[i];
            }
        }
        else
        {
            new_name[index] = '\0';
            // Copying name.
            char * name = malloc(sizeof(char) * max_length);
            memcpy(name, new_name, sizeof(char) * max_length);
            daPrepend(array, name);
            index = 0;
        }
    }
    new_name[index] = '\0';
    daPrepend(array, new_name);

    return array;
}

IntArray * strSplitToInts(char delimiter, char * str)
{
    // Creating array
    IntArray * array = iaCreate();

    int current = 0;
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] != delimiter)
        {
            // Zero is 48.
            current = current * 10 + ( (int) str[i] - 48);
        }
        else
        {
            iaPrepend(array, current);
            current = 0;
        }
    }
    iaPrepend(array, current);

    return array;
}
