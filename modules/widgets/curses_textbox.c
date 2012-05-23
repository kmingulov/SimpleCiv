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

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <curses.h>

#include "curses_draws.h"
#include "curses_textbox.h"

Textbox * createTextbox(int start_r, int start_c, int r, int c)
{
    Textbox * textbox = malloc(sizeof(Textbox));

    textbox -> lines_per_page = r - TEXTBOX_BOTTOM_INDENT - TEXTBOX_TOP_INDENT - 2;
    textbox -> pages_count = 1;
    textbox -> current_page = 0;
    textbox -> lines = daCreate();
    textbox -> properties = iaCreate();
    textbox -> start_r = start_r;
    textbox -> start_c = start_c;
    textbox -> r = r;
    textbox -> c = c;

    return textbox;
}

void addEnter(Textbox * tb)
{
    // Add string.
    daPrepend(tb -> lines, NULL);
    iaPrepend(tb -> properties, 0);

    // Update pages count.
    tb -> pages_count = ceil((float) tb -> lines -> length / tb -> lines_per_page);
}

int addString(Textbox * tb, const char * format, ...)
{
    // Buffer and args list.
    va_list args;
    char buffer[1024];
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer) - 1, format, args);

    // Max string length. 2 for borders.
    int max_length = tb -> c - 2 - TEXTBOX_LEFT_INDENT - TEXTBOX_RIGHT_INDENT;

    // Split buffer to few strings.
    int index = 0;
    int count = 0;
    while(index < strlen(buffer))
    {
        // Allocate new string.
        char * s = malloc(sizeof(char) * (max_length + 1));

        // Copy string.
        memcpy(s, &buffer[index], max_length);
        s[max_length] = '\0';

        // Add to array.
        daPrepend(tb -> lines, s);
        iaPrepend(tb -> properties, 0);
        count += 1;

        // Go on.
        index += max_length;
    }

    // Update pages count.
    tb -> pages_count = ceil((float) tb -> lines -> length / tb -> lines_per_page);

    return count;
}

int addBoldString(Textbox * tb, const char * format, ...)
{
    // Args list.
    va_list args;
    va_start(args, format);

    // Add string.
    int count = addString(tb, format, args);

    // Make it bold!
    int start_i = tb -> properties -> length - count;
    for(int i = 0; i < count; i++)
    {
        tb -> properties -> data[start_i + i] = 1;
    }

    return count;
}

void drawTextbox(Textbox * tb)
{
    clearBlock(tb -> start_r, tb -> start_c, tb -> r, tb -> c);
    drawBox(tb -> start_r, tb -> start_c, tb -> r, tb -> c);

    int start_line = tb -> current_page * tb -> lines_per_page;
    int end_line = start_line + tb -> lines_per_page;

    int line = tb -> start_r + 1 + TEXTBOX_TOP_INDENT;
    for(int i = start_line; i < end_line; i++)
    {
        if(i < tb -> lines -> length)
        {
            char * t = (char *) daGetByIndex(tb -> lines, i);

            if(t != NULL)
            {
                int b = iaGetByIndex(tb -> properties, i);

                if(b) attron(A_BOLD);

                mvprintw(line++, tb -> start_c + 1 + TEXTBOX_LEFT_INDENT, t);

                if(b) attroff(A_BOLD);
            }
            else
            {
                line++;
            }
        }
    }
}

void destroyTextbox(Textbox * textbox)
{
    daDestroy(textbox -> lines, &free);
    iaDestroy(textbox -> properties);
    free(textbox);
}
