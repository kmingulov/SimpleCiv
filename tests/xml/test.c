#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <expat.h>

#include "../../modules/parser/xml.h"
#include "../../modules/parser/expat_handlers_config.h"

void foreachFunction(int index, void * data)
{
    printf("\t%s\n", (char *) data);
}

int main()
{
    // Create variables for parse.
    WorldProperties * properties = parseConfig("../../config.xml");

    if(properties != NULL)
    {
        printf("Width  = %d\nHeight = %d\nCount  = %d\nNames:\n", properties -> map_w, properties -> map_h, properties -> players_count);
        daForEach(properties -> player_names, &foreachFunction);
        daDestroy(properties -> player_names, &free);
        free(properties);
    }
    else
    {
        printf("Incorrect filename.\n");
    }

    return 0;
}
