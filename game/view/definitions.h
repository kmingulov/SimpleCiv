#ifndef VIEW_DEFINITIONS
#define VIEW_DEFINITIONS

/*
    Key definitions.
*/
#undef  KEY_ENTER

#define KEY_ENTER                    10
#define KEY_SPACE                    32

/*
    View process definitions.
*/
#define VIEW_REDRAW_ALL              0
#define VIEW_REDRAW_INFO             1
#define VIEW_REDRAW_MAP              2
#define VIEW_REDRAW_TECH_DIALOG      4
#define VIEW_REDRAW_CITY_DIALOG      5

#define VIEW_MOVE_CURSOR_RIGHT       6
#define VIEW_MOVE_CURSOR_LEFT        7
#define VIEW_MOVE_CURSOR_TOP         8
#define VIEW_MOVE_CURSOR_BOTTOM      9

#define VIEW_MOVE_TECH_CURSOR_TOP    10
#define VIEW_MOVE_TECH_CURSOR_BOTTOM 11

#define VIEW_ESCAPE                  12

/*
    Interface definitions.
*/
#define SIDEBAR_PLAYER_BLOCK         2
#define SIDEBAR_CELL_BLOCK           11

#endif
