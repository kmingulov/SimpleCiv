#include <stdlib.h>

#include "message.h"

Message * createMessage(unsigned char type, void * data)
{
    Message * message = malloc(sizeof(Message));
    message -> type = type;
    message -> data = data;
    return message;
}

void destroyMessage(void * data)
{
    Message * message = (Message *) data;

    if(message -> data != NULL)
    {
        free(message -> data);
    }
    free(message);
}
