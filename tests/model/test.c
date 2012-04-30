#include <stdio.h>
#include <stdlib.h>

#include "../../game/world/world.h"
#include "../../modules/parser/xml.h"

int main()
{
    // Parse settings from config file.
    WorldProperties * properties = parseConfig("../../config.xml");

    // Creating world.
    World * world = createWorld(properties);

    // Saving world.
    FILE * map;
    map = fopen("map.xml", "w");
    saveWorld(world, properties, map);
    fclose(map);

    // Destroing world.
    destroyWorld(world, properties);

    return 0;
}
