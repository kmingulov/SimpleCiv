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
    Copy the array.
*/
IntArray * iaCopy(IntArray * array);

/*
    Creates an array with length.
*/
IntArray * iaLengthCreate(int length);

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

/*
    Returns element #index.
*/
int iaGetByIndex(IntArray * array, int index);

/*
    Sets element #index value to value.
*/
void iaSetByIndex(IntArray * array, int index, int value);

/*
    Increment value of #index element by value.
*/
void iaIncrementByIndex(IntArray * array, int index, int value);

/*
    Returns first found positions of value in the array.
    Returns -1 if nothing found.
*/
int iaSearchForData(IntArray * array, int value);

#endif
