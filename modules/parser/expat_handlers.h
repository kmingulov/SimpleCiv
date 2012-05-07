#ifndef EXPAT_HANDLERS
#define EXPAT_HANDLERS

#include "../../game/world/world.h"

/*
    Definitions for parser.
*/
// Count of states.
#define XML_STATES                  21

#define XML_NONE                    0

#define XML_MAP                     1
#define XML_MAP_ROWS                2
#define XML_MAP_COLUMNS             3

#define XML_PLAYERS                 4
#define XML_PLAYERS_COUNT           5
#define XML_PLAYERS_NAMES           6
#define XML_PLAYERS_CITIES          7

#define XML_UNIT                    8
#define XML_UNIT_ID                 9
#define XML_UNIT_NAME               10
#define XML_UNIT_HEALTH             11
#define XML_UNIT_DAMAGE             12
#define XML_UNIT_MOVES              13

#define XML_TECH                    14
#define XML_TECH_ID                 15
#define XML_TECH_NAME               16
#define XML_TECH_PROVIDES           17
#define XML_TECH_PROVIDES_UNITS     18
#define XML_TECH_PROVIDES_TECHS     19
#define XML_TECH_REQUIRES           20
#define XML_TECH_REQUIRES_RESOURCES 21

/*
    Struct for parser data.
*/
typedef struct XMLParserData
{
    void * data;
    int state;
} XMLParserData;

/*
    Handlers for parse.
*/
void elementStart(void * data, const char * name, const char ** attr);
void elementEnd(void * data, const char * name);
void elementContent(void * data, const char * s, int len);

#endif
