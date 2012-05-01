#include <stdio.h>
#include <stdlib.h>

#include "../../game/world/world.h"
#include "../../modules/parser/string_functions.h"

#include "../../modules/parser/xml.h"
#include "../../modules/technology/technology.h"

int main()
{
    // Creating world.
    World * world = createWorld();

    if(world == NULL)
    {
        printf("An error has occurred. Terminating.\n");
        return 1;
    }

    // Destroing world.
    destroyWorld(world);

    return 0;
}
