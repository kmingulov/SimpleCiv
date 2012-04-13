#include <stdio.h>
#include <assert.h>
#include "../../modules/dyn_array/dyn_array.h"

void functionChars(void * data)
{
    free(data);
}

int main()
{
    DynArray * array = daCreate(); 
    char * data, * new_data;

    // Creating array of strings: A, AB, ABC, ABCD, ABCDE…
    for(int i = 0; i < 26; i++)
    {
        data = malloc(sizeof(char) * (i + 2));

        if(i == 2)
        {
            new_data = data;
        }

        for(int j = 0; j < i + 1; j++)
        {
            data[j] = j + 65;
        }
        data[i + 1] = '\0';
        daPrepend(array, data);
    }

    // Basic tests.
    assert(array -> length == 26);
    assert(array -> available == 4);

    // Tests for get.
    assert((char *) daGetByIndex(array, 25) == data);
    assert((char *) daGetByIndex(array, -1) == NULL);
    assert((char *) daGetByIndex(array, 26) == NULL);

    // Tests for remove.
    assert(daRemoveByPointer(array, NULL, &functionChars) == 0);
    assert(daRemoveByPointer(array, new_data, &functionChars) == 1);
    assert(daRemoveByPointer(array, data, &functionChars) == 1);

    // All done.
    daDestroy(array, &functionChars);

    return 0;
}
