#ifndef CELL
#define CELL

#include "../../game/world/definitions.h"
#include "../graph/graph.h"

typedef struct Cell
{
    // Type of territory.
    unsigned char territory;
    // Resources.
    unsigned char resources;
    // TODO
    //      city
    //      units
} Cell;

/*
    Creates double circular row list from cells.
*/
Node * createRow(int l);

/*
    Merges two rows, created by createRow() function.
*/
void mergeRows(Node * n1, Node * n2);

/*
    Creates list with width w and height h.
*/
Node * createMap(int w, int h);

/*
    Destroys map.
*/
void destroyMap(Node * head);

#endif
