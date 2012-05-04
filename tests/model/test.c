#include <stdio.h>
#include <stdlib.h>

#include "../../game/world/world.h"
#include "../../modules/parser/string_functions.h"

#include "../../modules/parser/xml.h"
#include "../../modules/technology/technology.h"

#include "../../modules/view/view.h"



void techForeachNeighbour(Node * parent, Node * child, Edge * link)
{
    Technology * t1 = (Technology *) parent -> data;
    Technology * t2 = (Technology *) child -> data;
    printf("%s ---%d--> %s\n", t1 -> name, link -> type, t2 -> name);
}

int main()
{
    // Creating world.
    World * world = createWorld();

    if(world == NULL)
    {
        printf("An error has occurred. Terminating.\n");
        return 1;
    }

    View * view = createView();

    if(view == NULL)
    {
        printf("An error has occurred. Terminating.\n");
        return 1;
    }

    //~ drawInterface(&view->iface);
    //~ drawMap(world->graph_map, &view->iface);


    /*foreachNeighbour(world -> techs_tree, &techForeachNeighbour);
    printf("\n");

    foreachNeighbour(((TechnologyCommonInfo *) world -> techs_info -> data[0]) -> tech_in_tree, &techForeachNeighbour);
    printf("\n");

    foreachNeighbour(((TechnologyCommonInfo *) world -> techs_info -> data[1]) -> tech_in_tree, &techForeachNeighbour);
    printf("\n");*/

    // Destroing world.
    destroyWorld(world);
    destroyView(view);

    return 0;
}
