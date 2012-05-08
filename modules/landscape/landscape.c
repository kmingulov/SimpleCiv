#include "landscape.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void generateLandscape(Node * c, int k, char required, char fill)
{
    unsigned char directions[4] = {EDGE_CELL_RIGHT, EDGE_CELL_LEFT,
        EDGE_CELL_BOTTOM, EDGE_CELL_TOP};
    int tries = 4;
    while(k >= 0 && tries >= 0)
    {
        tries--;
        Node * neighbour = getNeighbour(c, directions[rand() % 4]);

        if( ((Cell *) neighbour -> data) -> territory == required )
        {
            k--;
            ( (Cell *) neighbour -> data) -> territory = fill;
            generateLandscape(neighbour, k, required, fill);
        }
    }
}

void generateMap(Node * map, int max_r, int max_c)
{
    unsigned char territories[4] = {CELL_TYPE_WATER, CELL_TYPE_TREE,
        CELL_TYPE_HILL, CELL_TYPE_MOUNTAIN};
    unsigned char required[4] = {CELL_TYPE_GRASS, CELL_TYPE_GRASS,
        CELL_TYPE_GRASS, CELL_TYPE_HILL};

    srand(time(NULL));

    Node * current = map;

    // Filling up by default type of territory (grass).
    for(int i = 0; i < max_r; i++)
    {
        for(int j = 0; j < max_c; j++)
        {
            ((Cell *) current -> data) -> territory = CELL_TYPE_GRASS;
            current = getNeighbour(current, EDGE_CELL_RIGHT);
        }
        current = getNeighbour(current, EDGE_CELL_BOTTOM);
    }

    // Generating landscape.
    for(int i = 0; i < 4; i++)
    {
        int n = 7;
        int k = pow(2, n);
        for(int j = 0; j < n; j++)
        {
            Node * c = getCell(map, rand() % max_r, rand() % max_c);
            generateLandscape(c, k, required[i], territories[i]);
            k /= 2;
        }
    }

    // Generating resources.
    unsigned char resources[CELL_RES_COUNT] = {CELL_RES_BRONZE, CELL_RES_IRON,
        CELL_RES_COAL, CELL_RES_GUNPOWDER, CELL_RES_HORSES};
    for(int i = 0; i < max_r; i++)
    {
        for(int j = 0; j < max_c; j++)
        {
            Cell * c = (Cell *) current -> data;
            if(c -> territory != CELL_TYPE_WATER)
            {
                int random = rand() % 3;
                if(random == 2)
                {
                    c -> resources = resources[rand() % CELL_RES_COUNT];
                }
            }
            current = getNeighbour(current, EDGE_CELL_RIGHT);
        }
        current = getNeighbour(current, EDGE_CELL_BOTTOM);
    }

    // Putting mushrooms on the map.
    int r;
    int c;
    do
    {
        r = rand () % max_r;
        c = rand () % max_c;
    } while( ((Cell *) getCell(current, r, c) -> data) -> territory == CELL_TYPE_WATER );
    ((Cell *) getCell(current, r, c) -> data) -> resources = CELL_RES_MUSHROOMS;    
}

/*
    Big chunk of code, where I tried to implement Perlin noise for cycled map.

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
    s = noiseRand(floorx,  floory); 
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

    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
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
            printf("%d ", (int) round(cur_noise));
        }
        printf("\n");
    }
}

*/
