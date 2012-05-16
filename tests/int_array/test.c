#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../modules/int_array/int_array.h"

int main()
{
    IntArray * array = iaCreate();

    // Creating an array.
    for(int i = 0; i < 27; i++)
    {
        iaPrepend(array, i);
    }

    // Test copy.
    IntArray * copy = iaCopy(array);
    assert(iaGetByIndex(copy, 7) == 7);
    iaDestroy(copy);

    // Basic tests.
    assert(array -> length == 27);
    assert(array -> available == 3);
    assert(array -> data[26] == 26);
    iaIncrementByIndex(array, 0, 1);
    assert(array -> data[0] == 1);
    assert(iaGetByIndex(array, 7) == 7);
    assert(iaSearchForData(array, 100) == -1);
    iaDestroy(array);

    // Test for iaLengthCreate().
    array = iaLengthCreate(3);
    assert(array -> length == 3);
    assert(array -> data[0] == 0);
    assert(array -> data[1] == 0);
    assert(array -> data[2] == 0);
    iaDestroy(array);
    
    return 0;
}
