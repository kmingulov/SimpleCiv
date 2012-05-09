#ifndef UNIT
#define UNIT

#include "../../game/world/world.h"

#include "../int_array/int_array.h"
#include "../dyn_array/dyn_array.h"
#include "../player/player.h"

/*
    This is struct of unit. It's really similar to technology struct (see
    modules/technology/technology.h file).
    This struct for units' info table (common for all players).
    Each player also will have table with technologies' id and value.
    Also there will be a common for all players table with these values: hp,
    damage, etc.
*/

typedef struct UnitCommonInfo
{
    char * name;
    char c;
    unsigned int max_health;
    unsigned int max_damage;
    unsigned int max_moves;
} UnitCommonInfo;

/*
    This struct of real unit, who live in our world.
*/
typedef struct Unit
{
    unsigned char unit_id;   // Unit id in units' info table.
    Player * owner;          // Owner of this unit.
    unsigned int r, c;       // X and Y coordinates.
    unsigned int health;     // Current health.
    unsigned int moves;      // Available moves.
} Unit;

/*
    Creates UnitCommonInfo.
*/
UnitCommonInfo * createUnitCommonInfo();

/*
    Destroys UnitCommonInfo variable.
*/
void destroyUnitCommonInfo(void * data);

/*
    Creates unit table.
*/
IntArray * createUnitStatus(IntArray * techs_status, DynArray * techs_info, DynArray * units_info);

/*
    Creates new unit in world in row r, column c. Id of unit is unit_id and
    owner is player.
*/
Unit * createUnit(World * world, unsigned int r, unsigned int c, unsigned char unit_id, Player * player);

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
