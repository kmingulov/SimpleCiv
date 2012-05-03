#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "../../modules/graph/graph.h"
#include "../../modules/player/player.h"

#define TYPE_PLAYER 1
#define PLAYER_NEXT 11

void foreachFunc(Node * parent, Node * child, Edge * link)
{
    // Looks like a knee :)
    printf("%d ---%d--> %d %s\n", (int) parent, link -> type, (int) child, ((Player *) child -> data) -> name);
}

void destroyPlayer(unsigned char type, void * data)
{
    free( ((Player *) data) -> name );
    free( (Player *) data );
}

int main()
{
    Node * head = NULL;
    Node * temp = NULL;

    // Initialize random.
    srand(time(NULL));

    // Create list of players.
    for(int i = 0; i < 5; i++)
    {
        // Create new player.
        Player * data = malloc(sizeof(Player));
        // Generate random name.
        char * name = malloc(sizeof(char) * 10);
        for(int i = 0; i < 9; i++)
        {
            name[i] = rand() % 26 + 65;
        }
        name[9] = '\0';
        // Add name to player.
        data -> name = name;
        // Add him to graph.
        // If temp == NULL (i.e. i == 0), it will just create graph. See graph.h
        // for some notes.
        temp = addNode(temp, PLAYER_NEXT, TYPE_PLAYER, data);
        // Remember head.
        if(head == NULL)
        {
            head = temp;
        }
    }

    // Loop list.
    addEdge(temp, head, PLAYER_NEXT);

    // Print list. If it's all okay, we will see each player 3 times.
    for(int i = 0; i < 15; i++)
    {
        foreachNeighbour(temp, &foreachFunc);
        temp = getNeighbour(temp, PLAYER_NEXT);
    }

    DynArray * deleted = daCreate();
    destroyGraph(head, deleted, &destroyPlayer);
    daDestroy(deleted, NULL);

    return 0;
}
