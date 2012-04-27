#include <stdio.h>
#include <stdlib.h>
#include "../../game/world/world.h"

int main()
{
    FILE * map;
    map = fopen("map.xml", "w");

    // We will parse it all from config file.
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

    World * world = createWorld(properties);

    //saveWorld(world, properties, map);

    destroyWorld(world, properties);
    fclose(map);

    return 0;
}
