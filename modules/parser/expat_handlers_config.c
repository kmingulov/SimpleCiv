#include <stdio.h>
#include <stdlib.h>

#include "string_functions.h"
#include "expat_handlers_config.h"

void configStartElement(void * data, const char * name, const char ** attr)
{
    XMLConfigParser * parse = (XMLConfigParser *) data;

    // Set state of parser.
    if(strcmp(name, "width") == 0)
    {
        parse -> state = XML_CONFIG_STATE_WIDTH;
    } else if(strcmp(name, "height") == 0)
    {
        parse -> state = XML_CONFIG_STATE_HEIGHT;
    } else if(strcmp(name, "count") == 0)
    {
        parse -> state = XML_CONFIG_STATE_COUNT;
    } else if(strcmp(name, "names") == 0)
    {
        parse -> state = XML_CONFIG_STATE_NAMES;
    }
}

void configEndElement(void * data, const char * name)
{
    // Set state to none.
    XMLConfigParse * parse = (XMLConfigParse *) data;
    parse -> state = XML_CONFIG_STATE_NONE;
}

void configContentElement(void * data, const char * s, int len)
{
    // Copy string.
    char * temp = malloc(sizeof(char) * len + 1);
    memcpy(temp, s, sizeof(char) * len);
    temp[len] = '\0';

    // Remove spaces.
    strTrim(temp);

    // If it is non-null string, check for parser state.
    if(strlen(temp) != 0)
    {
        int state = ((XMLConfigParse *) data) -> state;
        WorldProperties * properties = ((XMLConfigParse *) data) -> properties;

        switch(state)
        {
            case XML_CONFIG_STATE_WIDTH:
                properties -> map_w = atoi(temp);
            break;

            case XML_CONFIG_STATE_HEIGHT:
                properties -> map_h = atoi(temp);
            break;

            case XML_CONFIG_STATE_COUNT:
                properties -> players_count = atoi(temp);
            break;

            // TODO players_names
        }
    }

    free(temp);
}
