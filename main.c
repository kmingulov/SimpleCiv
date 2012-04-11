#include <stdlib.h>
#include <time.h>
#include "modules/landscape/landscape.h"
#include "modules/map/map.h"
#include "modules/players/players.h"
#include "modules/cui/cui.h"

int main()
{
    // Initialize random.
    srand(time(NULL));
///gfsdgs
    // Creating map.
    int map_w = 250, map_h = 250;
    Cell * map = createMap(map_w, map_h);
    generateMap(map, map_w, map_h);

    // Initialize CUI and create interface settings' variable.
    initCUI();
    Interface iface = createInterface();

    // Draw interface and map.
    drawInterface(&iface);
    drawMap(map, &iface);

    // Key code.    
    int key = 0;

    while(true)
    {
        move(iface.cur_r, iface.cur_c);

        key = getch();

        if(key == KEY_ESCAPE)
        {
            break;
        }

        if(key >= KEY_DOWN && key <= KEY_RIGHT)
        {
            moveCursor(key, &iface, &map);
            // See modules/cui/cui.h for some comments, why we change cur_c and
            // cur_r places and why we write (1 - cur_r), not cur_r - 1.
            Cell * c = getCell(map, iface.cur_c - 1, 1 - iface.cur_r);
            drawCellInfo(c, &iface);
        }
    }

    // All done.
    deinitCUI();
    destroyMap(map);

    return 0;
}
