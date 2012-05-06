#ifndef CONTROL
#define CONTROL

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

#endif
