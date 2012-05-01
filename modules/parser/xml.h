#ifndef XML
#define XML

#define XML_MAX_CHARS    10000
#define XML_CONFIG       0
#define XML_TECHNOLOGIES 1
#define XML_UNITS        2

/*
    Parses XML file with type and returns data.
*/
void * parseXML(int type);

#endif
