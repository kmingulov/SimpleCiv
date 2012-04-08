/*
    Console User Interface (CUI) module.
    It's important to remember difference in sequence (and their orientation)
    of axis between ncurses library and our map module.

          y                 c--------> columns
          ^                 |
          |                 |
          |                 |
    ------c------> x        |
          |                 |
          |                 | rows

      (our module)              (ncurses)

    So, then we do something with coordinates, we need change their order and
    change orientation of y axis.

    Ncurses has "memory leaks". Read more at:
    http://invisible-island.net/ncurses/ncurses.faq.html#config_leaks
*/

#ifndef CUI
#define CUI

#include <ncurses.h>
#include "../map/map.h"

/*
    Key definitions.
*/
#define KEY_ESCAPE 27

/*
    Functions of initialization and deinitialization of CUI.
*/
void initCUI();
void deinitCUI();

/*
    Put char into cell by her row and column (uses move and addch functions.)
*/
void maddch(int row, int column, int letter);

/*
    Put char string into the middle/right of row.
*/
void putInMiddle(int start_r, int start_c, int length, char * string);
void putInRight(int start_r, int start_c, int length, char * string);

/*
    Draws basic interface.
*/
void drawInterface(int rows, int columns, int d);

/*
    Draws map. Cell map will be in (start_row, start_column). Map we will draw
    until (end_row, end_column) point.
*/
void drawMap(Cell * map, int start_row, int start_column, int end_row, int end_column);

#endif
