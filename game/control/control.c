#include <stdlib.h>
#include <ncurses.h>

#include "../../modules/list/list.h"
#include "../../modules/city/city.h"
#include "../../modules/unit/unit.h"
#include "../view/definitions.h"
#include "../world/definitions.h"
#include "../view/view.h"
#include "control.h"
#include "definitions.h"

Control * createControl()
{
    Control * control = malloc(sizeof(Control));
    control -> state = CONTROL_MOVE_CURSOR;
    control -> cur_unit = NULL;
    control -> cur_city = NULL;
    return control;
}

void destroyControl(Control * control)
{
    free(control);
}

Message * controlProcess(World * world, View * view, Control * control, int key)
{
    // Arrow keys.
    if(key == KEY_UP || key == KEY_DOWN || key == KEY_RIGHT || key == KEY_LEFT)
    {
        // Move cursor state.
        if(control -> state == CONTROL_MOVE_CURSOR)
        {
            switch (key)
            {
                case KEY_UP   : return createMessage(VIEW_MOVE_CURSOR_TOP,    NULL); break;
                case KEY_DOWN : return createMessage(VIEW_MOVE_CURSOR_BOTTOM, NULL); break;
                case KEY_RIGHT: return createMessage(VIEW_MOVE_CURSOR_RIGHT,  NULL); break;
                case KEY_LEFT : return createMessage(VIEW_MOVE_CURSOR_LEFT,   NULL); break;
            }
        }

        if(control -> state == CONTROL_MOVE_UNIT)
        {
            switch (key)
            {
                case KEY_UP   : moveUnit(view->current_cell, EDGE_CELL_TOP); break;
                case KEY_DOWN : moveUnit(view->current_cell, EDGE_CELL_BOTTOM); break;
                case KEY_RIGHT: moveUnit(view->current_cell, EDGE_CELL_RIGHT); break;
                case KEY_LEFT : moveUnit(view->current_cell, EDGE_CELL_LEFT); break;
            }
        }

        // TODO Move unit state.
        // TODO Choose technology state (only up/down arrow keys).
    }

    // Enter (end of the turn).
    if(key == KEY_ENTER)
    {
        Player * player = (Player *) world -> graph_players -> data;
        // Remembering player's view settings.
        player -> cur_r = view -> cur_r;
        player -> cur_c = view -> cur_c;
        player -> map_r = view -> map_r;
        player -> map_c = view -> map_c;
        player -> current_cell = view -> current_cell;
        // Nulling all.
        control -> state = CONTROL_MOVE_CURSOR;
        control -> cur_unit = NULL;
        control -> cur_city = NULL;
        // Processing player's units and cities.
        listForEach(player -> cities, &developCity);
        ListElement * le = player -> units -> head;
        for(int i = 0; i < player -> units -> length; i++)
        {
            developUnit(le -> data, world -> units_info);
            le = le -> next;
        }
        // Next player.
        world -> graph_players = getNeighbour(world -> graph_players, EDGE_NEXT_PLAYER);
        player = (Player *) world -> graph_players -> data;
        // Getting his settings (if there are != 0).
        if(player -> cur_r != 0)  view -> cur_r = player -> cur_r; else view -> cur_r = view -> rows / 2;
        if(player -> cur_c != 0)  view -> cur_c = player -> cur_c; else view -> cur_c = view -> sidebar / 2;
        if(player -> map_r != -1) view -> map_r = player -> map_r; else view -> map_r = view -> rows / 2 - 1;
        if(player -> map_c != -1) view -> map_c = player -> map_c; else view -> map_c = view -> sidebar / 2 - 1;
        if(player -> current_cell != NULL) view -> current_cell = player -> current_cell; else view -> current_cell = getCell(player -> graph_map, view -> map_r, view -> map_c);
        // This fix doesn't work O_O. So I added player -> current_cell.
        //view -> current_cell = getCell(player -> graph_map, view -> map_r, view -> map_c);
        // Send redrawing message.
        return createMessage(VIEW_REDRAW_ALL, NULL);
    }

    if (key == KEY_SPACE)
    {
        if (getNeighbour(view -> current_cell, EDGE_CELL_UNIT) != NULL )
        {
            if (control -> state == CONTROL_MOVE_UNIT)
                control -> state = CONTROL_MOVE_CURSOR;
            else
                control -> state = CONTROL_MOVE_UNIT;
        }


    }

    return NULL;
}
