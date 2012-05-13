#ifndef CELL
#define CELL

#include "../graph/graph.h"

typedef struct Cell
{
    // Type of territory.
    unsigned char territory;
    // Resources.
    unsigned char resources;
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
    Creates map with max_r rows and max_c columns.
*/
Node * createMap(int max_r, int max_c);

/*
    Destroys map. This functions doesn't use destroyGraph() function.
    It's _highly_ recommended to use this function instead of destroyGraph().
    Reason is simple — map is symmetric. Computational complexity of this
    algorithm is O(N), of destroyGraph() algorithm — O(N²).
*/
void destroyMap(Node * map_head, int max_r, int max_c);

/*
    Gets cell in row r, column c (assumed that Node * map_head is (0,0) point).
*/
Node * getCell(Node * map_head, int r, int c);

#endif
