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
    // Create array
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
            // Copy name.
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

DynArray * strSplitAndAtoi(char delimiter, char * str, int max_length)
{
    // Create array
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
            // Convert to int and add to array.
            // Dirty hack for memory economy. It's silly to create pointer to
            // int!
            daPrepend(array, (int *) atoi(new_name));
            index = 0;
        }
    }
    new_name[index] = '\0';
    daPrepend(array, (int *) atoi(new_name));
    free(new_name);

    return array;
}
