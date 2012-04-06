#ifndef LANDSCAPE
#define LANDSCAPE

#include "../map/map.h"

/*
    Recursive algorithm to generate random landscape.
        c — point, from where we begin create landscape.
        k — magic coef, that means how many cells we will fill.
        required — value, what we need to fill this cell.
        fill — value, with that we will fill this cell.
*/
void generateLandscape(Cell * c, int k, char required, char fill);

#endif
