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

/*
    Doesn't free anything (because data was free'd already).
*/
void destroyNull(void * data)
{
    // nothing
}

/*
    Free TechnologyParseInfo.
*/
void destroyTechnologyParseInfo(void * data)
{
    TechnologyParseInfo * t = (TechnologyParseInfo *) data;

    free(t -> name);
    daDestroy(t -> provides_units, &destroyNull);
    daDestroy(t -> provides_technologies, &destroyNull);
    daDestroy(t -> requires_resources, &destroyNull);
    free(t);
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
    DynArray * techs_additional_data = parseXML(XML_TECHNOLOGIES);
    if(techs_additional_data == NULL)
    {
        printf("Failed\n\033[1;31mError:\033[0m resources/technologies.xml doesn't exist or corrupted.\n");
        return NULL;
    }
    printf("%d technologies loaded\n", techs_additional_data -> length);

    // TODO Go through techs_additional_data array and create tree of
    // technologies. Create array of TechnologyCommonInfo. After create arrays
    // of technologies and units for each players.

    // Destroy techs_additional_data.
    daDestroy(techs_additional_data, &destroyTechnologyParseInfo);

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
    daDestroy(world -> properties -> player_names, &destroyNull);
    free(world -> properties);

    // Destroy array of UnitCommonInfo.
    daDestroy(world -> units_info, &destroyUnitCommonInfo);

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
