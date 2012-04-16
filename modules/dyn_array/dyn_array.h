#ifndef DYN_ARRAY
#define DYN_ARRAY

#include <stdlib.h>

typedef struct DynArray
{
    int length;    // Length of dynamic array.
    int available; // How much elements we can add.
    void ** data;  // Array of pointers.
} DynArray;

/*
    Returns created dynamic array.
*/
DynArray * daCreate();

/*
    Destroy dynamic array. deleteFunc is deletion (for data) function.
*/
void daDestroy(DynArray * array, void (* deleteFunc)(void * data));

/*
    Puts element in the end of array.
*/
void daPrepend(DynArray * array, void * data);

/*
    Gets element by index.
*/
void * daGetByIndex(DynArray * array, int index);

/*
    Executes function for each element in array.
*/
void daForEach(DynArray * array, void (* function)(int index, void * data));

/*
    Removes _first_ element pointer data. Will return 0, if nothing found, 
    and 1, if element succefully removed. deleteFunc is deletion (for data)
    function.
*/
int daRemoveByPointer(DynArray * array, void * data, void (* deleteFunc)(void * data));

#endif
