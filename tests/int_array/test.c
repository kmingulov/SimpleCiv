#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../modules/int_array/int_array.h"
#include "../../modules/parser/string_functions.h"

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
    assert(array -> data[26] == 26);

    // All done.
    iaDestroy(array);

    // Test for strSplitToInts function.
    array = strSplitToInts('|', "12|42|652");
    assert(array -> data[0] == 12);
    assert(array -> data[1] == 42);
    assert(array -> data[2] == 652);
    iaDestroy(array);

    return 0;
}
