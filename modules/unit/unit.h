#ifndef UNIT
#define UNIT
/*
    This is struct of unit. It's really similar to technology struct (see
    modules/technology/technology.h file).
    Each player also will have table with technologies' id and value.
    Also there will be a common for all players table with these values: hp,
    damage, etc.
*/
typedef struct Unit
{
	int id;
} Unit;

#endif
