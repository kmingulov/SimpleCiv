/*
    View module.
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

#ifndef VIEW
#define VIEW

// For name game
#define GAME_NAME "SimpleCiv"

#include <ncurses.h>
#include "../../modules/cell/cell.h"

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
    View struct, which contains general settings of view.
*/


typedef struct View
{
    // Number of rows and columns and distance between left edge of screen and
    // sidebar (in columns).
    int rows, columns, sidebar;
    // Cursor coordinates.
    int cur_r, cur_c;
} View;

/*
    Functions of initialization and deinitialization of View.
*/
View * createView();
void destroyView(View * view);

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
    Draws basic view. d is width of side bar.
*/
void drawView(View * view);


/*
    Draws map.
*/
void drawMap(Node * map, View * view);

#endif
