#include "landscape.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

double noiseRand(double x, double y)
{
    int n = (int) x + (int) y * 57;
    n = (n << 13) ^ n;
    int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
    return 1.0 - ((double) nn / 1073741824.0);
}

double noiseInterpolate(double a, double b, double x)
{
    double ft = x * 3.1415;
    double f = (1.0 - cos(ft)) * 0.5;
    return a * (1.0 - f) + b * f;
}

double noise(double x, double y)
{
    double floorx = (double) ((int) x);
    double floory = (double) ((int) y);
    double s, t, u, v;
    s = noiseRand(floorx,     floory); 
    t = noiseRand(floorx + 1, floory);
    u = noiseRand(floorx,     floory + 1);
    v = noiseRand(floorx + 1, floory + 1);
    double int1 = noiseInterpolate(s, t, x - floorx);
    double int2 = noiseInterpolate(u, v, x - floorx);
    return noiseInterpolate(int1, int2, y - floory);
}

void generateLandscape(Node * map_head, int w, int h, double p)
{
    Node * current = map_head;
    int octaves = 5;

    srand(time(NULL));

    double max = -100, min = 100;

    for(int i = h; i < 2*h; i++)
    {
        for(int j = w; j < 2*w; j++)
        {
            // Calculating the noise.
            double cur_noise = 0;
            for(int k = 0; k < octaves - 1; k++)
            {
                double frequency = pow(2, k);
                double amplitude = pow(p, k);
                double x = ((double) j) * frequency, y = ((double) i) * frequency;
                //printf("%lf %lf\n", x, y);
                cur_noise += noise(x, y) * amplitude;
            }
            if(cur_noise < min)
            {
                min = cur_noise;
            }
            if(cur_noise > max)
            {
                max = cur_noise;
            }
            // Update node.
            printf("%lf ", cur_noise);
        }
        printf("\n");
    }
}


/*void generateLandscape(Cell * c, int k, char required, char fill)
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
}*/
