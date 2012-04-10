#ifndef PLAYERS
#define PLAYERS

typedef struct Player
{
    // Player data.
    char * name;
    int gold;
    // TODO
    //      cities array

    // Next player.
    struct Player * next;
} Player;

/*
    Creates players list with n players (their name are… names).
*/
Player * createPlayersList(int n, char ** names);

/*
    Destroys players list.
*/
void destroyPlayersList(Player * p);

#endif
