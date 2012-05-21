/*

    SimpleCiv is simple clone of Civilization game, using ncurses library.
    Copyright (C) 2012 by K. Mingulov, A. Sapronov.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <curses.h>

#include "draw_functions.h"

void clearBlock(int start_r, int start_c, int r, int c)
{
    for(int i = start_r; i < start_r + r; i++)
    {
        for(int j = start_c; j< start_c + c; j++)
        {
            mvaddch(i, j, ' ');
        }
    }
}

void drawBox(int start_r, int start_c, int r, int c)
{
    for(int i = start_c + 1; i < start_c + c - 1; i++)
    {
        mvaddch(start_r,         i, ACS_HLINE);
        mvaddch(start_r + r - 1, i, ACS_HLINE);
    }

    for(int i = start_r + 1; i < start_r + r - 1; i++)
    {
        mvaddch(i, start_c,         ACS_VLINE);
        mvaddch(i, start_c + c - 1, ACS_VLINE);
    }

    mvaddch(start_r,         start_c,         ACS_ULCORNER);
    mvaddch(start_r + r - 1, start_c,         ACS_LLCORNER);
    mvaddch(start_r,         start_c + c - 1, ACS_URCORNER);
    mvaddch(start_r + r - 1, start_c + c - 1, ACS_LRCORNER);
}

void drawVertLine(int start_r, int r, int c)
{
    for(int i = start_r + 1; i < start_r + r - 1; i++)
    {
        mvaddch(i, c, ACS_VLINE);
    }

    mvaddch(start_r,         c, ACS_TTEE);
    mvaddch(start_r + r - 1, c, ACS_BTEE);
}

void drawHorizLine(int start_c, int c, int r)
{
    for(int i = start_c + 1; i < start_c + c - 1; i++)
    {
        mvaddch(r, i, ACS_HLINE);
    }

    mvaddch(r, start_c,         ACS_LTEE);
    mvaddch(r, start_c + c - 1, ACS_RTEE);
}

void putInMiddle(int start_r, int start_c, int length, const char * format, ...)
{
    // Preparing buffer string.
    va_list args;
    char buffer[1024];

    va_start(args, format);

    vsnprintf(buffer, sizeof(buffer) - 1, format, args);

    // Printing a piece of string.
    int delta = length - strlen(buffer);

    char * s = malloc(sizeof(char) * length);
    strcpy(s, buffer);

    if(delta < 0)
    {
        s[length] = '\0';
        delta = 0;
    }

    delta = floor((float) delta / 2);
    mvprintw(start_r, start_c + delta, s);
    free(s);
}

void putInLeft(int start_r, int start_c, int length, const char * format, ...)
{
    va_list args;
    char buffer[1024];

    va_start(args, format);

    vsnprintf(buffer, sizeof(buffer) - 1, format, args);

    if(strlen(buffer) > length)
    {
        buffer[length] = '\0';
    }

    mvprintw(start_r, start_c, buffer);

    refresh();
}

void putInRight(int start_r, int start_c, int length, const char * format, ...)
{
    va_list args;
    char buffer[1024];

    va_start(args, format);

    vsnprintf(buffer, sizeof(buffer) - 1, format, args);

    if(strlen(buffer) > length)
    {
        buffer[length] = '\0';
    }

    mvprintw(start_r, start_c + length - strlen(buffer), buffer);

    refresh();
}
