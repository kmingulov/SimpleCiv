#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include "../../modules/dyn_array/dyn_array.h"

void function(void * data)
{
    printf("%s\n", (char *) data);
    free(data);
}

void functionInts(void * data)
{
    printf("%d\n", * ((int *) data));
    free(data);
}

int main()
{
    // Initialize random.
    srand(time(NULL));

    // Creates dynamical array.
    DynArray * array = createDynArray();

    // Work with array.
    for(int i = 0; i < 15; i++)
    {
        char * data = malloc(sizeof(char) * (i + 2));
        for(int j = 0; j < i + 1; j++)
        {
            data[j] = rand() % 26 + 65;
        }
        data[i + 1] = '\0';
        prependDynArray(array, data);
    }

    // Destroy it. Also it will print line of strings generated in the for loop.
    destroyDynArray(array, &function);

    // Create new array. But with ints now.
    array = createDynArray();

    for(int i = 0; i < 15; i++)
    {
        int * data = malloc(sizeof(int));
        * data = i;
        prependDynArray(array, data);
    }

    // Testing get.
    int * data = (int *) getDynArray(array, 5);
    assert(* data == 5);

    destroyDynArray(array, &functionInts);

    return 0;
}
