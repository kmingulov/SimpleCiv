#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <curses.h>

#include "draw_functions.h"
#include "view_textbox.h"

ViewTextbox * createViewTextbox(int start_r, int start_c, int r, int c)
{
    ViewTextbox * textbox = malloc(sizeof(ViewTextbox));

    textbox -> lines_per_page = r - 4;
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

void addString(ViewTextbox * tb, const char * format, ...)
{
    // Buffer and args list.
    va_list args;
    char buffer[1024];
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer) - 1, format, args);

    // Cut buffer.
    buffer[tb -> c - 5] = '\0';

    // Add string.
    char * s = malloc(sizeof(char) * (tb -> c - 4));
    daPrepend(tb -> lines, strcpy(s, &buffer[0]));
    iaPrepend(tb -> properties, 0);
    tb -> pages_count = ceil((float) tb -> lines -> length / tb -> lines_per_page);
}

void addBoldString(ViewTextbox * tb, const char * format, ...)
{
    // Args list.
    va_list args;
    va_start(args, format);

    // Add string.
    addString(tb, format, args);

    // Make it bold!
    tb -> properties -> data[tb -> properties -> length - 1] = 1;
}

void drawViewTextbox(ViewTextbox * tb)
{
    clearBlock(tb -> start_r, tb -> start_c, tb -> r, tb -> c);
    drawBox(tb -> start_r, tb -> start_c, tb -> r, tb -> c);

    int start_line = tb -> current_page * tb -> lines_per_page;
    int end_line = start_line + tb -> lines_per_page;

    int line = tb -> start_r + 2;
    for(int i = start_line; i < end_line; i++)
    {
        if(i < tb -> lines -> length)
        {
            char * t = (char *) daGetByIndex(tb -> lines, i);
            int b = iaGetByIndex(tb -> properties, i);

            if(b) attron(A_BOLD);

            mvprintw(line++, tb -> start_c + 3, t);

            if(b) attroff(A_BOLD);
        }
    }
}

void destroyViewTextbox(ViewTextbox * textbox)
{
    daDestroy(textbox -> lines, &free);
    iaDestroy(textbox -> properties);
    free(textbox);
}
