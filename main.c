#include <stdio.h>
#include <stdlib.h>

#include "game/world/world.h"
#include "modules/view/view.h"

int main()
{
    // Creating world and view.
    World * world = createWorld();
    View * view = createView();

    if(world == NULL || view == NULL)
    {
        printf("An error has occurred. Terminating.\n");
        return 1;
    }

    //~ drawInterface(&view->iface);
    //~ drawMap(world->graph_map, &view->iface);

    // Destroing everything.
    destroyWorld(world);
    destroyView(view);

    return 0;
}
