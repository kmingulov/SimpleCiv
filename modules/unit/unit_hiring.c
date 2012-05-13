#include <stdlib.h>

#include "unit_hiring.h"

UnitHiring * createHiring()
{
    UnitHiring * res = malloc(sizeof(UnitHiring));

    res -> id = -1;
    res -> turns = 0;
    res -> delta = 0;

    return res;
}

void destroyHiring(UnitHiring * uh)
{
    free(uh);
}
