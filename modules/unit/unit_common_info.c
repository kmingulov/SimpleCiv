#include <stdlib.h>

#include "unit_common_info.h"

UnitCommonInfo * createUnitCommonInfo()
{
    UnitCommonInfo * unit = malloc(sizeof(UnitCommonInfo));

    unit -> name = NULL;
    unit -> max_health = 0;
    unit -> max_damage = 0;
    unit -> max_moves = 0;
    unit -> hiring_turns = 0;
    unit -> gold_drop = 0;
    unit -> privileges = NULL;
    unit -> resources = NULL;

    return unit;
}

void destroyUnitCommonInfo(void * data)
{
    UnitCommonInfo * unit = (UnitCommonInfo *) data;

    free(unit -> name);

    if(unit -> privileges != NULL)
    {
        iaDestroy(unit -> privileges);
    }

    if(unit -> resources != NULL)
    {
        iaDestroy(unit -> resources);
    }

    free(unit);
}
