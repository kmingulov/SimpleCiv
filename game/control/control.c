#include <stdlib.h>
#include <string.h>


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
        if(control -> state == CONTROL_CHOOSE_TECH || control -> state == CONTROL_CHOOSE_UNIT)
        {
            List * list = listCreate();
            switch(key)
            {
                case KEY_UP  :
                    listPrepend(list, createMessage(VIEW_CHOOSER_MOVE_CURSOR_TOP, NULL));
                break;

                case KEY_DOWN:
                    listPrepend(list, createMessage(VIEW_CHOOSER_MOVE_CURSOR_BOTTOM, NULL));
                break;
            }
            return list;
        }

        // TODO Add choosing unit state.
    }

    // Enter.
    if(key == KEY_ENTER_FIXED)
    {
        // Start research.
        if(control -> state == CONTROL_CHOOSE_TECH)
        {
            Player * player = (Player *) world -> graph_players -> data;
            int current = view -> chooser -> current;
            // Change research.
            if(current == -1)
            {
                player -> research -> id = -1;
                player -> research -> turns = 0;
                player -> research -> delta = 0;
            }
            else
            {
                int t_id = iaGetByIndex(view -> chooser -> ids, current);
                // If there're equal, player doesn't change anything.
                if(t_id != player -> research -> id)
                {
                    Technology * t = (Technology *) ((Node *) daGetByIndex(world -> techs_info, t_id)) -> data;
                    player -> research -> id = t_id;
                    player -> research -> turns = 0;
                    player -> research -> delta = 1.5f * t -> turns;
                }
            }
            // Go back to the map.
            control -> state = CONTROL_MOVE_CURSOR;
            destroyChooser(view -> chooser);
            view -> chooser = NULL;
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_ALL, NULL));
            return list;
        }

        // Start hiring.
        if(control -> state == CONTROL_CHOOSE_UNIT)
        {
            Node * n = getNeighbour(view -> current_cell, EDGE_CELL_CITY);
            City * city = (City *) n -> data;
            int current = view -> chooser -> current;
            // Change research.
            if(current == -1)
            {
                city -> hiring -> id = -1;
                city -> hiring -> turns = 0;
                city -> hiring -> delta = 0;
            }
            else
            {
                int u_id = iaGetByIndex(view -> chooser -> ids, current);
                // If there're equal, player doesn't change anything.
                if(u_id != city -> hiring -> id)
                {
                    UnitCommonInfo * u_info = (UnitCommonInfo *) daGetByIndex(world -> units_info, u_id);
                    city -> hiring -> id = u_id;
                    city -> hiring -> turns = 0;
                    city -> hiring -> delta = 1.5f * u_info -> hiring_turns;
                }
            }
            // Go back to the map.
            control -> state = CONTROL_MOVE_CURSOR;
            destroyChooser(view -> chooser);
            view -> chooser = NULL;
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_ALL, NULL));
            return list;
        }

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
            // Processing player's research. Also player need to have enough money.
            if(player -> research -> id != -1 && player -> gold > player -> research -> delta)
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
                    // Updating unit table.
                    updateUnitStatus(player -> available_units, player -> available_techs, world -> techs_info);
                    // Updating research info.
                    player -> research -> id = -1;
                    player -> research -> turns = 0;
                    player -> research -> delta = 0;
                }
            }
            // Processing player's units and cities.
            ListElement * le = player -> cities -> head;
            for(int i = 0; i < player -> cities -> length; i++)
            {
                developCity(world, le -> data);
                le = le -> next;
            }
            le = player -> units -> head;
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

    // Space event.
    if( key == KEY_SPACE && (control -> state == CONTROL_MOVE_CURSOR || control -> state == CONTROL_MOVE_UNIT) )
    {
        Node * node = NULL;

        node = getNeighbour(view -> current_cell, EDGE_CELL_UNIT);
        if(node != NULL)
        {
            // Cannot move not your unit.
            Unit * unit = (Unit *) node -> data;
            Player * player = (Player *) world -> graph_players -> data;
            if(player != unit -> owner)
            {
                return NULL;
            }

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

        node = getNeighbour(view -> current_cell, EDGE_CELL_CITY);
        if(node != NULL)
        {
            // Cannot open dialog for not your city.
            City * city = (City *) node -> data;
            Player * player = (Player *) world -> graph_players -> data;
            if(player != city -> owner)
            {
                return NULL;
            }

            if(control -> state != CONTROL_CHOOSE_UNIT)
            {
                control -> state = CONTROL_CHOOSE_UNIT;
                // Create chooser.
                view -> chooser = createUnitChooser(world, view);
                List * list = listCreate();
                listPrepend(list, createMessage(VIEW_REDRAW_CITY_DIALOG, NULL));
                return list;
            }
        }
    }

    // Turning technology state.
    if((char) key == 'T' || (char) key == 't')
    {
        if(control -> state != CONTROL_CHOOSE_TECH)
        {
            // Switch state.
            control -> state = CONTROL_CHOOSE_TECH;
            // Create chooser.
            view -> chooser = createTechChooser(world);
            // Send message.
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_TECH_DIALOG, NULL));
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

        if(control -> state == CONTROL_HELP || control -> state == CONTROL_UNIT_INFO)
        {
            control -> state = CONTROL_MOVE_CURSOR;
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_ALL, NULL));
            return list;
        }

        if(control -> state == CONTROL_CHOOSE_TECH || control -> state == CONTROL_CHOOSE_UNIT)
        {
            control -> state = CONTROL_MOVE_CURSOR;
            destroyChooser(view -> chooser);
            view -> chooser = NULL;
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_ALL, NULL));
            return list;
        }
    }

    // Showing help.
    if((char) key == 'H' || (char) key == 'h')
    {
        if(control -> state == CONTROL_MOVE_CURSOR || control -> state == CONTROL_MOVE_UNIT)
        {
            control -> state = CONTROL_HELP;
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_HELP, NULL));
            return list;
        }
    }

    // Showing unit info.
    if((char) key == 'I' || (char) key == 'i')
    {
        if(control -> state == CONTROL_MOVE_CURSOR || control -> state == CONTROL_MOVE_UNIT)
        {
            Node * n = getNeighbour(view -> current_cell, EDGE_CELL_UNIT);
            // There is no unit, cannot show any info.
            if(n == NULL)
            {
                return NULL;
            }
            control -> state = CONTROL_UNIT_INFO;
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_UNIT_INFO, NULL));
            return list;
        }
    }

    // Create city.
    if((char) key == 'C' || (char) key == 'c')
    {
        if(control -> state == CONTROL_MOVE_UNIT)
        {
            Node * n = getNeighbour(view -> current_cell, EDGE_CELL_UNIT);
            Unit * unit = (Unit *) n -> data;
            UnitCommonInfo * u_info = (UnitCommonInfo *) daGetByIndex(world -> units_info, unit -> unit_id);

            if(iaSearchForData(u_info -> privileges, UNIT_PRVL_BUILD_CITY) != -1)
            {
                char * s = malloc(sizeof(char) * 16);
                strcpy(s, "NAME");

                createCity(world, s, unit -> r, unit -> c, unit -> owner);

                List * list = listCreate();
                listPrepend(list, createMessage(VIEW_REDRAW_ALL, NULL));
                return list;
            }
            return NULL;
        }
    }

    return NULL;
}
