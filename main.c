#include <stdio.h>
#include <stdlib.h>

#include "game/world/world.h"
#include "game/view/view.h"

int main()
{

    // Creating world and view and control.
    World * world = createWorld();
    View * view = createView();
    //Control * control = createControl();

    if(world == NULL || view == NULL /* || control == NULL */)
    {
        printf("An error has occurred. Terminating.\n");
        return 1;
    }



    drawView(view);
    drawMap(world->graph_map, view);



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
            /*
            moveCursor();
            drawCellInfo();
            */
        }
    }




    // Destroing everything.
    destroyWorld(world);
    destroyView(view);
    //destroyControl(control);


    return 0;
}
