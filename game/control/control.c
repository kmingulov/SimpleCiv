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
    return control;
}

void destroyControl(Control * control)
{
    free(control);
}

int * twoIntsInPointer(int a, int b)
{
    int * result = malloc(sizeof(int) * 2);
    result[0] = a;
    result[1] = b;
    return result;
}

List * controlProcess(World * world, View * view, Control * control, int key)
{
    // Arrow keys.
    if(key == KEY_UP || key == KEY_DOWN || key == KEY_RIGHT || key == KEY_LEFT)
    {
        // Move cursor state.
        if(control -> state == CONTROL_MOVE_CURSOR)
        {
            List * list = listCreate();
            switch (key)
            {
                case KEY_UP   :
                    listPrepend(list, createMessage(VIEW_MOVE_CURSOR_TOP, NULL));
                break;

                case KEY_DOWN :
                    listPrepend(list, createMessage(VIEW_MOVE_CURSOR_BOTTOM, NULL));
                break;

                case KEY_RIGHT:
                    listPrepend(list, createMessage(VIEW_MOVE_CURSOR_RIGHT, NULL));
                break;

                case KEY_LEFT :
                    listPrepend(list, createMessage(VIEW_MOVE_CURSOR_LEFT, NULL));
                break;
            }
            return list;
        }

        // Move unit state.
        if(control -> state == CONTROL_MOVE_UNIT)
        {
            // Cannot move not your unit.
            Node * n = getNeighbour(view -> current_cell, EDGE_CELL_UNIT);
            if(n == NULL)
            {
                return NULL;
            }
            Unit * unit = (Unit *) n -> data;
            Player * player = (Player *) world -> graph_players -> data;
            if(player != unit -> owner)
            {
                return NULL;
            }

            int keys[][5] = {{KEY_UP,    EDGE_CELL_TOP,    VIEW_MOVE_CURSOR_TOP,    -1, 0},
                             {KEY_DOWN,  EDGE_CELL_BOTTOM, VIEW_MOVE_CURSOR_BOTTOM, 1,  0},
                             {KEY_RIGHT, EDGE_CELL_RIGHT,  VIEW_MOVE_CURSOR_RIGHT,  0,  1},
                             {KEY_LEFT,  EDGE_CELL_LEFT,   VIEW_MOVE_CURSOR_LEFT,   0,  -1}};
            for(int i = 0; i < 4; i++)
            {
                if(key == keys[i][0])
                {
                    // Succefully moved unit.
                    int res = moveUnit(world, view -> current_cell, keys[i][1]);
                    if(res == 1)
                    {
                        List * list = listCreate();
                        listPrepend(list, createMessage(VIEW_REDRAW_MAP, NULL));
                        // Moving cursor.
                        listPrepend(list, createMessage(keys[i][2], NULL));
                        return list;
                    }
                    else if(res == 2)
                    {
                        List * list = listCreate();
                        listPrepend(list, createMessage(VIEW_REDRAW_ALL, NULL));
                        return list;
                    }
                    return NULL;
                }
            }
        }

        // Choosing technology state.
        if(control -> state == CONTROL_CHOOSE_TECH)
        {
            List * list = listCreate();
            switch (key)
            {
                case KEY_UP   :
                    listPrepend(list, createMessage(VIEW_MOVE_TECH_CURSOR_TOP, NULL));
                break;

                case KEY_DOWN :
                    listPrepend(list, createMessage(VIEW_MOVE_TECH_CURSOR_BOTTOM, NULL));
                break;
            }
            return list;
        }

        // TODO Add choosing unit state.
    }

    // Enter (end of the turn).
    if(key == KEY_ENTER)
    {
        // End of the turn.
        if(control -> state == CONTROL_MOVE_CURSOR || control -> state == CONTROL_MOVE_UNIT)
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
            // Processing player's units and cities.
            listForEach(player -> cities, &developCity);
            ListElement * le = player -> units -> head;
            for(int i = 0; i < player -> units -> length; i++)
            {
                developUnit(le -> data, world -> units_info);
                le = le -> next;
            }
            // Processing player's research.
            if(player -> research -> id != -1)
            {
                player -> research -> turns++;
                player -> gold -= player -> research -> delta;
                // Getting technology.
                Node * n = (Node *) daGetByIndex(world -> techs_info, player -> research -> id);
                Technology * t = (Technology *) n -> data;
                // Woohoo! Reasearched!
                if(player -> research -> turns == t -> turns)
                {
                    // Updating tech table.
                    updateTechnologyStatus(player -> available_techs, n);
                    // Updatint research info.
                    player -> research -> id = -1;
                    player -> research -> turns = 0;
                }
            }
            // Next player.
            world -> graph_players = getNeighbour(world -> graph_players, EDGE_NEXT_PLAYER);
            player = (Player *) world -> graph_players -> data;
            // Getting his settings (if there are != 0).
            if(player -> cur_r != 0)  view -> cur_r = player -> cur_r; else view -> cur_r = view -> rows / 2;
            if(player -> cur_c != 0)  view -> cur_c = player -> cur_c; else view -> cur_c = view -> sidebar / 2;
            if(player -> map_r != -1) view -> map_r = player -> map_r; else view -> map_r = view -> rows / 2 - 1;
            if(player -> map_c != -1) view -> map_c = player -> map_c; else view -> map_c = view -> sidebar / 2 - 1;
            if(player -> current_cell != NULL) view -> current_cell = player -> current_cell;
            else view -> current_cell = getCell(player -> graph_map, view -> map_r, view -> map_c);
            // This fix doesn't work O_O. So I added player -> current_cell.
            //view -> current_cell = getCell(player -> graph_map, view -> map_r, view -> map_c);
            // Send redrawing message.
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_ALL, NULL));
            return list;
        }
    }

    // translate to hindi
    if(key == KEY_SPACE)
    {
        Node * n = getNeighbour( view -> current_cell, EDGE_CELL_CITY );
        if(n == NULL)
        {
            // Cannot open dialog for not your unit.
            Node * n = getNeighbour(view -> current_cell, EDGE_CELL_UNIT);
            if (n != NULL)
            {
                Unit * unit = (Unit *) n -> data;
                Player * player = (Player *) world -> graph_players -> data;
                if(player != unit -> owner)
                {
                    return NULL;
                }

                if(getNeighbour(view -> current_cell, EDGE_CELL_UNIT) != NULL)
                {
                    if(control -> state == CONTROL_MOVE_UNIT)
                    {
                        control -> state = CONTROL_MOVE_CURSOR;
                        return NULL;
                    }
                    else
                    {
                        control -> state = CONTROL_MOVE_UNIT;
                        return NULL;
                    }
                }
            }
            else
            {
                return NULL;
            }
        }
        else
        {
            // Cannot open dialog for not your city.
            City * city = (City *) n -> data;
            Player * player = (Player *) world -> graph_players -> data;
            if(player != city -> owner)
            {
                return NULL;
            }

            if(control -> state != CONTROL_CHOOSE_UNIT)
            {
                control -> state = CONTROL_CHOOSE_UNIT;
                List * list = listCreate();
                listPrepend(list, createMessage(VIEW_REDRAW_CITY_DIALOG, NULL));
                return list;
            }
            else
            {
                control -> state = CONTROL_MOVE_CURSOR;
                List * list = listCreate();
                listPrepend(list, createMessage(VIEW_REDRAW_ALL, NULL));
                return list;
            }
        }
    }

    // Turning technology state.
    if((char) key == 'T' || (char) key == 't')
    {
        if(control -> state != CONTROL_CHOOSE_TECH )
        {
            control -> state = CONTROL_CHOOSE_TECH;
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_TECH_DIALOG, NULL));
            return list;
        }
        else
        {
            control -> state = CONTROL_MOVE_CURSOR;
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_ALL, NULL));
            return list;
        }
    }

    // Trying to escape?
    if((char) key == 'Q' || (char) key == 'q')
    {
        if(control -> state == CONTROL_MOVE_CURSOR || control -> state == CONTROL_MOVE_UNIT)
        {
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_ESCAPE, NULL));
            return list;
        }

        if(control -> state == CONTROL_CHOOSE_TECH || control -> state == CONTROL_CHOOSE_UNIT)
        {
            control -> state = CONTROL_MOVE_CURSOR;
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_ALL, NULL));
            return list;
        }
    }

    return NULL;
}
