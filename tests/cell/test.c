#include <stdio.h>
#include <assert.h>
#include "../../modules/cell/cell.h"

int main()
{
    Node * n = createMap(3, 3);

    // Testing all directions.
    unsigned char a[4] = {EDGE_CELL_RIGHT, EDGE_CELL_LEFT, EDGE_CELL_TOP, EDGE_CELL_BOTTOM};
    for(int i = 0; i < 4; i++)
    {
        Node * temp = n;
        for(int j = 0; j < 3; j++)
        {
            temp = getNeighbour(temp, a[i]);
        }
        assert( temp == n );
    }

    /*
        Destroy map.
        TODO Valgrind shows many notices about destroyMap() like this:

            Invalid read of size 1
                at 0x8048B36: destroyGraph (graph.c:54)

            Address 0x41c1cc1 is 1 bytes inside a block of size 12 free'd
                at 0x402540C: free (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
                by 0x8048B7B: destroyGraph (graph.c:64)

        I don't know what to do with it :(
    */
    destroyMap(n);

    return 0;
}
