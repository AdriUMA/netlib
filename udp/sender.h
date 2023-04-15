#ifndef SENDER_H
#define SENDER_H

typedef struct str_sender {
    char* address;
    unsigned port;
    int socketFD;
    unsigned bufferSize;
}* Sender;

Sender openSender(char* address, unsigned port, unsigned bufferSize);

void closeSender(Sender sender);

int sendFrame(Sender sender, void* data, unsigned dataLength);

#endif