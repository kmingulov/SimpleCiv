#include <stdlib.h>
#include <string.h>
#include <expat.h>

#include "../../game/world/world.h"
#include "../dyn_array/dyn_array.h"
#include "xml.h"
#include "expat_handlers.h"

void * parseXML(int type)
{
    // Creating variables for parse.
    void * data = NULL;
    FILE * file = NULL;

    // What about type?
    switch(type)
    {
        case XML_CONFIG:
            data = malloc(sizeof(WorldProperties));
            file = fopen("../../config.xml", "r");
        break;

        case XML_UNITS:
            data = daCreate();
            file = fopen("../../resources/units.xml", "r");
        break;

        case XML_TECHNOLOGIES:
            data = daCreate();
            file = fopen("../../resources/technologies.xml", "r");
        break;

        default:
            return NULL;
        break;
    }

    // Initializing parser data.
    XMLParserData * p_data = malloc(sizeof(XMLParserData));
    p_data -> data = data;
    p_data -> state = XML_NONE;

    // Opening file and reading data.
    if(file == NULL)
    {
        free(data);
        free(p_data);
        return NULL;
    }
    char * xml = calloc(XML_MAX_CHARS + 1, sizeof(char));
    fread(xml, sizeof(char), XML_MAX_CHARS, file);
    fclose(file);

    // Creating and setting up parser.
    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetUserData(parser, p_data);
    XML_SetElementHandler(parser, &elementStart, &elementEnd);
    XML_SetCharacterDataHandler(parser, &elementContent);

    // Parsing xml file.
    if(!XML_Parse(parser, xml, strlen(xml), 0))
    {
        free(data);
        free(p_data);
        free(xml);
        XML_ParserFree(parser);
        return NULL;
    }

    // Freeing auxiliary data.
    free(p_data);
    free(xml);
    XML_ParserFree(parser);

    // Returning data.
    return data;
}
