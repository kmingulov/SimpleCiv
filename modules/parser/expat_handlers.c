#include <stdlib.h>
#include <string.h>

#include "../dyn_array/dyn_array.h"
#include "../unit/unit.h"
#include "string_functions.h"
#include "expat_handlers.h"

// This is a lenght of arrays (see below).
#define XML_STATES 12

/*
    Auxiliary arrays for comfortable view of elementStart() function.
    xml_tags[] — array of xml tags of our xml files.
    xml_states[] — array of XMLParserData's states.
    xml_parents[i] — state, which required for state xml_states[i].

    TODO Looks awful. How make it more beautiful?
*/
const char xml_tags[][13] = {"map", "width", "height", "players", "count",
    "names", "unit", "id", "name", "health", "damage", "technology"};
const int xml_states[] = {XML_MAP, XML_MAP_WIDTH, XML_MAP_HEIGHT, XML_PLAYERS,
    XML_PLAYERS_COUNT, XML_PLAYERS_NAMES, XML_UNIT, XML_UNIT_ID, XML_UNIT_NAME,
    XML_UNIT_HEALTH, XML_UNIT_DAMAGE, XML_TECH};
const int xml_parents[] = {0, XML_MAP, XML_MAP, 0, XML_PLAYERS, XML_PLAYERS, 0, 
    XML_UNIT, XML_UNIT, XML_UNIT, XML_UNIT, 0};

void elementStart(void * data, const char * name, const char ** attr)
{
    XMLParserData * p_data = (XMLParserData *) data;

    for(int i = 0; i < XML_STATES; i++)
    {
        // Check for tag and required state.
        if(strcmp(name, xml_tags[i]) == 0 && p_data -> state == xml_parents[i])
        {
            p_data -> state = xml_states[i];
            break;
        }
    }
}

void elementEnd(void * data, const char * name)
{
    XMLParserData * p_data = (XMLParserData *) data;

    // Set state to parent.
    for(int i = 0; i < XML_STATES; i++)
    {
        if(xml_states[i] == p_data -> state)
        {
            p_data -> state = xml_parents[i];
            break;
        }
    }
}

void elementContent(void * data, const char * s, int len)
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
        XMLParserData * p_data = (XMLParserData *) data;
        void * temp_data = NULL;

        switch(p_data -> state)
        {
            case XML_MAP_WIDTH:
                ((WorldProperties *) p_data -> data) -> map_w = atoi(temp);
            break;

            case XML_MAP_HEIGHT:
                ((WorldProperties *) p_data -> data) -> map_h = atoi(temp);
            break;

            case XML_PLAYERS_COUNT:
                ((WorldProperties *) p_data -> data) -> players_count = atoi(temp);
            break;

            case XML_PLAYERS_NAMES:
                ((WorldProperties *) p_data -> data) -> player_names = strSplit(' ', temp, 16);
            break;

            case XML_UNIT_ID:
                temp_data = malloc(sizeof(UnitCommonInfo));
                daPrepend(p_data -> data, temp_data);
            break;

            case XML_UNIT_NAME:
                temp_data = malloc(sizeof(char) * 16);
                ((UnitCommonInfo *) daGetLast(p_data -> data)) -> name = strcpy(temp_data, temp);
            break;

            case XML_UNIT_HEALTH:
                ((UnitCommonInfo *) daGetLast(p_data -> data)) -> max_health = atoi(temp);
            break;

            case XML_UNIT_DAMAGE:
                ((UnitCommonInfo *) daGetLast(p_data -> data)) -> max_damage = atoi(temp);
            break;
        }
    }

    free(temp);
}
