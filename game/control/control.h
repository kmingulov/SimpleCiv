#ifndef CONTROL
#define CONTROL

#include "../../player/player.h"
#include "../../unit/unit.h"
#include "../../city/city.h"

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

#endif
