#ifndef PLAYERS
#define PLAYERS

typedef struct Player
{
    // _Unique_ number of this player. Probably, it will be used for game saves.
    int id;
    // Name of player, used only for gamer's convenience.
    char * name;
    // Array of player's units (type: Unit, not UnitCommonInfo!).
    DynArray * units;
    // Arrays of available units and technologies.
    DynArray * available_units;
    DynArray * available_techs;
    // TODO Add city struct and DynArray of cities.
} Player;

#endif
