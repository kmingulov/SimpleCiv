#ifndef LANDSCAPE
#define LANDSCAPE

#include "../cell/cell.h"

/*
    Recursive algorithm to generate random landscape.
        c — point, from where we begin create landscape.
        k — magic coef, that means how many cells we will fill.
        required — value, what we need to fill this cell.
        fill — value, with that we will fill this cell.
*/
//void generateLandscape(Cell * c, int k, char required, char fill);

void generateLandscape(Node * map_head, int w, int h, double p);

/*
    Function generate random landscape and put it in fourly circular list "map".
    Ints w and h are map width and height respectively.
    Uses generateLandscape function.
*/
//void generateMap(Cell * map, int w, int h);

#endif
