#include "sender.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

Sender openSender(char* address, unsigned port, unsigned bufferSize){
    Sender sender;

    // Allocate memory for the sender
    if ((sender = malloc(sizeof(struct str_sender))) == NULL) return NULL;

    // Init IPv4-UDP socket
    if ((sender->socketFD = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        free(sender);
        return NULL;
    }

    // Init sender
    if ((sender->address = malloc(sizeof(char)*(strlen(address)+1))) == NULL) return NULL;
    strcpy(sender->address, address);
    sender->bufferSize = bufferSize;
    sender->port = port;

    return sender;
}

void closeSender(Sender sender){
    if (sender == NULL) return;
    
    // Close socket
    close(sender->socketFD);

    // Free memory
    free(sender->address);
    free(sender);
}

int sendFrame(Sender sender, void *data, unsigned int dataLength){
    struct sockaddr_in server;

    // Server
    server.sin_family = AF_INET;
    server.sin_port = htons(sender->port);
    server.sin_addr.s_addr = inet_addr(sender->address);

    // Send
    return sendto(sender->socketFD, data, dataLength, 0, (const struct sockaddr*)&server, sizeof(server));
}