#ifndef CONTROL
#define CONTROL

#include "../../modules/list/list.h"
#include "../message/message.h"
#include "../world/world.h"
#include "../view/view.h"

typedef struct Control
{
    // State of the control.
    unsigned char state;
} Control;

/*
    Creates control.
*/
Control * createControl();

/*
    Destroys control.
*/
void destroyControl(Control * control);

/*
    Process control and returns a message for view.
*/
List * controlProcess(World * world, View * view, Control * control, int key);

#endif
