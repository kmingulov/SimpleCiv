#include "dyn_array.h"
#include <string.h>
#include <stdlib.h>

#define ARRAY_INCREMENT 5
#define SIZE            sizeof(int)

DynArray * daCreate()
{
    DynArray * array = malloc(sizeof(DynArray));

    array -> length = 0;
    array -> available = ARRAY_INCREMENT;
    array -> data = malloc(SIZE * array -> available);

    return array;
}

void daDestroy(DynArray * array, void (* deleteFunc)(void * data))
{
    for(int i = 0; i < array -> length; i++)
    {
        if(deleteFunc != NULL)
        {
            deleteFunc(array -> data[i]);
        }
    }

    free(array -> data);
    free(array);
}

void daIncrement(DynArray * array)
{
    if(array -> available == 0)
    {
        array -> available += ARRAY_INCREMENT;
        void ** new_data = malloc(SIZE * (array -> length + array -> available));
        memcpy(new_data, array -> data, SIZE * array -> length);
        free(array -> data);
        array -> data = new_data;
    }
}

void daPrepend(DynArray * array, void * data)
{
    daIncrement(array);

    array -> data[array -> length] = data;

    array -> available--;
    array -> length++;
}

void * daGetByIndex(DynArray * array, int index)
{
    // Max index = array -> length - 1. Index cannot be over max index.
    if(index > array -> length - 1 || index < 0)
    {
        return NULL;
    }

    return array -> data[index];
}

void * daGetLast(DynArray * array)
{
    return array -> data[array -> length - 1];
}

int daSearchForData(DynArray * array, void * data)
{
    int i;

    for(i = 0; i < array -> length; i++)
    {
        if(array -> data[i] == data)
        {
            break;
        }
    }

    if(i != array -> length)
    {
        return i;
    }

    return -1;
}

void daForEach(DynArray * array, void (* function)(int index, void * data))
{
    for(int i = 0; i < array -> length; i++)
    {
        function(i, array -> data[i]);
    }
}

int daRemoveByPointer(DynArray * array, void * data, void (* deleteFunc)(void * data))
{
    int index = 0;

    // Searching for data.
    // Max index = array -> length - 1, so index had to be less than max index.
    while(index <= array -> length - 1 && array -> data[index] != data)
    {
        index++;
    }

    // Nothing found.
    if(index == array -> length)
    {
        return 0;
    }

    // Deleting data.
    deleteFunc(array -> data[index]);

    // Moving all elements.
    for(int i = index; i < array -> length - 1; i++)
    {
        array -> data[i] = array -> data[i + 1];
    }
    array -> length--;
    array -> available++;

    // TODO: check, if array -> available > 5. daDecriment?

    // All done.
    return 1;
}
