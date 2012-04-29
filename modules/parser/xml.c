#include <stdlib.h>
#include <string.h>
#include <expat.h>

#include "xml.h"
#include "expat_handlers_config.h"

WorldProperties * parseConfig(char * filename)
{
    // Create variables for parse.
    WorldProperties * properties = malloc(sizeof(WorldProperties));
    XMLConfigParserData * data = malloc(sizeof(XMLConfigParserData));
    data -> properties = properties;
    data -> state = XML_CONFIG_STATE_NONE;

    // Open config and read data.
    FILE * config = fopen(filename, "r");
    if(config == NULL)
    {
        free(properties);
        free(data);
        return NULL;
    }
    char * xml = malloc(XML_MAX_CHARS * sizeof(char));
    fread(xml, sizeof(char), XML_MAX_CHARS, config);
    fclose(config);

    // Create and set up parser.
    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetUserData(parser, data);
    XML_SetElementHandler(parser, &configStartElement, &configEndElement);
    XML_SetCharacterDataHandler(parser, &configContentElement);

    // Parse config file.
    XML_Parse(parser, xml, strlen(xml), 0);

    // Free auxiliary data.
    free(data);
    free(xml);
    XML_ParserFree(parser);

    // Return properties.
    return properties;
}
