#include <curses.h>

#include "../../game/view/view_textbox.h"

int main()
{
    // Initialize ncurses.
    initscr();
    raw();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    start_color();
    attroff(A_BOLD);

    int r, c;
    getmaxyx(stdscr, r, c);

    ViewTextbox * vtb = createViewTextbox(r, c, 5);
    addString(vtb, "Hello.", 1);
    addString(vtb, "", 0);
    addString(vtb, "This is a textbox.", 0);
    addString(vtb, "You can put any information there.", 0);
    addString(vtb, "(Also there is a scrolling function.)", 0);
    drawViewTextbox(vtb);
    getch();

    destroyViewTextbox(vtb);
    endwin();
    return 0;
}
