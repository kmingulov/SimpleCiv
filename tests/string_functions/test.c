#include <stdio.h>
#include <string.h>
#include "../../modules/parser/string_functions.h"
#include "../../game/world/definitions.h"

const char res_names[][10] = {"bronze", "iron", "coal", "gunpowder", "horses",
    "mushrooms"};

const int res_values[] = {1, 2, 3, 4, 5, 6};

int resourcesConvertation(char * str)
{
    for(int i = 0; i < CELL_RES_COUNT; i++)
    {
        if(strcmp(str, res_names[i]) == 0)
        {
            return res_values[i];
        }
    }

    return 0;
}

int main()
{
    char str[] = {"bronze"};

    IntArray * array = strSplitAndConvert(',', str, &resourcesConvertation);

    if(array == NULL)
    {
        printf("NULL\n");
        return 0;
    }

    printf("%d:\n", array -> length);

    for(int i = 0; i < array -> length; i++)
    {
        printf("%d ", iaGetByIndex(array, i));
    }
    printf("\n");

    return 0;
}
