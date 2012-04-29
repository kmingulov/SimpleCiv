#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../dyn_array/dyn_array.h"
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
        // Parser data.
        XMLConfigParserData * p_data = (XMLConfigParserData *) data;

        switch(p_data -> state)
        {
            case XML_CONFIG_STATE_WIDTH:
                p_data -> properties -> map_w = atoi(temp);
            break;

            case XML_CONFIG_STATE_HEIGHT:
                p_data -> properties -> map_h = atoi(temp);
            break;

            case XML_CONFIG_STATE_COUNT:
                p_data -> properties -> players_count = atoi(temp);
            break;

            case XML_CONFIG_STATE_NAMES:
                p_data -> properties -> player_names = strSplit(' ', temp, 16);
            break;
        }
    }

    free(temp);
}
