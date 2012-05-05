#ifndef LIST
#define LIST

/*
    Struct of element of cycle list.
*/
typedef struct ListElement
{
    void * data;
    struct ListElement * next, * prev;
} ListElement;

/*
    Struct of list.
*/
typedef struct List
{
    int length;
    ListElement * head;
} List;

/*
    Creates list.
*/
List * listCreate();

/*
    Destroys list. Function is function for data deletion.
*/
void listDestroy(List * list, void (* function)(void * data));

/*
    Adds data to the end of the list (before head).
*/
void listPrepend(List * list, void * data);

/*
    Returns n-th (away from head) element.
*/
void * listGetByN(List * list, int n);

#endif
