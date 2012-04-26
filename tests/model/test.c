#include <stdio.h>
#include <stdlib.h>
#include "../../game/model/model.h"

int main()
{
    FILE * map;
    map = fopen("map.xml", "w");

    // We will parse it all from config file.
    ModelProperties * properties = malloc(sizeof(ModelProperties));
    properties -> map_w = 1000;
    properties -> map_h = 1000;
    properties -> players_count = 5;
    properties -> player_names = daCreate();

    for(int i = 0; i < 5; i++)
    {
        char * name = malloc(sizeof(char) * 8);
        name[0] = 'P'; name[1] = 'l'; name[2] = 'a'; name[3] = 'y'; name[4] = 'e'; name[5] = 'r';
        name[6] = 49 + i; name[7] = '\0';
        daPrepend(properties -> player_names, name);
    }

    Model * model = createModel(properties);

    saveModel(model, properties, map);

    destroyModel(model, properties);
    fclose(map);

    return 0;
}
