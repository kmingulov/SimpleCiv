#include <stdio.h>
#include <stdlib.h>

#include "game/world/world.h"
#include "game/view/view.h"

#include "game/message/message.h"

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





    unsigned char key;
    while(true)
    {
        key = getch();

        //~ // Good bye.
        if(key == KEY_ESCAPE)
        {
            break;
        }

        // Process control. Does something with world. Depends on key.
        // int action = controlProcess(world, control, key);
        // Process view. Redraw some elements. Depends on action = control's
        // decision what view need to redraw.
        // viewProcess(world, view, action);
        //int action = controlProcess(world, control, key);

        // test
        if(key == 9)  // TAB
        {
            viewProcess(world, view, 0);
        }
    }



    // Destroing everything.
    destroyWorld(world);
    destroyView(view);
    //destroyControl(control);



    return 0;
}
