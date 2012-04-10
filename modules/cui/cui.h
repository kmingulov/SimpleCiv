/*
    Console User Interface (CUI) module.
    It's important to remember difference in sequence (and their orientation)
    of axis between ncurses library and our map module.

          y                 0--------> columns
          ^                 |
          |                 |
          |                 |
    ------0------> x        |
          |                 |
          |                 | rows

      (our module)              (ncurses)

    So, then we do something with coordinates, we need change their order and
    change orientation of y axis.

    Ncurses has "memory leaks". Read more at:
    http://invisible-island.net/ncurses/ncurses.faq.html#config_leaks

    TODO
        Line 62: maybe rewrite it more compactly? Or not?
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
    Constants.
*/
#define PLAYER_START 2
#define INFO_START 10

/*
    Interface struct, which contains general settings of interface.
*/
typedef struct Interface
{
    // Number of rows and columns and distance between left edge of screen and 
    // sidebar (in columns).
    int rows, columns, sidebar;
    // Cursor coordinates.
    int cur_r, cur_c;
} Interface;

/*
    Creates interface struct variable.
*/
Interface createInterface();

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
    Moves cursor.
*/
void moveCursor(int key, Interface * iface, Cell ** map);

/*
    Draws basic interface. d is width of side bar.
*/
void drawInterface(Interface * iface);

/*
    Prints territory info into side bar.
*/
void drawCellInfo(Cell * cell, Interface * iface);

/*
    Draws map.
*/
void drawMap(Cell * map, Interface * iface);

#endif
