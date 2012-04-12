#include "dyn_array.h"
#include <string.h>
#include <stdio.h>

#define ARRAY_INCREMENT 10
#define SIZE            sizeof(int)

DynArray * createDynArray()
{
    DynArray * array = malloc(sizeof(DynArray));

    array -> length = 0;
    array -> available = ARRAY_INCREMENT;
    array -> data = malloc(SIZE * array -> available);

    return array;
}

void destroyDynArray(DynArray * array, void (* function)(void * data))
{
    for(int i = 0; i < array -> length; i++)
    {
        int * destination = (int *)((int) array -> data + SIZE * i);
        function((void *)(* destination));
    }

    free(array -> data);
    free(array);
}

void incrementDynArray(DynArray * array)
{
    if(array -> available == 0)
    {
        array -> available += ARRAY_INCREMENT;
        void * new_data = malloc(SIZE * (array -> length + array -> available));
        memcpy(new_data, array -> data, SIZE * array -> length);
        free(array -> data);
        array -> data = new_data;
    }
}

void prependDynArray(DynArray * array, void * data)
{
    incrementDynArray(array);

    int * destination = (int *)((int) array -> data + SIZE * array -> length);
    * destination = (int) data;

    array -> available--;
    array -> length++;
}

void * getDynArray(DynArray * array, int index)
{
    int * destination = (int *)((int) array -> data + SIZE * index);
    return (void *) * destination;
}
