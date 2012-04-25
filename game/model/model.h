#ifndef MODEL
#define MODEL

// Model defines (for graph's edges).
#define TYPE_PLAYER 1
#define TYPE_CELL   2

#define PLAYER_NEXT 11

#include "../../modules/dyn_array/dyn_array.h"
#include "../../modules/graph/graph.h"
#include "../../modules/map/map.h"
#include "../../modules/landscape/landscape.h"
#include "../../modules/player/player.h"

typedef struct ModelProperties
{
    // World width and height.
    int map_w, map_h;
    // Players' count.
    int players_count;
    // And their names.
    DynArray * player_names;
} ModelProperties;

typedef struct Model
{
    // Game graph.
    Node * graph_head;

    // Game (static) map.
    Cell * map_head;
} Model;

Model * createModel(ModelProperties * properties);

void destroyModel(Model * model, ModelProperties * properties);

#endif
