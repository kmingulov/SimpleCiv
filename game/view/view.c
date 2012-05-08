#include <string.h>
#include <stdlib.h>
#include <math.h>


#include "view.h"

#include "../../modules/graph/graph.h"
#include "../../modules/player/player.h"
#include "../../modules/city/city.h"
#include "../../modules/unit/unit.h"
#include "../../modules/technology/technology.h"
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

    result -> sidebar = 0.8 * result -> columns;
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
    mvprintw(start_r, start_c + length - strlen(buffer), buffer);

    refresh();
}

void drawGeneralView(World * world, View * view)
{
    erase();

    // Copying rows, columns and sidebar.
    int r = view -> rows;
    int c = view -> columns;
    int s = view -> sidebar;

    attron(COLOR_PAIR(0));

    // Drawing main lines.
    for(int i = 1; i < c; i++)
    {
        mvaddch(0, i, ACS_HLINE);
        mvaddch(r - 1, i, ACS_HLINE);
        if(i > s && i < c - 1)
        {
            mvaddch(SIDEBAR_PLAYER_BLOCK, i, ACS_HLINE);
            mvaddch(SIDEBAR_CELL_BLOCK, i, ACS_HLINE);
            mvaddch(r - 3, i, ACS_HLINE);
        }
    }

    for(int i = 1; i < r - 1; i++)
    {
        mvaddch(i, s, ACS_VLINE);
        mvaddch(i, 0, ACS_VLINE);
        mvaddch(i, c - 1, ACS_VLINE);
    }

    // Corners.
    mvaddch(0, 0, ACS_ULCORNER);
    mvaddch(r - 1, 0, ACS_LLCORNER);
    mvaddch(0, c - 1, ACS_URCORNER);
    mvaddch(r - 1, c - 1, ACS_LRCORNER);
    mvaddch(0, s, ACS_TTEE);
    mvaddch(r - 1, s, ACS_BTEE);

    mvaddch(SIDEBAR_PLAYER_BLOCK, s, ACS_LTEE); mvaddch(SIDEBAR_PLAYER_BLOCK, c - 1, ACS_RTEE);
    mvaddch(SIDEBAR_CELL_BLOCK, s, ACS_LTEE); mvaddch(SIDEBAR_CELL_BLOCK, c - 1, ACS_RTEE);
    mvaddch(r - 3, s, ACS_LTEE); mvaddch(r - 3, c - 1, ACS_RTEE);

    // Project name.
    attron(A_BOLD); putInMiddle(1, s + 1, c - s - 2, GAME_NAME); attroff(A_BOLD);

    attroff(COLOR_PAIR(0));
}

void drawTechView(World * world, View * view)
{
    erase();

    // Copying rows, columns and sidebar.
    int r = view -> rows;
    int c = view -> columns;

    // Drawing main lines.
    for(int i = 1; i < c; i++)
    {
        mvaddch(0, i, ACS_HLINE);
        mvaddch(r - 1, i, ACS_HLINE);
    }
    for(int i = 1; i < r - 1; i++)
    {
        mvaddch(i, 0, ACS_VLINE);
        mvaddch(i, c - 1, ACS_VLINE);
    }
    mvaddch(0, 0, ACS_ULCORNER);
    mvaddch(r - 1, 0, ACS_LLCORNER);
    mvaddch(0, c - 1, ACS_URCORNER);
    mvaddch(r - 1, c - 1, ACS_LRCORNER);

    // Drawing player name and other info.
    Player * player = (Player *) world -> graph_players -> data;
    attron(A_BOLD); mvprintw(2, 3, "%s's researches", player -> name); attroff(A_BOLD);
    mvprintw(3, 3, "%d gold, %d gold spents on reasearches every turn", player -> gold, 1);

    // Drawing available technologies.
    attron(A_BOLD); mvprintw(5, 3, "Available for researching:"); attroff(A_BOLD);
    int line = 6; int count = 0;
    for(int i = 0; i < player -> available_techs -> length; i++)
    {
        int value = iaGetByIndex(player -> available_techs, i);
        if(value == TECH_AVAILABLE)
        {
            Technology * t = (Technology *) ((Node *) daGetByIndex(world -> techs_info, i)) -> data;
            // Checking for resources.
            if(t -> requires_resources == NULL)
            {
                // Nothing requires. Great.
                count++;
                mvprintw(line++, 3, "[ ] %s", t -> name);
            }
            else
            {
                // Checking for each resource.
                char okay = 1;
                for(int j = 0; j < t -> requires_resources -> length; j++)
                {
                    // Getting resource id.
                    int id = iaGetByIndex(t -> requires_resources, j);
                    // Does player have this resources?
                    if(iaGetByIndex(player -> resources, id) == 0)
                    {
                        // Sad but true.
                        okay = 0;
                        break;
                    }
                }
                // You're lucky man.
                if(okay == 1)
                {
                    count++;
                    mvprintw(line++, 3, "[ ] %s", t -> name);
                }
            }
        }
    }

    if(count == 0)
    {
        mvprintw(line++, 3, "No technologies");
    }

    // Drawing researched technologies.
    line++;
    attron(A_BOLD); mvprintw(line++, 3, "Already researched:"); attroff(A_BOLD);
    for(int i = 0; i < player -> available_techs -> length; i++)
    {
        int value = iaGetByIndex(player -> available_techs, i);
        if(value == TECH_RESEARCHED)
        {
            Technology * t = (Technology *) ((Node *) daGetByIndex(world -> techs_info, i)) -> data;
            mvprintw(line++, 3, "%s", t -> name);
        }
    }
}

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

void drawPlayerInfo(World * world, View * view)
{
    int s = view -> sidebar;
    int len = view -> columns - view -> sidebar - 2;

    clearBlock(SIDEBAR_PLAYER_BLOCK + 1, s + 1, 7, len);

    // Player.
    Player * player = (Player *) world -> graph_players -> data;

    // Player info.
    attron(A_BOLD); putInMiddle(SIDEBAR_PLAYER_BLOCK + 1, s + 1, len, "%s", player -> name); attroff(A_BOLD);
    mvprintw(SIDEBAR_PLAYER_BLOCK + 2, s + 1, "Gold");
    putInRight(SIDEBAR_PLAYER_BLOCK + 2, s + 1, len, "%d", player -> gold);
    const char res_names[][10] = {"", "Bronze", "Iron", "Coal", "Gunpowder", "Horses"};
    for(int i = 1; i <= CELL_RES_COUNT - 1; i++)
    {
        mvprintw(SIDEBAR_PLAYER_BLOCK + 2 + i, s + 1, res_names[i]);
        putInRight(SIDEBAR_PLAYER_BLOCK + 2 + i, s + 1, len, "%d", iaGetByIndex(player -> resources, i));
    }
}

void drawCellInfo(World * world, View * view)
{
    int s = view -> sidebar;
    int r = view -> rows;
    int len = view -> columns - view -> sidebar - 2;

    clearBlock(SIDEBAR_CELL_BLOCK + 1, s + 1, 11, len);

    // Cell.
    Cell * c = (Cell *) view -> current_cell -> data;
    attron(A_BOLD);

    // Type of territory.
    switch(c -> territory)
    {
        case CELL_TYPE_WATER:    mvprintw(SIDEBAR_CELL_BLOCK + 1, s + 1, "Water    "); break;
        case CELL_TYPE_GRASS:    mvprintw(SIDEBAR_CELL_BLOCK + 1, s + 1, "Grass    "); break;
        case CELL_TYPE_TREE:     mvprintw(SIDEBAR_CELL_BLOCK + 1, s + 1, "Forest   "); break;
        case CELL_TYPE_HILL:     mvprintw(SIDEBAR_CELL_BLOCK + 1, s + 1, "Hill     "); break;
        case CELL_TYPE_MOUNTAIN: mvprintw(SIDEBAR_CELL_BLOCK + 1, s + 1, "Mountains"); break;
    }

    // Resources.
    switch(c -> resources)
    {
        case CELL_RES_NONE:      mvprintw(SIDEBAR_CELL_BLOCK + 2, s + 1, "            "); break;
        case CELL_RES_BRONZE:    mvprintw(SIDEBAR_CELL_BLOCK + 2, s + 1, "Bronze      "); break;
        case CELL_RES_IRON:      mvprintw(SIDEBAR_CELL_BLOCK + 2, s + 1, "Iron        "); break;
        case CELL_RES_COAL:      mvprintw(SIDEBAR_CELL_BLOCK + 2, s + 1, "Coal        "); break;
        case CELL_RES_GUNPOWDER: mvprintw(SIDEBAR_CELL_BLOCK + 2, s + 1, "Gunpowder   "); break;
        case CELL_RES_HORSES:    mvprintw(SIDEBAR_CELL_BLOCK + 2, s + 1, "Horses      "); break;
        case CELL_RES_MUSHROOMS: mvprintw(SIDEBAR_CELL_BLOCK + 2, s + 1, "Mushrooms :O"); break;
    }

    attroff(A_BOLD);

    // City.
    Node * city = getNeighbour(view -> current_cell, EDGE_CELL_CITY);
    if(city != NULL)
    {
        City * c = (City *) city -> data;
        attron(A_BOLD); mvprintw(SIDEBAR_CELL_BLOCK + 3, s + 1, "City:  "); attroff(A_BOLD);
        putInLeft(SIDEBAR_CELL_BLOCK + 4, s + 2, len - 2, c -> name);
        putInLeft(SIDEBAR_CELL_BLOCK + 5, s + 2, len - 2, c -> owner -> name);
        mvprintw(SIDEBAR_CELL_BLOCK + 6, s + 2, "People");
        putInRight(SIDEBAR_CELL_BLOCK + 6, s + 2, len - 2, "%d", c -> population);
    }

    // Unit.
    Node * unit = getNeighbour(view -> current_cell, EDGE_CELL_UNIT);
    if(unit != NULL)
    {
        Unit * u = (Unit *) unit -> data;
        UnitCommonInfo * u_info = (UnitCommonInfo *) daGetByIndex(world -> units_info, u -> unit_id);
        attron(A_BOLD); mvprintw(SIDEBAR_CELL_BLOCK + 7, s + 1, "Unit:  "); attroff(A_BOLD);
        putInLeft(SIDEBAR_CELL_BLOCK + 8, s + 2, len - 2, u_info -> name);
        putInLeft(SIDEBAR_CELL_BLOCK + 9, s + 2, len - 2, u -> owner -> name);
        mvprintw(SIDEBAR_CELL_BLOCK + 10, s + 2, "HP");
        putInRight(SIDEBAR_CELL_BLOCK + 10, s + 2, len - 2, "%d/%d", u -> health, u_info -> max_health);
        mvprintw(SIDEBAR_CELL_BLOCK + 11, s + 2, "Moves");
        putInRight(SIDEBAR_CELL_BLOCK + 11, s + 2, len - 2, "%d/%d", u -> moves, u_info -> max_moves);
    }

    // Other info.
    clearBlock(r - 2, s + 1, 1, len);
    putInMiddle(r - 2, s + 1, len, "(%d,%d)", view -> map_r, view -> map_c);
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
            move(i, j);

            if(getNeighbour(current, EDGE_CELL_CITY) != NULL)
            {
                addch('M');
            }
            else if(getNeighbour(current, EDGE_CELL_UNIT) != NULL)
            {
                // Getting unit's char.
                Unit * unit = (Unit *) getNeighbour(current, EDGE_CELL_UNIT) -> data;
                UnitCommonInfo * u_info = (UnitCommonInfo *) daGetByIndex(world -> units_info, unit -> unit_id);
                addch(u_info -> c);
            }
            else
            {
                unsigned char type = ((Cell *) current -> data) -> territory;
                attron(COLOR_PAIR(type));

                switch ( type )
                {
                    case CELL_TYPE_WATER    : addch('.'); break;
                    case CELL_TYPE_GRASS    : addch('_'); break;
                    case CELL_TYPE_HILL     : addch('-'); break;
                    case CELL_TYPE_TREE     : addch('T'); break;
                    case CELL_TYPE_MOUNTAIN : addch('^'); break;
                    default                 : addch('E'); break;
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
                drawGeneralView(world, view);
                drawPlayerInfo(world, view);
                drawCellInfo(world, view);
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
                drawCellInfo(world, view);
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
                drawCellInfo(world, view);
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
                drawCellInfo(world, view);
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
                drawCellInfo(world, view);
                move(view -> cur_r, view -> cur_c);
            break;
        }

        destroyMessage(message);
    }
}
