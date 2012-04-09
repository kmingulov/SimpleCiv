#include <stdlib.h>
#include <time.h>
#include "modules/landscape/landscape.h"
#include "modules/map/map.h"
#include "modules/cui/cui.h"

int main()
{
    // Gt random!
    srand(time(NULL));

    initCUI();

    // Screen sizes.
    int w, h, d;
    getmaxyx(stdscr, w, h);
    d = 0.85 * h;

    // Map sizes.
    int map_w = 250, map_h = 250;

    // Creating map.
    Cell * map = createMap(map_w, map_h);
    generateMap(map, map_w, map_h);

    // Draw interface and map.
    drawInterface(w, h, d);
    drawMap(map, 1, 1, w - 2, d - 1);

    // Coordinates of our cursor.
    int cur_x = 10, cur_y = 10;
    move(cur_x, cur_y);

    // Key code.    
    int key = 0;

    while(true)
    {
        key = getch();

        if(key == KEY_ESCAPE)
        {
            break;
        }

        if(key >= KEY_DOWN && key <= KEY_RIGHT)
        {
            moveCursor(key, w, d, &map, &cur_x, &cur_y);
        }

        // See modules/cui/cui.h for some comments, why we change cur_y and
        // cur_x places and why we write (1 - cur_x), not cur_x - 1.
        Cell * c = getCell(map, cur_y - 1, 1 - cur_x);
        identifyCell(c, h, d);

        move(cur_x, cur_y);
    }

    // All done.
    destroyMap(map);
    deinitCUI();

    return 0;
}
