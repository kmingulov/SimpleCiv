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

    // Basic tests.
    assert(array -> length == 27);
    assert(array -> available == 3);

    // All done.
    iaDestroy(array);

    return 0;
}
