

#include <stdlib.h>

#include "fog.h"
#include "../int_array/int_array.h"


FogOfWar * fogCreate()
{
    FogOfWar * fog = malloc(sizeof(FogOfWar));

    return fog;
}


void DestroyFog(FogOfWar * fog)
{
    iaDestroy(fog -> r);
    iaDestroy(fog -> c);
    free(fog);
}


void updateFog(FogOfWar * fog, int r, int c)
{
    iaSetByIndex(fog -> r, r, 1);
    iaSetByIndex(fog -> c, c, 1);
}

int IsKnownFog(FogOfWar * fog, int r, int c)
{
    if(
        iaGetByIndex(fog -> r, r) != 0  &&
        iaGetByIndex(fog -> c, c) != 0
    )
    {
        return 1;
    }
    return 0;
}
