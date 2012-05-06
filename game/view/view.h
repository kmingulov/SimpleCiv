/*
    View module.

    Ncurses has "memory leaks". Read more at:
    http://invisible-island.net/ncurses/ncurses.faq.html#config_leaks
*/

#ifndef MODULE_VIEW
#define MODULE_VIEW

// For name game
#define GAME_NAME "SimpleCiv"

#include <ncurses.h>

#include "definitions.h"
#include "../../modules/cell/cell.h"
#include "../world/world.h"
#include "../message/message.h"

/*
    Key definitions.
*/
#define KEY_ESCAPE 27

/*
    View struct, which contains general settings of view.
*/

typedef struct View
{
    // Number of rows and columns and distance between left edge of screen and
    // sidebar (in columns).
    int rows, columns, sidebar;
    // Cursor coordinates (in the ncurses).
    int cur_r, cur_c;
    // Cursor coordinates (in the world).
    int map_r, map_c;
    // Current cell.
    Node * current_cell;
} View;

/*
    Functions of initialization and deinitialization of View.
*/
View * createView(World * world);
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
void drawView(World * world, View * view);

/*
    Draws info.
*/
void drawInfo(World * world, View * view);

/*
    Draws map.
*/
void drawMap(World * world, View * view);

/*
    Event handling.
*/
void viewProcess(World * world, View * view, Message * message);

#endif
