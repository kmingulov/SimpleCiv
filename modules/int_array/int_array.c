#include <stdlib.h>
#include <string.h>

#include "int_array.h"

IntArray * iaCreate()
{
    IntArray * array = malloc(sizeof(IntArray));

    array -> length = 0;
    array -> available = INT_ARRAY_INCREMENT;
    array -> data = malloc(sizeof(int) * array -> available);

    return array;
}

void iaDestroy(IntArray * array)
{
    free(array -> data);
    free(array);
}

void iaExpand(IntArray * array)
{
    // Expanding array.
    array -> available += INT_ARRAY_INCREMENT;
    // Allocating new memory.
    void * new_data = malloc(sizeof(int) * (array -> length + array -> available));
    // Coping old data.
    memcpy(new_data, array -> data, sizeof(int) * array -> length);
    // Deleting old data and remembering pointer.
    free(array -> data);
    array -> data = new_data;
}

void iaPrepend(IntArray * array, int n)
{
    if(array -> available == 0)
    {
        iaExpand(array);
    }

    array -> data[array -> length] = n;

    array -> available--;
    array -> length++;
}
