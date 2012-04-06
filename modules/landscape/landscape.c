#include "landscape.h"
#include <stdlib.h>

void generateLandscape(Cell * c, int k, char required, char fill)
{
    while(k >= 0 && isWhereCell(c, required))
    {
        Cell * neighbor = getCellByNumber(c, rand() % 4);

        if(neighbor -> territory == required)
        {
            k--;
            neighbor -> territory = fill;
            generateLandscape(neighbor, k, required, fill);
        }
    }
}
