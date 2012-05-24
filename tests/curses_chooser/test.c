#include <stdio.h>
#include <curses.h>

#include "../../modules/widgets/curses_chooser.h"

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

    Chooser * chooser = createChooser(5, 5, r - 10, c - 10);
    getch();
    destroyChooser(chooser);

    endwin();
    return 0;
}
