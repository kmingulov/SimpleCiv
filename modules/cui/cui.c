#include <stdlib.h>
#include <string.h>
#include "cui.h"

Interface createInterface()
{
    Interface result;

    getmaxyx(stdscr, result.rows, result.columns);

    result.sidebar = 0.85 * result.columns;
    result.cur_r = result.rows / 2;
    result.cur_c = result.sidebar / 2;

    return result;
}

void initCUI()
{
    // Initialize ncurses.
    initscr();
    raw();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    start_color();

    // Color pairs. 0 — default, 1-5 — territories' colors.
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLUE,  COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
}

void deinitCUI()
{
    endwin();
}

void moveCursor(int key, Interface * iface, Cell ** map)
{
    // TODO Rewrite it more compactly?
    if(key == KEY_UP)
    {
        if(iface -> cur_r > 5) iface -> cur_r--;
        else
        {
            * map = (* map) -> top;
            drawMap(* map, iface);
        }
    } else if(key == KEY_DOWN)
    {
        if(iface -> cur_r < iface -> rows - 6) iface -> cur_r++;
        else
        {
            * map = (* map) -> bottom;
            drawMap(* map, iface);
        }
    } else if(key == KEY_LEFT)
    {
        if(iface -> cur_c > 5) iface -> cur_c--;
        else
        {
            * map = (* map) -> left;
            drawMap(* map, iface);
        }
    } else if(key == KEY_RIGHT)
    {
        if(iface -> cur_c < iface -> sidebar - 5) iface -> cur_c++;
        else
        {
            * map = (* map) -> right;
            drawMap(* map, iface);
        }
    }
}

void drawInterface(Interface * iface)
{
    // Copying rows, columns and sidebar.
    int r = iface -> rows;
    int c = iface -> columns;
    int s = iface -> sidebar;

    attron(COLOR_PAIR(0));

    // Drawing main lines.
    for(int i = 1; i < c; i++)
    {
        maddch(0, i, ACS_HLINE);
        maddch(r - 1, i, ACS_HLINE);
        if(i > s && i < c - 1)
        {
            maddch(PLAYER_START, i, ACS_HLINE);
            maddch(INFO_START, i, ACS_HLINE);
            maddch(r - 4, i, ACS_HLINE);
        }
    }

    for(int i = 1; i < r - 1; i++)
    {
        maddch(i, s, ACS_VLINE);
        maddch(i, 0, ACS_VLINE);
        maddch(i, c - 1, ACS_VLINE);
    }

    // Corners.
    maddch(0, 0, ACS_ULCORNER);
    maddch(r - 1, 0, ACS_LLCORNER);
    maddch(0, c - 1, ACS_URCORNER);
    maddch(r - 1, c - 1, ACS_LRCORNER);
    maddch(0, s, ACS_TTEE);
    maddch(r - 1, s, ACS_BTEE);

    // Project name.
    putInMiddle(1, s + 1, c - s - 2, "%%projectname%%");

    // Player info.
    maddch(PLAYER_START, s, ACS_LTEE); maddch(PLAYER_START, c - 1, ACS_RTEE);
    putInMiddle(PLAYER_START + 1, s + 1, c - s - 2, "Player");

    // Territory info
    maddch(INFO_START, s, ACS_LTEE); maddch(INFO_START, c - 1, ACS_RTEE);
    putInMiddle(INFO_START + 1, s + 1, c - s - 2, "Information");

    // Hints.
    maddch(r - 4, s, ACS_LTEE); maddch(r - 4, c - 1, ACS_RTEE);
    mvprintw(r - 3, s + 1, "ESC   Quit");
    mvprintw(r - 2, s + 1, "ENTER End turn");

    attroff(COLOR_PAIR(0));
}

void drawCellInfo(Cell * cell, Interface * iface)
{    
    int s = iface -> sidebar;

    // TODO Check: player knows this territory or no, knows resources on this
    //      territory.
    //      Add resources and cities.

    // Auxiliary array.
    char territories[5][9] = {"Water   ", "Grass   ", "Hill    ", "Forest  ", "Mountain"};

    // Territory type.
    if(cell -> territory <= 4 && cell -> territory >= 0)
    {
        mvprintw(INFO_START + 2, s + 1, "%s", territories[cell -> territory]);
    }
    else
    {
        mvprintw(INFO_START + 2, s + 1, "Unknown ");
    }
}

void drawMap(Cell * map, Interface * iface)
{
    int start_row = 1,    end_row = iface -> rows - 2;
    int start_column = 1, end_column = iface -> sidebar - 1;

    Cell * current = map;
    Cell * line = map;

    attron(A_BOLD);

    for(int i = start_row; i <= end_row; i++)
    {
        for(int j = start_column; j <= end_column; j++)
        {
            int type = current -> territory;
            move(i, j);

            attron(COLOR_PAIR(type + 1));
            if(type == 0) printw(".");
            else if(type == 1) printw("_");
            else if(type == 2) printw("-");
            else if(type == 3) printw("T");
            else if(type == 4) printw("^");
            attroff(COLOR_PAIR(type + 1));

            current = current -> right;
        }
        line = line -> bottom;
        current = line;
    }

    attroff(A_BOLD);
}
