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
