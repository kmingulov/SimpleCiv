#include <string.h>
#include <stdlib.h>

#include "../view/view_textbox.h"

#include "controlkeys.h"
#include "control.h"
#include "definitions.h"


List * pushKeyT(World * world, View * view, Control * control)
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
    return NULL;
}



List * pushKeyQ(View * view, Control * control)
{
    // Trying to escape?
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
    return NULL;
}


List * pushKeyH (View * view, Control * control)
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
    return NULL;
}


List * pushKeyI (World * world, View * view,  Control * control)
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
    return NULL;
}




List * pushKeyC (World * world, View * view, Control * control)
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

List * pushKeyB (World * world, View * view,  Control * control)
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
    return NULL;
}
List * pushKeyN (World * world, View * view,  Control * control)
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
    return NULL;
}

List * pushKeyM (World * world, View * view,  Control * control)
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
    return NULL;

}

