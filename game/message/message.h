#ifndef MESSAGE
#define MESSAGE

typedef struct Message
{
    unsigned char type;
    void * data;
} Message;

/*
    Creates message.
*/
Message * createMessage(unsigned char type, void * data);

/*
    Destroys message.
*/
void destroyMessage(Message * mes);

#endif
