#include <stdlib.h>

#include "message.h"

Message * createMessage(unsigned char type, void * data)
{
    Message * message = malloc(sizeof(Message));
    message -> type = type;
    message -> data = data;
    return message;
}

void destroyMessage(Message * message)
{
    free(message -> data);
    free(message);
}
