#include <stdlib.h>

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

Message * controlProcess(World * world, Control * control, char key)
{
    // It's temporary %)
    return NULL;
}
