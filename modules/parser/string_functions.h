#ifndef STRING_FUNCTIONS
#define STRING_FUNCTIONS

#include "../dyn_array/dyn_array.h"
#include "../int_array/int_array.h"

/*
    Trim all spaces (checked by isspace() function) at the begin and at the end
    of string.
*/
void strTrimSpaces(char * str);

/*
    Split string to DynArray by delimiter. Max length of each element is
    max_length (including 0-determinant).
*/
DynArray * strSplit(char delimiter, char * str, int max_length);

/*
    Split string to IntArray, converts each element to int by function.
*/
IntArray * strSplitAndConvert(char delimiter, char * str, int (* function)(char * data));

/*
    Split string to IntArray by delimiter (convertint each element to integer
    by atoi() function).
*/
IntArray * strSplitToInts(char delimiter, char * str);

#endif
