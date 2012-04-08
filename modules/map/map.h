#ifndef MAP
#define MAP

typedef struct Cell
{
    // Neighboors of this cell.
    struct Cell * left, * right, * top, * bottom;
    // Type of territory.
    char territory;
    // TODO: resources
    //       city and buildings
    //       units
} Cell;

/*
    Creates double circular row list.
*/
Cell * createRow(int l);

/*
    Merges tho rows.
*/
void mergeRows(Cell * c1, Cell * c2);

/*
    Creates list with width w and height h.
*/
Cell * createMap(int w, int h);

/*
    Destroys row.
*/
void destroyRow(Cell * row);

/*
    Destroys map.
*/
void destroyMap(Cell * head);

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
char isWhereCell(Cell * c, char t);

#endif
