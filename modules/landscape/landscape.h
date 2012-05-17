#ifndef LANDSCAPE
#define LANDSCAPE

#include "../graph/graph.h"
#include "../map/map.h"

/*
    Recursive algorithm to generate random landscape.
        c — point, from where we begin create landscape.
        k — magic coef, that means how many cells we will fill.
        required — value, what we need to fill this cell.
        fill — value, with that we will fill this cell.
*/
void generateLandscape(Node * c, int k, char required, char fill);

/*
    Function generate random landscape and put it in "map".
    Uses generateLandscape function.
*/
void generateMap(Map * map);

#endif
