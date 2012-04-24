#include "landscape.h"
#include <stdlib.h>
#include <math.h>

void generateLandscape(Cell * c, int k, char required, char fill)
{
    while(k >= 0 && isWhereCell(c, required))
    {
        Cell * neighboor = getCellByNumber(c, rand() % 4);

        if(neighboor -> territory == required)
        {
            k--;
            neighboor -> territory = fill;
            generateLandscape(neighboor, k, required, fill);
        }
    }
}

void generateMap(Cell * map, int w, int h)
{
    // Magic numbers. Found by logarithmical approximation k = f( sqrt(w * h) ).
    // sqrt(w * h) is the characteristic size of map.

    // TODO 24.04.12. I've played with coefs and make them acceptable for maps
    // with sqrt(w * h) < 1000. Maybe it will be good to implement a Perlin 
    // noise instead?
    int k = round( (float) 102.4540490757f * log(sqrt(w * h)) - 409.3374246835f );
    int dk = 2;
    // 3kn = 0,8WH, 20% is water.
    int n = round( (float) 0.8f * w * h / k / 3 );

    // j is type of adding territory.
    // i — one of points, from where we start generateLandscape().
    for(int j = 1; j < 5; j++)
    {
        for(int i = 0; i < n; i++)
        {
            Cell * c = getCell(map, rand() % h, rand() % w);
            generateLandscape(c, k - i * dk, j - 1, j);
        }
    }
}
