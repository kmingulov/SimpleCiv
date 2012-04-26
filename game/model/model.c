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
        temp = addNode(temp, EDGE_NEXT_PLAYER, NODE_PLAYER, data);
        // Remember head.
        if(head == NULL)
        {
            head = temp;
        }
    }
    addEdge(temp, head, EDGE_NEXT_PLAYER);
    model -> graph_head = head;

    // Returns model.
    return model;
}

void destroyNode(unsigned char type, void * data)
{
    switch(type)
    {
        case NODE_PLAYER:
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

void saveModel(Model * model, ModelProperties * properties, FILE * map_file)
{
    
    fprintf(map_file, "<?xml version=\"1.0\" encoding=\"UTF-8\">\n<map>\n\t<width>%d</width>\n\t<height>%d</height>\n", properties -> map_w, properties -> map_h);

    Cell * current = model -> map_head;

    for(int i = 0; i < properties -> map_w; i++)
    {
        for(int j = 0; j < properties -> map_h; j++)
        {
            fprintf(map_file, "\t<cell x=\"%d\" y=\"%d\" territory=\"%d\">\n", i, j, current -> territory);
            current = current -> right;
        }
        current = current -> bottom;
    }

    fprintf(map_file, "</map>");
}
