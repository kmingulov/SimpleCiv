#ifndef UNIT
#define UNIT

#include "../../game/world/world.h"

#include "../int_array/int_array.h"
#include "../dyn_array/dyn_array.h"
#include "../player/player.h"

/*
    This struct of real unit, who live in our world.
*/
typedef struct Unit
{
    unsigned char unit_id;   // Unit id in units' info table.
    Player * owner;          // Owner of this unit.
    int r, c;                // X and Y coordinates.
    int health;              // Current health.
    unsigned int moves;      // Available moves.
} Unit;

/*
    Creates new unit in world in row r, column c. Id of unit is unit_id and
    owner is player.
*/
Unit * createUnit(World * world, unsigned int r, unsigned int c, unsigned char unit_id, Player * player);

/*
    Destroys unit.
*/
void destroyUnit(World * world, Unit * unit);

/*
    Figth between two units.
*/
void unitsFight(World * world, Unit ** unit1, Unit ** unit2);

/*
    Treats units at the end of a course
*/
void developUnit(void * data, DynArray * info);

/*
    Moves unit. Returns 0 if failed, 1 if moved succefully, 2 if there was a
    fight.
*/
int moveUnit(World * world, Node * current_cell, int direction);

#endif
