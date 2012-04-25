#include "model.h"

Model * createModel(ModelProperties * properties)
{
    // Creates model.
    Model * model = malloc(sizeof(Model));

    // Creates map.
    model -> map_head = createMap(properties -> map_w, properties -> map_h);
    generateMap(model -> map_head, properties -> map_w, properties -> map_h);

    // Creates players list.
    Node * head = NULL; // Graph head.
    Node * temp = NULL; // Temporary variable.
    for(int i = 0; i < properties -> players_count; i++)
    {
        // Create new player.
        Player * data = malloc(sizeof(Player));
        // Add name to player.
        data -> name = (char *) daGetByIndex(properties -> player_names, i);
        // Add him to graph.
        temp = addNode(temp, PLAYER_NEXT, TYPE_PLAYER, data);
        // Remember head.
        if(head == NULL)
        {
            head = temp;
        }
    }
    addEdge(temp, head, PLAYER_NEXT);
    model -> graph_head = head;

    // Returns model.
    return model;
}

void destroyNode(int type, void * data)
{
    switch(type)
    {
        case TYPE_PLAYER:
            free( ((Player *) data) -> name );
        break;
    }

    free(data);
}

void destroyNull(void * data)
{
    // nothing
}

void destroyModel(Model * model, ModelProperties * properties)
{
    // Destroy model.
    destroyMap(model -> map_head);
    destroyGraph(model -> graph_head, &destroyNode);
    free(model);

    // And properties.
    daDestroy(properties -> player_names, &destroyNull);
    free(properties);
}
