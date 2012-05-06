#ifndef CONTROL
#define CONTROL

#include "../message/message.h"

#include "../../modules/player/player.h"
#include "../../modules/unit/unit.h"
#include "../../modules/city/city.h"

typedef struct Control
{
    // State of the control.
    unsigned char state;

    // Current player.
    Player * cur_player;

    // Current unit and city.
    City * cur_city;
    Unit * cur_unit;
} Control;

/*
    Process control and returns a message for view.
*/
Message * controlProcess(World * world, Control * control, char key);

#endif
