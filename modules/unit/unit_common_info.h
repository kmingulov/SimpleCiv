#ifndef UNIT_COMMON_INFO
#define UNIT_COMMON_INFO

#include "../int_array/int_array.h"

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
    // Unit's name.
    char * name;
    // Unit's char.
    char c;
    // Stats.
    unsigned int max_health;
    unsigned int max_damage;
    unsigned int max_moves;
    unsigned int hiring_turns;
    unsigned int gold_drop;
    // Privileges and required resources.
    IntArray * privileges;
    IntArray * resources;
} UnitCommonInfo;

/*
    Creates UnitCommonInfo.
*/
UnitCommonInfo * createUnitCommonInfo();

/*
    Destroys UnitCommonInfo variable.
*/
void destroyUnitCommonInfo(void * data);

#endif
