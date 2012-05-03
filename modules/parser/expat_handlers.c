#include <stdlib.h>
#include <string.h>

#include "../../game/world/definitions.h"
#include "../graph/graph.h"
#include "../dyn_array/dyn_array.h"
#include "../unit/unit.h"
#include "../technology/technology.h"
#include "string_functions.h"
#include "expat_handlers.h"

// This is a lenght of arrays (see below).
#define XML_STATES 19

/*
    Auxiliary arrays for comfortable view of elementStart() function.
    xml_tags[] — array of xml tags of our xml files.
    xml_states[] — array of XMLParserData's states.
    xml_parents[i] — state, which required for state xml_states[i].
*/
const char xml_tags[][13] = {"map", "width", "height", "players", "count",
    "names", "unit", "id", "name", "health", "damage", "technology", "id",
    "name", "provides", "units", "technologies", "requires", "resources"};

const int xml_states[] = {XML_MAP, XML_MAP_WIDTH, XML_MAP_HEIGHT, XML_PLAYERS,
    XML_PLAYERS_COUNT, XML_PLAYERS_NAMES, XML_UNIT, XML_UNIT_ID, XML_UNIT_NAME,
    XML_UNIT_HEALTH, XML_UNIT_DAMAGE, XML_TECH, XML_TECH_ID, XML_TECH_NAME,
    XML_TECH_PROVIDES, XML_TECH_PROVIDES_UNITS, XML_TECH_PROVIDES_TECHS,
    XML_TECH_REQUIRES, XML_TECH_REQUIRES_RESOURCES};

const int xml_parents[] = {0, XML_MAP, XML_MAP, 0, XML_PLAYERS, XML_PLAYERS, 0, 
    XML_UNIT, XML_UNIT, XML_UNIT, XML_UNIT, 0, XML_TECH, XML_TECH, XML_TECH,
    XML_TECH_PROVIDES, XML_TECH_PROVIDES, XML_TECH, XML_TECH_REQUIRES};

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
    char * temp = malloc(sizeof(char) * (len + 1));
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
                // Here we do one _bad_ thing: we ignore unit id, what we read.
                // It won't matter, if all ids of units in units.xml file go
                // in ascending from 0 to (some number) without any missing
                // numbers between.
                temp_data = malloc(sizeof(UnitCommonInfo));
                daPrepend(p_data -> data, temp_data);
            break;

            case XML_UNIT_NAME:
                temp_data = malloc(sizeof(char) * (strlen(temp) + 1));
                ((UnitCommonInfo *) daGetLast(p_data -> data)) -> name = strcpy(temp_data, temp);
            break;

            case XML_UNIT_HEALTH:
                ((UnitCommonInfo *) daGetLast(p_data -> data)) -> max_health = atoi(temp);
            break;

            case XML_UNIT_DAMAGE:
                ((UnitCommonInfo *) daGetLast(p_data -> data)) -> max_damage = atoi(temp);
            break;

            case XML_TECH_ID:
                // Same note as for XML_UNIT_ID.
                temp_data = createTechnologyParseInfo();
                daPrepend(p_data -> data, temp_data);
            break;

            case XML_TECH_NAME:
                temp_data = malloc(sizeof(char) * (strlen(temp) + 1));
                ((Technology *) ((TechnologyParseInfo *) daGetLast(p_data -> data)) -> tech_in_tree -> data) -> name = strcpy(temp_data, temp);
            break;

            case XML_TECH_PROVIDES_UNITS:
                ((Technology *) ((TechnologyParseInfo *) daGetLast(p_data -> data)) -> tech_in_tree -> data) -> provides_units = strSplitAndAtoi(',', temp, 4);
            break;

            case XML_TECH_PROVIDES_TECHS:
                ((TechnologyParseInfo *) daGetLast(p_data -> data)) -> provides_technologies = strSplitAndAtoi(',', temp, 4);
            break;

            case XML_TECH_REQUIRES_RESOURCES:
                ((Technology *) ((TechnologyParseInfo *) daGetLast(p_data -> data)) -> tech_in_tree -> data) -> requires_resources = strSplitAndAtoi(',', temp, 4);
            break;
        }
    }

    free(temp);
}
