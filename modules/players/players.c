#include <stdlib.h>
#include "players.h"

Player * createPlayersList(int n, char ** names)
{
    Player * head = NULL;
    Player * current = NULL;

    for(int i = 0; i < n; i++)
    {
        Player * temp = malloc(sizeof(Player));
        temp -> name = * (char **)(names + i * sizeof(int));

        if(head == NULL)
        {
            head = temp;
            current = temp;
        }
        else
        {
            current -> next = temp;
            current = temp;
        }
    }

    current -> next = head;

    return head;
}

void destroyPlayersList(Player * p)
{
    Player * current = p;

    do
    {
        Player * temp = current -> next;
        free(current);
        current = temp;
    } while(current != p);
}
