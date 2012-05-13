#ifndef WORLD_PROPERTIES
#define WORLD_PROPERTIES

#include "../../modules/dyn_array/dyn_array.h"

/*
    Struct of world properties.
*/
typedef struct WorldProperties
{
    // Count of rows and columns in map.
    int map_r, map_c;

    // Players' count.
    int players_count;

    // And their names and city's names.
    DynArray * player_names;
    DynArray * player_cities;
} WorldProperties;

#endif
