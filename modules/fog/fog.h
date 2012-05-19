#ifndef __VIEW_FOG_H
#define __VIEW_FOG_H

#include "../int_array/int_array.h"

typedef struct FogOfWar
{
    IntArray * r;
    IntArray * c;

} FogOfWar;


/*
    Creates fog of war.
*/
FogOfWar * fogCreate();


/*
    Destroy.
*/
void DestroyFog(FogOfWar * fog);


void updateFog(FogOfWar * fog, int r, int c);

int IsKnownFog(FogOfWar * fog, int r, int c);


#endif



