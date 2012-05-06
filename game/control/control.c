#include <stdlib.h>
#include <ncurses.h>

#include "../view/definitions.h"
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

Message * controlProcess(World * world, Control * control, int key)
{
    // Arrow keys.
    if(key == KEY_UP || key == KEY_DOWN || key == KEY_RIGHT || key == KEY_LEFT)
    {
        // Move cursor state.
        if(control -> state == CONTROL_MOVE_CURSOR)
        {
            if(key == KEY_UP)
            {
                return createMessage(VIEW_MOVE_CURSOR_TOP,    NULL);
            }
            else if(key == KEY_DOWN)
            {
                return createMessage(VIEW_MOVE_CURSOR_BOTTOM, NULL);
            }
            else if(key == KEY_RIGHT)
            {
                return createMessage(VIEW_MOVE_CURSOR_RIGHT,  NULL);
            }
            else if(key == KEY_LEFT)
            {
                return createMessage(VIEW_MOVE_CURSOR_LEFT,   NULL);
            }
        }
    }

    return NULL;
}
