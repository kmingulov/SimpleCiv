#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <expat.h>

#include "../../modules/parser/xml.h"
#include "../../modules/parser/expat_handlers_config.h"

int main()
{
    // Create variables for parse.
    WorldProperties * properties = parseConfig("../../config.xml");

    if(properties != NULL)
    {
        printf("%d %d %d\n", properties -> map_w, properties -> map_h, properties -> players_count);
        free(properties);
    }
    else
    {
        printf("Incorrect filename.\n");
    }

    return 0;
}
