#include <string.h>
#include <stdlib.h>
#include <math.h>


#include "view.h"

#include "../../modules/graph/graph.h"
#include "../../modules/player/player.h"
#include "../../modules/city/city.h"
#include "../../modules/unit/unit.h"
#include "../world/definitions.h"



View * createView(World * world)
{
    View * result = malloc(sizeof(View));

    // Initialize ncurses.
    initscr();
    raw();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    start_color();

    // Color pairs. 0 — default, 1-5 — territories' colors.
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(CELL_TYPE_WATER, COLOR_BLUE,  COLOR_BLACK);
    init_pair(CELL_TYPE_GRASS, COLOR_GREEN, COLOR_BLACK);
    init_pair(CELL_TYPE_HILL, COLOR_WHITE, COLOR_BLACK);
    init_pair(CELL_TYPE_TREE, COLOR_GREEN, COLOR_BLACK);
    init_pair(CELL_TYPE_MOUNTAIN, COLOR_WHITE, COLOR_BLACK);

    getmaxyx(stdscr, result -> rows, result -> columns);

    result -> sidebar = 0.85 * result -> columns;
    result -> cur_r = result -> rows / 2;
    result -> cur_c = result -> sidebar / 2;
    result -> map_r = result -> cur_r - 1;
    result -> map_c = result -> cur_c - 1;
    result -> current_cell = getCell(world -> graph_map, result -> map_r, result -> map_c);

    return result;
}

void destroyView(View * view)
{
    endwin();
    free(view);
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

void drawView(World * world, View * view)
{
    // Copying rows, columns and sidebar.
    int r = view -> rows;
    int c = view -> columns;
    int s = view -> sidebar;

    attron(COLOR_PAIR(0));

    // Drawing main lines.
    for(int i = 1; i < c; i++)
    {
        maddch(0, i, ACS_HLINE);
        maddch(r - 1, i, ACS_HLINE);
        if(i > s && i < c - 1)
        {
            maddch(SIDEBAR_PLAYER_BLOCK, i, ACS_HLINE);
            maddch(SIDEBAR_CELL_BLOCK, i, ACS_HLINE);
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
    putInMiddle(1, s + 1, c - s - 2, GAME_NAME);

    maddch(SIDEBAR_PLAYER_BLOCK, s, ACS_LTEE); maddch(SIDEBAR_PLAYER_BLOCK, c - 1, ACS_RTEE);
    maddch(SIDEBAR_CELL_BLOCK, s, ACS_LTEE); maddch(SIDEBAR_CELL_BLOCK, c - 1, ACS_RTEE);

    attroff(COLOR_PAIR(0));
}

void drawInfo(World * world, View * view)
{
    // Copying rows, columns and sidebar.
    int r = view -> rows;
    //int c = view -> columns;
    int s = view -> sidebar;

    Player * player = (Player *) world -> graph_players -> data;

    // Player info.
    mvprintw(SIDEBAR_PLAYER_BLOCK + 1, s + 1, "%s", player -> name);
    mvprintw(SIDEBAR_PLAYER_BLOCK + 2, s + 1, "%d gold", player -> gold);

    // Cell info.
    // Type of territory.
    Cell * c = (Cell *) view -> current_cell -> data;
    switch(c -> territory)
    {
        case CELL_TYPE_WATER:    mvprintw(SIDEBAR_CELL_BLOCK + 1, s + 1, "Water    "); break;
        case CELL_TYPE_GRASS:    mvprintw(SIDEBAR_CELL_BLOCK + 1, s + 1, "Grass    "); break;
        case CELL_TYPE_TREE:     mvprintw(SIDEBAR_CELL_BLOCK + 1, s + 1, "Forest   "); break;
        case CELL_TYPE_HILL:     mvprintw(SIDEBAR_CELL_BLOCK + 1, s + 1, "Hill     "); break;
        case CELL_TYPE_MOUNTAIN: mvprintw(SIDEBAR_CELL_BLOCK + 1, s + 1, "Mountains"); break;
    }
    // Resources.
    attron(A_BOLD);
    switch(c -> resources)
    {
        case CELL_RES_NONE:      mvprintw(SIDEBAR_CELL_BLOCK + 2, s + 1, "            "); break;
        case CELL_RES_BRONZE:    mvprintw(SIDEBAR_CELL_BLOCK + 2, s + 1, "Bronze      "); break;
        case CELL_RES_IRON:      mvprintw(SIDEBAR_CELL_BLOCK + 2, s + 1, "Iron        "); break;
        case CELL_RES_COAL:      mvprintw(SIDEBAR_CELL_BLOCK + 2, s + 1, "Coal        "); break;
        case CELL_RES_GUNPOWDER: mvprintw(SIDEBAR_CELL_BLOCK + 2, s + 1, "Gunpowder   "); break;
        case CELL_RES_HORSES:    mvprintw(SIDEBAR_CELL_BLOCK + 2, s + 1, "Horses      "); break;
    }
    attroff(A_BOLD);
    // City.
    Node * city = getNeighbour(view -> current_cell, EDGE_CELL_CITY);
    if(city != NULL)
    {
        City * c = (City *) city -> data;
        attron(A_BOLD); mvprintw(SIDEBAR_CELL_BLOCK + 3, s + 1, "City:  "); attroff(A_BOLD);
        mvprintw(SIDEBAR_CELL_BLOCK + 4, s + 1, " %s", c -> name);
        mvprintw(SIDEBAR_CELL_BLOCK + 5, s + 1, " %s", c -> owner -> name);
        mvprintw(SIDEBAR_CELL_BLOCK + 6, s + 1, " %d people", c -> population);
    }
    else
    {
        mvprintw(SIDEBAR_CELL_BLOCK + 3, s + 1, "             ");
        mvprintw(SIDEBAR_CELL_BLOCK + 4, s + 1, "             ");
        mvprintw(SIDEBAR_CELL_BLOCK + 5, s + 1, "             ");
        mvprintw(SIDEBAR_CELL_BLOCK + 6, s + 1, "             ");
    }
    // Units info.
    Node * unit = getNeighbour(view -> current_cell, EDGE_CELL_UNIT);
    if(unit != NULL)
    {
        Unit * u = (Unit *) unit -> data;
        UnitCommonInfo * u_info = (UnitCommonInfo *) daGetByIndex(world -> units_info, u -> unit_id);
        attron(A_BOLD); mvprintw(SIDEBAR_CELL_BLOCK + 7, s + 1, "Unit:  "); attroff(A_BOLD);
        mvprintw(SIDEBAR_CELL_BLOCK + 8, s + 1, " %s", u_info -> name);
        mvprintw(SIDEBAR_CELL_BLOCK + 9, s + 1, " %s", u -> owner -> name);
        mvprintw(SIDEBAR_CELL_BLOCK + 10, s + 1, " %d/%d health", u -> health, u_info -> max_health);
        mvprintw(SIDEBAR_CELL_BLOCK + 11, s + 1, " %d/%d moves", u -> moves, u_info -> max_moves);
    }
    else
    {
    {
        mvprintw(SIDEBAR_CELL_BLOCK + 7, s + 1, "             ");
        mvprintw(SIDEBAR_CELL_BLOCK + 8, s + 1, "             ");
        mvprintw(SIDEBAR_CELL_BLOCK + 9, s + 1, "             ");
        mvprintw(SIDEBAR_CELL_BLOCK + 10, s + 1, "             ");
        mvprintw(SIDEBAR_CELL_BLOCK + 11, s + 1, "             ");
    }
    }
    // Other info.
    mvprintw(r - 2, s + 1, "(%d,%d)    ", view -> map_r, view -> map_c);
}

void drawMap(World * world, View * view)
{

    int start_row = 1,    end_row = view -> rows - 2;
    int start_column = 1, end_column = view -> sidebar - 1;

    Node * current = ((Player *) world -> graph_players -> data) -> graph_map;
    Node * line = current;

    for(int i = start_row; i <= end_row; i++)
    {
        for(int j = start_column; j <= end_column; j++)
        {

            unsigned char type;

            type = ((Cell *) current -> data) -> territory;

            if(getNeighbour(current, EDGE_CELL_CITY))
            {
                printw("M");
            }
            else if(getNeighbour(current, EDGE_CELL_UNIT))
            {
                printw("U");
            }
            else
            {
                move(i, j);
                attron(COLOR_PAIR(type));

                switch ( type )
                {
                    case CELL_TYPE_WATER    : printw(".");  break;
                    case CELL_TYPE_GRASS    : printw("_");  break;
                    case CELL_TYPE_HILL     : printw("-");  break;
                    case CELL_TYPE_TREE     : printw("T");  break;
                    case CELL_TYPE_MOUNTAIN : printw("^");  break;
                    default                 : printw("E");  break;
                }
                attroff(COLOR_PAIR(type));
            }


            current = getNeighbour(current, EDGE_CELL_RIGHT);
        }
        line = getNeighbour(line, EDGE_CELL_BOTTOM);
        current = line;
    }
    move(view->cur_r,view->cur_c);

}


void viewProcess(World * world, View * view, Message * message)
{
    Player * player = (Player *) world -> graph_players -> data;

    if(message != NULL)
    {
        switch(message -> type)
        {
            case VIEW_REDRAW_ALL:
                drawView(world, view);
                drawInfo(world, view);
                drawMap(world, view);
                move(view -> cur_r, view -> cur_c);
            break;

            case VIEW_REDRAW_MAP:
                drawMap(world, view);
            break;

            case VIEW_MOVE_CURSOR_TOP:
                view -> current_cell = getNeighbour(view -> current_cell, EDGE_CELL_TOP);
                view -> map_r--; view -> map_r = view -> map_r < 0 ? view -> map_r + world -> properties -> map_r : view -> map_r;
                if(view -> cur_r > 5)
                {
                    view -> cur_r--;
                }
                else
                {
                    player -> graph_map = getNeighbour(player -> graph_map, EDGE_CELL_TOP);
                    drawMap(world, view);
                }
                drawInfo(world, view);
                move(view -> cur_r, view -> cur_c);
            break;

            case VIEW_MOVE_CURSOR_BOTTOM:
                view -> current_cell = getNeighbour(view -> current_cell, EDGE_CELL_BOTTOM);
                view -> map_r = (view -> map_r + 1) % world -> properties -> map_r;
                if(view -> cur_r < view -> rows - 5)
                {
                    view -> cur_r++;
                }
                else
                {
                    player -> graph_map = getNeighbour(player -> graph_map, EDGE_CELL_BOTTOM);
                    drawMap(world, view);
                }
                drawInfo(world, view);
                move(view -> cur_r, view -> cur_c);
            break;

            case VIEW_MOVE_CURSOR_RIGHT:
                view -> current_cell = getNeighbour(view -> current_cell, EDGE_CELL_RIGHT);
                view -> map_c = (view -> map_c + 1) % world -> properties -> map_c;
                if(view -> cur_c < view -> sidebar - 5)
                {
                    view -> cur_c++;
                }
                else
                {
                    player -> graph_map = getNeighbour(player -> graph_map, EDGE_CELL_RIGHT);
                    drawMap(world, view);
                }
                drawInfo(world, view);
                move(view -> cur_r, view -> cur_c);
            break;

            case VIEW_MOVE_CURSOR_LEFT:
                view -> current_cell = getNeighbour(view -> current_cell, EDGE_CELL_LEFT);
                view -> map_c--; view -> map_c = view -> map_c < 0 ? view -> map_c + world -> properties -> map_c : view -> map_c;
                if(view -> cur_c > 5)
                {
                    view -> cur_c--;
                    move(view -> cur_r, view -> cur_c);
                }
                else
                {
                    player -> graph_map = getNeighbour(player -> graph_map, EDGE_CELL_LEFT);
                    drawMap(world, view);
                }
                drawInfo(world, view);
                move(view -> cur_r, view -> cur_c);
            break;
        }

        destroyMessage(message);
    }
}
