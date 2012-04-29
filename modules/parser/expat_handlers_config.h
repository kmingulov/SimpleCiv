#ifndef EXPAT_HANDLERS_CONFIG
#define EXPAT_HANDLERS_CONFIG

#include "../../game/world/world.h"

/*
    Definitions for config parser.
*/
#define XML_CONFIG_STATE_NONE   0
#define XML_CONFIG_STATE_WIDTH  1
#define XML_CONFIG_STATE_HEIGHT 2
#define XML_CONFIG_STATE_COUNT  3
#define XML_CONFIG_STATE_NAMES  4

/*
    Struct for config parser.
*/
typedef struct XMLConfigParserData
{
    WorldProperties * properties;
    int state;
} XMLConfigParserData;

/*
    Handlers for config parse.
*/
void configStartElement(void * data, const char * name, const char ** attr);
void configEndElement(void * data, const char * name);
void configContentElement(void * data, const char * s, int len);

#endif
