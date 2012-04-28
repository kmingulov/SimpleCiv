#ifndef MODEL
#define MODEL

#include <stdio.h>
#include <stdlib.h>

#include "definitions.h"
#include "../../modules/dyn_array/dyn_array.h"
#include "../../modules/graph/graph.h"
#include "../../modules/cell/cell.h"
#include "../../modules/player/player.h"

/*
    Struct of world properties.
*/
typedef struct WorldProperties
{
    // World width and height.
    int map_w, map_h;
    // Players' count.
    int players_count;
    // And their names.
    DynArray * player_names;
} WorldProperties;

/*
    Struct of model.
*/
typedef struct World
{
    // Game graph.
    Node * graph_head; // Players.
    Node * map_head;   // Map.

    // Technology tree. Type of each node is struct Technology.
    Node * tech_head;

    // Common info about technologies and units.
    DynArray * units_info; // Type — UnitCommonInfo.
    DynArray * techs_info; // Type — now char * (name of technology).
} World;

/*
    Creates model of the game with specified properties.
*/
World * createWorld(WorldProperties * properties);

/*
    Destroy model.
*/
void destroyWorld(World * world, WorldProperties * properties);

/*
    Save world to xml files.
    TODO This is _just_ draft. In future this function will receive char * name,
    save world to several xml files and add them to tar.gz (or any other)
    archive. So variable FILE * map_file is temporary.
*/
void saveWorld(World * world, WorldProperties * properties, FILE * map_file);

#endif
