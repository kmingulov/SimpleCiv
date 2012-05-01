#include <stdio.h>
#include <stdlib.h>

#include "../../game/world/world.h"
#include "../../modules/parser/xml.h"
#include "../../modules/unit/unit.h"

void destroyUnit(void * data)
{
    UnitCommonInfo * unit = (UnitCommonInfo *) data;
    free(unit -> name);
    free(unit);
}

int main()
{
    // Parse xml files.
    printf("Parsing config file… ");
    WorldProperties * properties = parseXML(XML_CONFIG);
    if(properties == NULL)
    {
        printf("Failed\n\033[1;31mError:\033[0m config.xml file doesn't exist or corrupted.\n");
        return 1;
    }
    printf("Done\n");

    printf("Parsing units file… ");
    DynArray * units = parseXML(XML_UNITS);
    if(units == NULL)
    {
        printf("Failed\n\033[1;31mError:\033[0m resources/units.xml file doesn't exist or corrupted.\n");
        return 1;
    }
    printf("%d units loaded.\n", units -> length);

    // Creating world.
    printf("Creating world %dx%d… ", properties -> map_w, properties -> map_h);
    World * world = createWorld(properties);

    // Destroing world.
    printf("Done");
    printf("\nDestroing world… ");
    destroyWorld(world, properties);
    daDestroy(units, &destroyUnit);
    printf("Done\n");

    return 0;
}
