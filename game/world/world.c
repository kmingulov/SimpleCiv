#include "world.h"

World * createWorld(WorldProperties * properties)
{
    // Creates model.
    World * world = malloc(sizeof(World));

    // Creates map.
    world -> map_head = createMap(properties -> map_w, properties -> map_h);
    //generateMap(world -> map_head, properties -> map_w, properties -> map_h);

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
    world -> graph_head = head;

    // TODO:
    // Loading from xml technologies' tree and units' tree.
    // Initialize table of technologies and units for each player.
    // Create several units for each player.

    // Returns model.
    return world;
}

/*
    Additional destroy functions.
*/
void destroyNode(unsigned char type, void * data)
{
    switch(type)
    {
        case NODE_CELL:
        break;

        case NODE_PLAYER:
            free( ((Player *) data) -> name );
        break;
    }

    free(data);
}

/*
    Doesn't free anything (because data was free'd already).
*/
void destroyNull(void * data)
{
    // nothing
}

void destroyWorld(World * world, WorldProperties * properties)
{
    // Auxiliary array for destroyGraph();
    DynArray * deleted = daCreate();

    // Destroy map.
    destroyMap(world -> map_head, properties -> map_w, properties -> map_h);

    // Destroy world.
    destroyGraph(world -> graph_head, deleted, &destroyNode);
    free(world);

    // And properties.
    daDestroy(properties -> player_names, &destroyNull);
    free(properties);

    // Destroy auxiliary array.
    free(deleted -> data);
    free(deleted);
}

void saveWorld(World * world, WorldProperties * properties, FILE * map_file)
{
    fprintf(map_file, "<?xml version=\"1.0\" encoding=\"UTF-8\">\n<map>\n\t<width>%d</width>\n\t<height>%d</height>\n", properties -> map_w, properties -> map_h);

    Node * current = world -> map_head;

    for(int i = 0; i < properties -> map_w; i++)
    {
        for(int j = 0; j < properties -> map_h; j++)
        {
            fprintf(map_file, "\t<cell x=\"%d\" y=\"%d\" territory=\"%d\">\n", i, j, ( (Cell *) current -> data ) -> territory);
            current = getNeighbour(current, EDGE_CELL_RIGHT);
        }
        current = getNeighbour(current, EDGE_CELL_BOTTOM);
    }

    fprintf(map_file, "</map>");
}
