

#include <stdlib.h>

#include "fog.h"
#include "../int_array/int_array.h"


FogOfWar * fogCreate(int r, int c)
{
    FogOfWar * fog = malloc(sizeof(FogOfWar));
    fog -> rows = daCreate();
    for(int i = 0; i < r; i++)
    {
        daPrepend(fog -> rows, iaLengthCreate(c));
    }
    return fog;
}


void DestroyFog(FogOfWar * fog)
{
    for (int i = 0; i < fog -> rows -> length; i++)
    {
        iaDestroy(daGetByIndex(fog -> rows, i));
    }
    daDestroy(fog -> rows,&free);
    free(fog);
}


void updateFog(FogOfWar * fog, int r, int c)
{
    iaSetByIndex(daGetByIndex(fog -> rows, r), c, 1);
}

int IsKnownFog(FogOfWar * fog, int r, int c)
{
    if(iaGetByIndex(daGetByIndex(fog -> rows, r),c))
    {
        return 1;
    }
    return 0;
}
