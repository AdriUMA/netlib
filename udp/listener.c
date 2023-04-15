#include "listener.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

Listener openListener(unsigned port, unsigned bufferSize){
    struct sockaddr_in serverAddress;

    // Allocate Memory for the listener struct.
    Listener listener = malloc(sizeof(struct str_listener));
    if (listener == NULL) return NULL;

    // Prepare a socket using IPv4 and UDP
    if ((listener->socketFD = socket(AF_INET, SOCK_DGRAM, 0)) < 0) return NULL;

    // Buffer
    listener->buffer.size = bufferSize;
    listener->buffer.dataSize = 0;
    listener->buffer.data = malloc(sizeof(bufferSize));
    if (listener->buffer.data == NULL) return NULL;

    // Port
    listener->port = port;

    // Server
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Socket opening
    if (bind(listener->socketFD, (const struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) return NULL;

    // Returning the listener ready
    return listener;
}

void closeListener(Listener listener){
    // Close socket by id
    close(listener->socketFD);

    // Free memory
    free(listener->buffer.data);
    free(listener);
}

int waitFrame(Listener listener){
    // Waiting for new client data
    listener->buffer.dataSize = recv(listener->socketFD, listener->buffer.data, listener->buffer.size, MSG_WAITALL);
    
    // Overflow
    if (listener->buffer.dataSize > listener->buffer.size) return -1;

    // Return -1 if error happends
    return listener->buffer.dataSize < 0 ? -1 : 0;
}