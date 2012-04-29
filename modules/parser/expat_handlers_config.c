#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_functions.h"
#include "expat_handlers_config.h"

void configStartElement(void * data, const char * name, const char ** attr)
{
    XMLConfigParserData * p_data = (XMLConfigParserData *) data;

    // Set state of parser.
    if(strcmp(name, "width") == 0)
    {
        p_data -> state = XML_CONFIG_STATE_WIDTH;
    }
    else if(strcmp(name, "height") == 0)
    {
        p_data -> state = XML_CONFIG_STATE_HEIGHT;
    }
    else if(strcmp(name, "count") == 0)
    {
        p_data -> state = XML_CONFIG_STATE_COUNT;
    }
    else if(strcmp(name, "names") == 0)
    {
        p_data -> state = XML_CONFIG_STATE_NAMES;
    }
}

void configEndElement(void * data, const char * name)
{
    // Set state to none.
    XMLConfigParserData * p_data = (XMLConfigParserData *) data;
    p_data -> state = XML_CONFIG_STATE_NONE;
}

void configContentElement(void * data, const char * s, int len)
{
    // Copy string.
    char * temp = malloc(sizeof(char) * len + 1);
    memcpy(temp, s, sizeof(char) * len);
    temp[len] = '\0';

    // Remove spaces.
    strTrimSpaces(temp);

    // If it is non-null string, check for parser state.
    if(strlen(temp) != 0)
    {
        int state = ((XMLConfigParserData *) data) -> state;
        WorldProperties * properties = ((XMLConfigParserData *) data) -> properties;

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
