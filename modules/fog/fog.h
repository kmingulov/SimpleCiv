#ifndef __VIEW_FOG_H
#define __VIEW_FOG_H

#include "../int_array/int_array.h"
#include "../dyn_array/dyn_array.h"

typedef struct FogOfWar
{
    DynArray * rows;
} FogOfWar;


/*
    Creates fog of war.
*/
FogOfWar * fogCreate(int r, int c);


/*
    Destroy.
*/
void DestroyFog(FogOfWar * fog);


void updateFog(FogOfWar * fog, int r, int c);

int IsKnownFog(FogOfWar * fog, int r, int c);


#endif



