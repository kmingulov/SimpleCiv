#ifndef MODEL
#define MODEL

#include "../../modules/dyn_array/dyn_array.h"
#include "../../modules/graph/graph.h"
#include "../../modules/map/map.h"
#include "../../modules/landscape/landscape.h"
#include "../../modules/player/player.h"

/*
    Defines for nodes' types.
*/

// For map.
#define NODE_CELL          1

// For player.
#define NODE_PLAYER        2
#define NODE_CITIES        3
#define NODE_UNITS         4
#define NODE_TECH_TABLE    5

// For technologies.
#define NODE_TECHNOLOGY    6

/*
    Defines for edges' types.
*/

// For map.
#define EDGE_CELL_CITY     1
#define EDGE_CELL_UNIT     2

// For players.
#define EDGE_NEXT_PLAYER   3

// For technologies.
#define EDGE_TECH_PROVIDES 4
#define EDGE_TECH_REQUIRES 5

// Struct of model properties.
typedef struct ModelProperties
{
    // World width and height.
    int map_w, map_h;
    // Players' count.
    int players_count;
    // And their names.
    DynArray * player_names;
} ModelProperties;

// Struct of model.
typedef struct Model
{
    // Game graph.
    Node * graph_head;

    // Game (static) map.
    Cell * map_head;
} Model;

/*
    Creates model of the game with properties.
*/
Model * createModel(ModelProperties * properties);

/*
    Destroy model.
*/
void destroyModel(Model * model, ModelProperties * properties);

#endif
