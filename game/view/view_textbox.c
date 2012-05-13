#include <stdlib.h>
#include <string.h>
#include <curses.h>

#include "draw_functions.h"
#include "view_textbox.h"

ViewTextbox * createViewTextbox(int r, int c, int lines_per_page)
{
    ViewTextbox * textbox = malloc(sizeof(ViewTextbox));

    textbox -> lines_per_page = lines_per_page;
    textbox -> current_page = 0;
    textbox -> lines = daCreate();
    textbox -> properties = iaCreate();
    textbox -> r = r;
    textbox -> c = c;

    return textbox;
}

void addString(ViewTextbox * tb, char * string, int bold)
{
    char * s = malloc(sizeof(char) * (tb -> c - 4));
    daPrepend(tb -> lines, strcpy(s, string));
    iaPrepend(tb -> properties, bold);
}

void drawViewTextbox(ViewTextbox * tb)
{
    erase();
    drawBox(0, 0, tb -> r, tb -> c);

    int start_line = tb -> current_page * tb -> lines_per_page;
    int end_line = start_line + tb -> lines_per_page;

    int line = 2;
    for(int i = start_line; i < end_line; i++)
    {
        if(i < tb -> lines -> length)
        {
            char * t = (char *) daGetByIndex(tb -> lines, i);
            int b = iaGetByIndex(tb -> properties, i);

            if(b) attron(A_BOLD);

            mvprintw(line++, 3, t);

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
