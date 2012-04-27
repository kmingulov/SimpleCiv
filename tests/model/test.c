#include <stdio.h>
#include <stdlib.h>
#include "../../game/world/world.h"

int main()
{
    // In future we will parse it all from config file.
    WorldProperties * properties = malloc(sizeof(WorldProperties));
    properties -> map_w = 10;
    properties -> map_h = 10;
    properties -> players_count = 5;
    properties -> player_names = daCreate();

    for(int i = 0; i < 5; i++)
    {
        char * name = malloc(sizeof(char) * 8);
        name[0] = 'P'; name[1] = 'l'; name[2] = 'a'; name[3] = 'y'; name[4] = 'e'; name[5] = 'r';
        name[6] = 49 + i; name[7] = '\0';
        daPrepend(properties -> player_names, name);
    }

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
