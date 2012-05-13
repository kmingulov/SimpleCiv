#ifndef UNIT_HIRING
#define UNIT_HIRING

/*
    Struct of hiring (for cities).
*/
typedef struct UnitHiring
{
    int id;
    // How many turns we researching this technology.
    int turns;
    // How many does it cost.
    int delta;
} UnitHiring;

/*
    Creates hiring.
*/
UnitHiring * createHiring();

/*
    Destroys hiring.
*/
void destroyHiring(UnitHiring * uh);

#endif
