/*
    View module.

    Ncurses has "memory leaks". Read more at:
    http://invisible-island.net/ncurses/ncurses.faq.html#config_leaks
*/

#ifndef MODULE_VIEW
#define MODULE_VIEW

// For name game
#define GAME_NAME "SimpleCiv"

#include <curses.h>

#include "definitions.h"
#include "../../modules/cell/cell.h"
#include "../../modules/list/list.h"
#include "../world/world.h"
#include "../message/message.h"

/*
    View struct, which contains general settings of view.
*/

typedef struct ViewChooser
{
    // Array of ids.
    IntArray * ids;
    // Current id.
    int current;
    // First row of the list with items.
    int start_r;
} ViewChooser;

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
    // Current chooser.
    ViewChooser * chooser;
} View;

/*
    Functions of initialization and deinitialization of View.
*/
View * createView(World * world);
void destroyView(View * view);

/*
    Functions of creation and destruction chooser.
*/
ViewChooser * createTechChooser(World * world);
ViewChooser * createUnitChooser(World * world);
void destroyChooser(ViewChooser * chooser);

/*
    Put char string into the middle/right/left of row. Syntax is similar to
    printf function.
    TODO Add to putInMiddle/putInRight functions check for strlen(buffer) >
    length (string too long).
*/
void putInMiddle(int start_r, int start_c, int length, const char * format, ...);
void putInRight(int start_r, int start_c, int length, const char * format, ...);
void putInLeft(int start_r, int start_c, int length, const char * format, ...);

/*
    Draws basic view (for map).
*/
void drawGeneralView(World * world, View * view);

/*
    Draws tech view.
*/
void drawTechView(World * world, View * view);

/*
    Draws tech view.
*/
void drawCityView(World * world, View * view);


/*
    Clears block from (start_r,start_c) to (start_r+r,start_c+c) point.
*/
void clearBlock(int start_r, int start_c, int r, int c);

/*
    Draws player info.
*/
void drawPlayerInfo(World * world, View * view);

/*
    Draws cell info.
*/
void drawCellInfo(World * world, View * view);

/*
    Draws map.
*/
void drawMap(World * world, View * view);

/*
    Event handling. Returns 0 if game need to terminate, else 1.
*/
int viewProcess(World * world, View * view, List * list);

#endif
