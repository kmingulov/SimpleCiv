#include <stdio.h>
#include <stdlib.h>

#include "game/world/world.h"
#include "game/view/view.h"
#include "game/control/control.h"

#include "modules/list/list.h"
#include "game/message/message.h"

int main()
{
    // Creating world and view and control.
    World * world = createWorld();
    View * view = createView(world);
    Control * control = createControl();

    if(world == NULL || view == NULL || control == NULL)
    {
        printf("An error has occurred. Terminating.\n");
        return 1;
    }



    List * queue = listCreate();
    listPrepend(queue, createMessage(VIEW_REDRAW_ALL, NULL));
    int key = 0;
    while(true)
    {
        // Process view. Redraw some elements. Depends on action = control's
        // decision what view need to redraw.
        if(viewProcess(world, view, queue) == 0)
        {
            // Good bye.
            break;
        }

        // Reading key.
        key = getch();

        // Process control. Does something with world. Depends on key.
        queue = controlProcess(world, view, control, key);
    }



    // Destroing everything.
    destroyControl(control);
    destroyView(view);
    destroyWorld(world);



    return 0;
}
