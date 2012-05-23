#include <stdlib.h>
#include <string.h>

#include "../../modules/unit/unit.h"
#include "../../modules/unit/unit_table.h"
#include "../../modules/unit/unit_common_info.h"
#include "../../modules/technology/technology.h"
#include "../../modules/technology/technology_table.h"

#include "../view/view_textbox.h"

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
                    listPrepend(list, createMessage(VIEW_MOVE_CURSOR_TOP));
                break;

                case KEY_DOWN :
                    listPrepend(list, createMessage(VIEW_MOVE_CURSOR_BOTTOM));
                break;

                case KEY_RIGHT:
                    listPrepend(list, createMessage(VIEW_MOVE_CURSOR_RIGHT));
                break;

                case KEY_LEFT :
                    listPrepend(list, createMessage(VIEW_MOVE_CURSOR_LEFT));
                break;
            }
            return list;
        }

        // Move unit state.
        if(control -> state == CONTROL_MOVE_UNIT)
        {
            // Cannot move to the cell with another unit.
            Node * n = getNeighbour(view -> current_cell, EDGE_CELL_UNIT);
            if(n == NULL)
            {
                return NULL;
            }
            Unit * unit = (Unit *) n -> data;
            // Cannot move not your unit.
            Player * player = (Player *) listGetHead(world -> players);
            if(player != unit -> owner)
            {
                return NULL;
            }

            int keys[][5] = {{KEY_UP,    EDGE_CELL_TOP,    VIEW_MOVE_CURSOR_TOP,   -1,   0},
                             {KEY_DOWN,  EDGE_CELL_BOTTOM, VIEW_MOVE_CURSOR_BOTTOM, 1,   0},
                             {KEY_RIGHT, EDGE_CELL_RIGHT,  VIEW_MOVE_CURSOR_RIGHT,  0,   1},
                             {KEY_LEFT,  EDGE_CELL_LEFT,   VIEW_MOVE_CURSOR_LEFT,   0,  -1}};
            for(int i = 0; i < 4; i++)
            {
                if(key == keys[i][0])
                {
                    // Succefully moved unit.
                    int res = moveUnit(world, view -> current_cell, keys[i][1]);
                    if(res == 0)
                    {
                        List * list = listCreate();
                        listPrepend(list, createMessage(VIEW_REDRAW_MAP));
                        // Moving cursor.
                        listPrepend(list, createMessage(keys[i][2]));
                        return list;
                    }
                    else if(res == 1)
                    {
                        List * list = listCreate();
                        listPrepend(list, createMessage(VIEW_REDRAW_ALL));
                        return list;
                    }
                    else if(res == 2)
                    {
                        // Show win message (9x36).
                        int start_r = (view -> rows - 9) / 2;
                        int start_c = (view -> columns - 36) / 2;
                        view -> textbox = createTextbox(start_r, start_c, 9, 36);
                        addWinInfoToTextbox(view -> textbox);
                        control -> state = CONTROL_TEXTBOX;
                        // Redrawing.
                        List * list = listCreate();
                        listPrepend(list, createMessage(VIEW_REDRAW_ALL));
                        listPrepend(list, createMessage(VIEW_REDRAW_TEXTBOX));
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
                    listPrepend(list, createMessage(VIEW_CHOOSER_MOVE_CURSOR_TOP));
                break;

                case KEY_DOWN:
                    listPrepend(list, createMessage(VIEW_CHOOSER_MOVE_CURSOR_BOTTOM));
                break;
            }
            return list;
        }

        // Scrolling textbox.
        if(control -> state == CONTROL_TEXTBOX)
        {
            switch(key)
            {
                case KEY_UP  :
                    view -> textbox -> current_page -= 1;
                    if(view -> textbox -> current_page < 0)
                    {
                        view -> textbox -> current_page = 0;
                    }
                break;

                case KEY_DOWN:
                    view -> textbox -> current_page += 1;
                    if(view -> textbox -> current_page >= view -> textbox -> pages_count)
                    {
                        view -> textbox -> current_page = view -> textbox -> pages_count - 1;
                    }
                break;
            }
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_TEXTBOX));
            return list;
        }
    }

    // Enter.
    if(key == KEY_ENTER_FIXED)
    {
        // Start research.
        if(control -> state == CONTROL_CHOOSE_TECH)
        {
            Player * player = (Player *) listGetHead(world -> players);
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
            listPrepend(list, createMessage(VIEW_REDRAW_ALL));
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
                    // Set info.
                    UnitCommonInfo * u_info = (UnitCommonInfo *) daGetByIndex(world -> units_info, u_id);
                    city -> hiring -> id = u_id;
                    city -> hiring -> turns = 0;
                    city -> hiring -> delta = 1.5f * u_info -> hiring_turns;
                    // Decrement player's resources.
                    Player * player = (Player *) listGetHead(world -> players);
                    if(u_info -> resources != NULL)
                    {
                        for(int i = 0; i < u_info -> resources -> length; i++)
                        {
                            int id = iaGetByIndex(u_info -> resources, i);
                            int res = iaGetByIndex(player -> resources, id);
                            iaSetByIndex(player -> resources, id, res - 1);
                        }
                    }
                }
            }
            // Go back to the map.
            control -> state = CONTROL_MOVE_CURSOR;
            destroyChooser(view -> chooser);
            view -> chooser = NULL;
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_ALL));
            return list;
        }

        // End of the turn.
        if(control -> state == CONTROL_MOVE_CURSOR || control -> state == CONTROL_MOVE_UNIT)
        {
            Player * player = (Player *) listGetHead(world -> players);
            // Remembering player's view settings.
            player -> cur_r = view -> cur_r;
            player -> cur_c = view -> cur_c;
            player -> map_r = view -> map_r;
            player -> map_c = view -> map_c;
            player -> current_cell = view -> current_cell;
            // Changing state.
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
                    updateTechnologyTable(player -> available_techs, n);
                    // Updating unit table.
                    updateUnitTable(player -> available_units, player -> available_techs, world -> techs_info);
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
            listScrollNext(world -> players);
            player = (Player *) listGetHead(world -> players);
            if(player -> is_computer)
            {
                listScrollNext(world -> players);
                player = (Player *) listGetHead(world -> players);
            }
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
            listPrepend(list, createMessage(VIEW_REDRAW_ALL));
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
            Player * player = listGetHead(world -> players);
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
            Player * player = (Player *) listGetHead(world -> players);
            if(player != city -> owner)
            {
                return NULL;
            }

            if(control -> state != CONTROL_CHOOSE_UNIT)
            {
                control -> state = CONTROL_CHOOSE_UNIT;
                // Create chooser.
                view -> chooser = createUnitChooser(world, city);
                List * list = listCreate();
                listPrepend(list, createMessage(VIEW_REDRAW_CITY_DIALOG));
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
            listPrepend(list, createMessage(VIEW_REDRAW_TECH_DIALOG));
            return list;
        }
    }

    // Trying to escape?
    if((char) key == 'Q' || (char) key == 'q')
    {
        if(control -> state == CONTROL_MOVE_CURSOR || control -> state == CONTROL_MOVE_UNIT)
        {
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_ESCAPE));
            return list;
        }

        if(control -> state == CONTROL_TEXTBOX)
        {
            control -> state = CONTROL_MOVE_CURSOR;
            destroyTextbox(view -> textbox);
            view -> textbox = NULL;
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_ALL));
            return list;
        }

        if(control -> state == CONTROL_CHOOSE_TECH || control -> state == CONTROL_CHOOSE_UNIT)
        {
            control -> state = CONTROL_MOVE_CURSOR;
            destroyChooser(view -> chooser);
            view -> chooser = NULL;
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_ALL));
            return list;
        }
    }

    // Showing help.
    if((char) key == 'H' || (char) key == 'h')
    {
        if(control -> state == CONTROL_MOVE_CURSOR || control -> state == CONTROL_MOVE_UNIT)
        {
            view -> textbox = createTextbox(5, 5, view -> rows - 10, view -> columns - 10);
            addHelpInfoToTextbox(view -> textbox);
            control -> state = CONTROL_TEXTBOX;
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_TEXTBOX));
            return list;
        }
    }

    // Showing unit info.
    if((char) key == 'I' || (char) key == 'i')
    {
        if(control -> state == CONTROL_MOVE_CURSOR || control -> state == CONTROL_MOVE_UNIT)
        {
            // There is a fog, cannot show any info.
            Player * player = (Player *) listGetHead(world -> players);
            if(!isKnownCell(player -> fog, view -> map_r, view -> map_c))
            {
                return NULL;
            }
            Node * n = getNeighbour(view -> current_cell, EDGE_CELL_UNIT);
            // There is no unit, cannot show any info.
            if(n == NULL)
            {
                return NULL;
            }
            view -> textbox = createTextbox(5, 5, view -> rows - 10, view -> columns - 10);
            addUnitInfoToTextbox(view -> textbox, world, view);
            control -> state = CONTROL_TEXTBOX;
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_TEXTBOX));
            return list;
        }
    }

    // Create city.
    if((char) key == 'C' || (char) key == 'c')
    {
        Node * c = getNeighbour(view -> current_cell, EDGE_CELL_CITY);
        if(control -> state == CONTROL_MOVE_UNIT && c == NULL)
        {
            Node * n = getNeighbour(view -> current_cell, EDGE_CELL_UNIT);
            Unit * unit = (Unit *) n -> data;
            UnitCommonInfo * u_info = (UnitCommonInfo *) daGetByIndex(world -> units_info, unit -> unit_id);

            if(iaSearchForData(u_info -> privileges, UNIT_PRVL_BUILD_CITY) != -1)
            {
                // TODO Input city name.
                char * s = malloc(sizeof(char) * 16);
                strcpy(s, "NAME");

                createCity(world, s, unit -> r, unit -> c, unit -> owner);
                destroyUnit(world, unit);
                control -> state = CONTROL_MOVE_CURSOR;

                List * list = listCreate();
                listPrepend(list, createMessage(VIEW_REDRAW_ALL));
                return list;
            }
            return NULL;
        }
        return NULL;
    }

    // Cut the forest.
    if((char) key == 'B' || (char) key == 'b')
    {
        if(control -> state == CONTROL_MOVE_UNIT)
        {
            Node * n = getNeighbour(view -> current_cell, EDGE_CELL_UNIT);
            Unit * unit = (Unit *) n -> data;
            UnitCommonInfo * u_info = (UnitCommonInfo *) daGetByIndex(world -> units_info, unit -> unit_id);
            if(
                iaSearchForData(u_info -> privileges, UNIT_PRVL_CHOP_TREES) != -1 &&
                ((Cell *) view -> current_cell -> data) -> territory == CELL_TYPE_TREE
            )
            {
                ((Cell *) view -> current_cell -> data) -> territory = CELL_TYPE_GRASS;
                unit -> owner -> gold += BALANCE_CHOPPING_GAIN;
                unit -> moves = 0;
                List * list = listCreate();
                listPrepend(list, createMessage(VIEW_REDRAW_ALL));
                return list;
            }
            return NULL;
        }
    }

    // Build mine.
    if((char) key == 'M' || (char) key == 'm')
    {
        if(control -> state == CONTROL_MOVE_UNIT)
        {
            Node * n = getNeighbour(view -> current_cell, EDGE_CELL_UNIT);
            Unit * unit = (Unit *) n -> data;
            UnitCommonInfo * u_info = (UnitCommonInfo *) daGetByIndex(world -> units_info, unit -> unit_id);
            Cell * cell = ((Cell *) view -> current_cell -> data);
            if(
                iaSearchForData(u_info -> privileges, UNIT_PRVL_BUILD_MINE) != -1 &&
                cell -> mine == CELL_NO_MINE &&
                cell -> resources != CELL_RES_NONE
            )
            {
                // Create mine.
                cell -> mine = CELL_MINE;
                unit -> owner -> gold -= BALANCE_MINE_COST;
                // Increment player's resources.
                IntArray * resources = unit -> owner -> resources;
                iaIncrementByIndex(resources, cell -> resources, BALANCE_MINE_GAIN);
                control -> state = CONTROL_MOVE_CURSOR;
                destroyUnit(world, unit);
                List * list = listCreate();
                listPrepend(list, createMessage(VIEW_REDRAW_ALL));
                return list;
            }
            return NULL;
        }
    }

    // Scrolling units/cities.
    if((char) key == 'N' || (char) key == 'n')
    {
        // Getting player.
        Player * player = listGetHead(world -> players);
        if(control -> state == CONTROL_MOVE_UNIT)
        {
            // Get unit.
            Node * node = getNeighbour(view -> current_cell, EDGE_CELL_UNIT);
            Unit * unit = (Unit *) node -> data;
            // Scroll player's units list to this unit (player will scroll
            // units from these unit).
            player -> units -> head = getListElementByPointer(player -> units, unit);
            // Scroll next.
            player -> units -> head = player -> units -> head -> next;
            // Focus on this unit.
            unit = (Unit *) player -> units -> head -> data;
            focusOn(world, view, unit -> r, unit -> c);
            // Send message.
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_ALL));
            return list;
        }

        if(control -> state == CONTROL_MOVE_CURSOR)
        {
            // If there is city, start scrolling from this city (like above with
            // units).
            Node * node = getNeighbour(view -> current_cell, EDGE_CELL_CITY);
            if(node != NULL)
            {
                City * city = (City *) node -> data;
                player -> cities -> head = getListElementByPointer(player -> cities, city);
            }
            player -> cities -> head = player -> cities -> head -> next;
            City * city = (City *) player -> cities -> head -> data;
            focusOn(world, view, city -> r, city -> c);
            // Send message.
            List * list = listCreate();
            listPrepend(list, createMessage(VIEW_REDRAW_ALL));
            return list;
        }

    }

    return NULL;
}
