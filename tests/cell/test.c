#include <stdio.h>
#include <assert.h>

#include "../../game/world/definitions.h"
#include "../../modules/map/map.h"

int main()
{
    Map * map = createMap(10, 10);

    Node * n = map -> head;

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

    assert(getCell(map, 10, 10) == n);

    destroyMap(map);

    // Creating non-square map.
    map = createMap(7, 13);

    assert(getCell(map, 0, 0) == n);
    assert(getCell(map, 7, 0) == n);
    assert(getCell(map, 7, 13) == n);
    assert(getCell(map, 0, 13) == n);

    destroyMap(map);

    return 0;
}
