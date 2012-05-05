#include <stdio.h>
#include <assert.h>
#include "../../modules/cell/cell.h"

int main()
{
    Node * n = createMap(10, 10);

    // Testing all directions.
    unsigned char a[4] = {EDGE_CELL_RIGHT, EDGE_CELL_LEFT, EDGE_CELL_TOP, EDGE_CELL_BOTTOM};
    for(int i = 0; i < 4; i++)
    {
        Node * temp = n;
        for(int j = 0; j < 10; j++)
        {
            temp = getNeighbour(temp, a[i]);
        }
        assert( temp == n );
    }

    assert(getCell(n, 10, 10) == n);

    destroyMap(n, 10, 10);

    // Creating non-square map.
    n = createMap(7, 13);

    assert(getCell(n, 0, 0) == n);
    assert(getCell(n, 7, 0) == n);
    assert(getCell(n, 7, 13) == n);
    assert(getCell(n, 0, 13) == n);

    destroyMap(n, 7, 13);

    return 0;
}
