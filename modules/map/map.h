#ifndef MAP
#define MAP

/*
    Module of circular linked list. We use it to create our map.

    TODO:
          add some data in struct
          rewrite createMap function
*/

typedef struct Cell
{
    // Neighboors of this cell.
    struct Cell * left, * right, * top, * bottom;
    char territory;
    // TODO: resources 00000000
    //       type of territory
    //       city and buildings
    //       units
} Cell;

/*
    Create list with width w and height h.
*/
Cell * createMap(int w, int h);

/*
    Destroy list.
*/
void destroyMap(Cell * head, int w, int h);

/*
    Get a cell in offset_x by x and in offset_y by y coordinate from cell c.
*/
Cell * getCell(Cell * c, int offset_x, int offset_y);

/*
    Get a left, right, top and bottom neighboors of this cell.
*/
Cell * getLeft(Cell * c);
Cell * getRight(Cell * c);
Cell * getTop(Cell * c);
Cell * getBottom(Cell * c);

/*
    Get cell by a number: top — 0, right — 1, bottom — 2, left — 3.
*/
Cell * getCellByNumber(Cell * c, int i);

/*
    Returns 1, if one of neighboors have territory == t.
    Returns zero, if no one found.
*/
char isWhereCell(Cell * c, int t);

#endif
