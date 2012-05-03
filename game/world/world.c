#include "world.h"

#include "../../modules/parser/xml.h"
#include "../../modules/unit/unit.h"
#include "../../modules/technology/technology.h"

/*
    Additional destroy functions.
*/
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

World * createWorld()
{
    // Creating world.
    World * world = malloc(sizeof(World));

    // Parsing config.xml.
    printf("Parsing config.xml… ");
    world -> properties = parseXML(XML_CONFIG);
    if(world -> properties == NULL)
    {
        printf("Failed\n\033[1;31mError:\033[0m config.xml doesn't exist or corrupted.\n");
        return NULL;
    }
    printf("Done\n");

    // Parsing units.xml.
    printf("Parsing resources/units.xml… ");
    world -> units_info = parseXML(XML_UNITS);
    if(world -> units_info == NULL)
    {
        printf("Failed\n\033[1;31mError:\033[0m resources/units.xml doesn't exist or corrupted.\n");
        return NULL;
    }
    printf("%d units loaded\n", world -> units_info -> length);

    // Parsing technologies.xml.
    printf("Parsing resources/technologies.xml… ");
    DynArray * techs_data = parseXML(XML_TECHNOLOGIES);
    if(techs_data == NULL)
    {
        printf("Failed\n\033[1;31mError:\033[0m resources/technologies.xml doesn't exist or corrupted.\n");
        return NULL;
    }
    printf("%d technologies loaded\n", techs_data -> length);

    // Going through techs_data and creating tech tree.
    printf("Creating technology tree… ");
    world -> techs_tree = ((TechnologyParseInfo *) techs_data -> data[0]) -> tech_in_tree;
    // Passing each technology.
    for(int i = 0; i < techs_data -> length; i++)
    {
        TechnologyParseInfo * current = (TechnologyParseInfo *) techs_data -> data[i];
        DynArray * provides = current -> provides_technologies;
        // For each neighbour creating two edges (TECH_PROVIDES and
        // TECH_REQUIRES).
        if(provides != NULL)
        {
            for(int j = 0; j < provides -> length; j++)
            {
                // Getting neighbour.
                int id = (int) provides -> data[j];
                TechnologyParseInfo * neighbour = (TechnologyParseInfo *) techs_data -> data[id];
                // Creating two edges.
                addEdge(current -> tech_in_tree, neighbour -> tech_in_tree, EDGE_TECH_PROVIDES);
                addEdge(neighbour -> tech_in_tree, current -> tech_in_tree, EDGE_TECH_REQUIRES);
            }
        }
    }
    printf("Done\n");

    // Creating techs_info table.
    world -> techs_info = daCreate();
    for(int i = 0; i < techs_data -> length; i++)
    {
        TechnologyParseInfo * t = (TechnologyParseInfo *) techs_data -> data[i];
        daPrepend(world -> techs_info, createTechnologyCommonInfo(t));
    }

    // Free techs_data.
    printf("Freeing auxiliary data… ");
    daDestroy(techs_data, &destroyTechnologyParseInfo);
    printf("Done\n");

    // TODO Create arrays of technologies and units for each players.

    // Creating map.
    printf("Creating map %dx%d… ", world -> properties -> map_w, world -> properties -> map_h);
    world -> graph_map = createMap(world -> properties -> map_w, world -> properties -> map_h);
    //generateMap(world -> map_head, properties -> map_w, properties -> map_h);
    printf("Done\n");

    // Creating players list.
    printf("Creating list of %d players… ", world -> properties -> players_count);
    Node * head = NULL; // Graph head.
    Node * temp = NULL; // Temporary variable.
    for(int i = 0; i < world -> properties -> players_count; i++)
    {
        // Create new player.
        Player * data = malloc(sizeof(Player));
        // Add name to player.
        data -> name = (char *) daGetByIndex(world -> properties -> player_names, i);
        // Add him to graph.
        temp = addNode(temp, EDGE_NEXT_PLAYER, NODE_PLAYER, data);
        // Remember head.
        if(head == NULL)
        {
            head = temp;
        }
    }
    addEdge(temp, head, EDGE_NEXT_PLAYER);
    world -> graph_players = head;
    printf("Done\n");

    printf("All done!\n");

    // Returning world.
    return world;
}

/*
    Destroys array of UnitCommonInfo.
*/
void destroyUnitCommonInfo(void * data)
{
    UnitCommonInfo * unit = (UnitCommonInfo *) data;
    free(unit -> name);
    free(unit);
}

void destroyWorld(World * world)
{
    // Auxiliary array for destroyGraph();
    DynArray * deleted = daCreate();

    // Destroy map.
    destroyMap(world -> graph_map, world -> properties -> map_w, world -> properties -> map_h);

    // Destroy properties.
    daDestroy(world -> properties -> player_names, NULL);
    free(world -> properties);

    // Destroy array of UnitCommonInfos.
    daDestroy(world -> units_info, &destroyUnitCommonInfo);

    // Destroy array of TechnologyCommonInfos.
    daDestroy(world -> techs_info, &free);

    // Destroy tech tree.
    destroyGraph(world -> techs_tree, deleted, &destroyTechnology);

    // Destroy world.
    destroyGraph(world -> graph_players, deleted, &destroyNode);
    free(world);

    // Destroy auxiliary array.
    free(deleted -> data);
    free(deleted);
}

void saveWorld(World * world, WorldProperties * properties, FILE * map_file)
{
    fprintf(map_file, "<?xml version=\"1.0\" encoding=\"UTF-8\">\n<map>\n\t<width>%d</width>\n\t<height>%d</height>\n", properties -> map_w, properties -> map_h);

    Node * current = world -> graph_map;

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
