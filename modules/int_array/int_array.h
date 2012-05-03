#ifndef INT_ARRAY
#define INT_ARRAY

#define INT_ARRAY_INCREMENT 5

/*
    This struct seems like a DynArray struct. But DynArray uses pointers to
    data, this is just a dynamical array of ints!
*/
typedef struct IntArray
{
    int length;    // Length of dynamic array.
    int available; // How much elements we can add.
    int * data;    // Data.
} IntArray;

/*
    Creates array.
*/
IntArray * iaCreate();

/*
    Destroys array.
*/
void iaDestroy(IntArray * array);

/*
    Expands array with another INT_ARRAY_INCREMENT elements.
*/
void iaExpand(IntArray * array);

/*
    Adds n to the array.
*/
void iaPrepend(IntArray * array, int n);

#endif
