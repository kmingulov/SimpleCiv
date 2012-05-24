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
#include "controlkeys.h"

Control * createControl()
{
    Control * control = malloc(sizeof(Control));
    control -> state = CONTROL_MOVE_CURSOR;
    return control;
}


char lower ( char s )
{
    if ( s >= 65 && s <= 91 )
            s += 32;
    return s;
}


void destroyControl(Control * control)
{
    free(control);
}


List * scrollingTextbox (View * view, Control * control, int key)
{
    // Scrolling textbox.
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

List * researching (World *world, View * view, Control * control, int key)
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


List * hiring (World *world, View * view, Control * control)
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

List * turning(World * world, View * view, Control * control)
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

List * CannotMove(World * world, View * view, Control * control, int key)
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
    return NULL;
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
                case KEY_UP   : listPrepend(list, createMessage(VIEW_MOVE_CURSOR_TOP)); break;
                case KEY_DOWN : listPrepend(list, createMessage(VIEW_MOVE_CURSOR_BOTTOM)); break;
                case KEY_RIGHT: listPrepend(list, createMessage(VIEW_MOVE_CURSOR_RIGHT)); break;
                case KEY_LEFT : listPrepend(list, createMessage(VIEW_MOVE_CURSOR_LEFT)); break;
            }
            return list;
        }

        // Move unit state.
        if(control -> state == CONTROL_MOVE_UNIT)
            return CannotMove(world, view, control, key);

        // Choosing technology state.
        if(control -> state == CONTROL_CHOOSE_TECH || control -> state == CONTROL_CHOOSE_UNIT)
        {
            List * list = listCreate();
            switch(key)
            {
                case KEY_UP  : listPrepend(list, createMessage(VIEW_CHOOSER_MOVE_CURSOR_TOP));  break;
                case KEY_DOWN: listPrepend(list, createMessage(VIEW_CHOOSER_MOVE_CURSOR_BOTTOM));  break;
            }
            return list;
        }

        // Scrolling textbox.
        if(control -> state == CONTROL_TEXTBOX)
            return scrollingTextbox(view, control, key);
    }

    // Enter.
    if(key == KEY_ENTER_FIXED)
    {
        // Start research.
        if(control -> state == CONTROL_TEXTBOX)
            return researching(world, view, control, key);

        // Start hiring.
        if(control -> state == CONTROL_CHOOSE_UNIT)
            return hiring (world, view, control);

        // End of the turn.
        if(control -> state == CONTROL_MOVE_CURSOR || control -> state == CONTROL_MOVE_UNIT)
            return turning(world, view, control);
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

    char charkey = lower((char) key);
    switch (charkey)
    {
        case 't': return(pushKeyT(world, view, control));        break;
        case 'q': return(pushKeyQ(view, control));               break;
        case 'h': return(pushKeyH(view, control));               break;
        case 'i': return(pushKeyI(world, view, control));        break; // Showing unit info.
        case 'c': return(pushKeyC(world, view, control));        break; // Create city.
        case 'b': return(pushKeyB(world, view, control));        break; // Cut the forest.
        case 'n': return(pushKeyN(world, view, control));        break;
        case 'm': return(pushKeyM(world, view, control));        break;
    };
    return NULL;
}

