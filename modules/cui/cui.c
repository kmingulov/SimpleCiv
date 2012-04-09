#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "cui.h"

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

void maddch(int row, int column, int letter)
{
    move(row, column);
    addch(letter);
    refresh();
}

void putInMiddle(int start_r, int start_c, int length, char * string)
{
    int delta = length - strlen(string);

    char * s = malloc(sizeof(char) * length);
    strcpy(s, string);

    if(delta < 0)
    {
        s[length] = '\0';
        delta = 0;
    }

    delta = floor((float) delta / 2);
    mvprintw(start_r, start_c + delta, "%s", s);
    free(s);
}

void putInRight(int start_r, int start_c, int length, char * string)
{
    mvprintw(start_r, start_c + length - strlen(string), "%s", string);
}

void moveCursor(int key, int w, int d, Cell ** map, int * cur_x, int * cur_y)
{
    // TODO Rewrite it more compactly?
    if(key == KEY_UP)
    {
        if(* cur_x > 5) (* cur_x)--;
        else
        {
            * map = (* map) -> top;
            drawMap(* map, 1, 1, w - 2, d - 1);
        }
    } else if(key == KEY_DOWN)
    {
        if(* cur_x < w - 6) (* cur_x)++;
        else
        {
            * map = (* map) -> bottom;
            drawMap(* map, 1, 1, w - 2, d - 1);
        }
    } else if(key == KEY_LEFT)
    {
        if(* cur_y > 5) (* cur_y)--;
        else
        {
            * map = (* map) -> left;
            drawMap(* map, 1, 1, w - 2, d - 1);
        }
    } else if(key == KEY_RIGHT)
    {
        if(* cur_y < d - 5) (* cur_y)++;
        else
        {
            * map = (* map) -> right;
            drawMap(* map, 1, 1, w - 2, d - 1);
        }
    }
}

void drawInterface(int rows, int columns, int d)
{
	attron(COLOR_PAIR(0));

    // Drawing main lines.
    for(int i = 1; i < columns; i++)
    {
        maddch(0, i, ACS_HLINE);
        maddch(rows - 1, i, ACS_HLINE);
        if(i > d && i < columns - 1)
        {
            maddch(2, i, ACS_HLINE);
            maddch(10, i, ACS_HLINE);
            maddch(rows - 4, i, ACS_HLINE);
        }
    }

    for(int i = 1; i < rows - 1; i++)
    {
        maddch(i, d, ACS_VLINE);
        maddch(i, 0, ACS_VLINE);
        maddch(i, columns - 1, ACS_VLINE);
    }

    // Corners.
    maddch(0, 0, ACS_ULCORNER);
    maddch(rows - 1, 0, ACS_LLCORNER);
    maddch(0, columns - 1, ACS_URCORNER);
    maddch(rows - 1, columns - 1, ACS_LRCORNER);
    maddch(0, d, ACS_TTEE);
    maddch(rows - 1, d, ACS_BTEE);

    // Project name.
    putInMiddle(1, d + 1, columns - d - 2, "%%projectname%%");
    maddch(2, d, ACS_LTEE); maddch(2, columns - 1, ACS_RTEE);

    // Current player.
    /*putInMiddle(3, d + 1, columns - d - 2, "%%playername%%");
    mvprintw(5, d + 1, "Gold");
    putInRight(5, d + 1, columns - d - 2, "100");
    mvprintw(7, d + 1, "Science", 51);
    putInRight(8, d + 1, columns - d - 2, "%%technology%%");
    mvprintw(9, d + 1, "==============>    ", 51);*/

    // Information block.
    maddch(10, d, ACS_LTEE); maddch(10, columns - 1, ACS_RTEE);
    /*putInMiddle(11, d + 1, columns - d - 2, "Information");
    mvprintw(12, d + 1, "Territory");
    putInRight(12, d + 1, columns - d - 2, "-");
    mvprintw(13, d + 1, "Resources");
    putInRight(13, d + 1, columns - d - 2, "-");
    mvprintw(14, d + 1, "City");
    putInRight(14, d + 1, columns - d - 2, "-");*/

    // Hints.
    maddch(rows - 4, d, ACS_LTEE); maddch(rows - 4, columns - 1, ACS_RTEE);
    mvprintw(rows - 3, d + 1, "ESC   Quit");
    mvprintw(rows - 2, d + 1, "ENTER End turn");

	attroff(COLOR_PAIR(0));
}

void identifyCell(Cell * c, int h, int d)
{
    // Auxiliary array.
    char territories[5][9] = {"   Water", "   Grass", "    Hill", "  Forest", "Mountain"};
    if(c -> territory <= 4 && c -> territory >= 0)
    {
        // TODO Damn. Rewrite!
        mvprintw(12, (d + 1) + (h - d - 2) - 8, "%s", territories[c -> territory]);
        //putInRight(12, d + 1, h - d - 2, territories[c -> territory]);
    }
    else
    {
        // Something goes wrong…
    }
}

void drawMap(Cell * map, int start_row, int start_column, int end_row, int end_column)
{
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
