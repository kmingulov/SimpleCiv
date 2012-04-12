#ifndef DYN_ARRAY
#define DYN_ARRAY

#include <stdlib.h>

typedef struct DynArray
{
    int length;    // Length of dynamic array.
    int available; // How much elements we can add.
    void * data;   // Pointer to array.
} DynArray;

/*
    Returns created dynamic array.
*/
DynArray * createDynArray();

/*
    Destroy dynamic array.
*/
void destroyDynArray(DynArray * array, void (* function)(void * data));

/*
    Puts element in the end of array.
*/
void prependDynArray(DynArray * array, void * data);

/*
    Gets element by index.
*/
void * getDynArray(DynArray * array, int index);

#endif
