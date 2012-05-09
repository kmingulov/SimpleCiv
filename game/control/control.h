#ifndef CONTROL
#define CONTROL

#include "../message/message.h"

#include "../../modules/player/player.h"
#include "../../modules/unit/unit.h"
#include "../../modules/city/city.h"
#include "../../modules/list/list.h"

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
