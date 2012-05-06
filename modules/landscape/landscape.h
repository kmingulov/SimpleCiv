#ifndef LANDSCAPE
#define LANDSCAPE

#include "../graph/graph.h"
#include "../cell/cell.h"

/*
    Recursive algorithm to generate random landscape.
        c — point, from where we begin create landscape.
        k — magic coef, that means how many cells we will fill.
        required — value, what we need to fill this cell.
        fill — value, with that we will fill this cell.
*/
void generateLandscape(Node * c, int k, char required, char fill);

/*
    Function generate random landscape and put it in fourly circular list "map".
    Ints max_r and max_c are count of rows and columns.
    Uses generateLandscape function.
*/
void generateMap(Node * map, int max_r, int max_c);

#endif
