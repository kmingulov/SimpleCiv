


#include "ssp.h"
#include "../dyn_array/dyn_array.h"
#include "../int_array/int_array.h"


static int normalize(int x, int b)
{
    // Check for bounds.
    while(x < 0)
    {
        x += b;
    }

    while(x >= b)
    {
        x -= b;
    }
    return x;
}

void setCell(DynArray *da,unsigned int r, unsigned int c, Map * map)
{
    int count = iaGetByIndex(daGetByIndex(da, r), c);
    count++;

    int r_dir[4] = {r  , r  , r+1, r-1};
    int c_dir[4] = {c+1, c-1, c  , c  };

    for (int i = 0; i<4; i++)
    {
        r_dir[i] = normalize(r, map -> max_r);
        c_dir[i] = normalize(c, map -> max_r);
        iaSetByIndex(daGetByIndex(da, r_dir[i]), c_dir[i], count);
        setCell(da, r_dir[i], r_dir[i],map);
    }
}

DynArray* ssp (unsigned int r, unsigned int c, Map *map)
{
    DynArray * da = daCreate();
    for(int i = 0; i < map -> max_r; i++)
    {
        // iaLengthCreate() creates array with length c and this array is
        // already null'd (each element == 0). So there is no need in it's
        // initialization.

        IntArray * row = iaCreate();
        for (int j = 0; j < map -> max_r; j++)
        {
            iaPrepend(row, -1);
        }
        // Prepend row.
        daPrepend(da, row);
    }
    setCell(da,r,c,map);
    return da;
}
