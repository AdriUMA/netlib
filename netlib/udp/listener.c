#include "listener.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

UDPListener openUDPListener(unsigned port, unsigned bufferSize){
    struct sockaddr_in serverAddress;

    // Allocate Memory for the listener struct.
    UDPListener listener = malloc(sizeof(struct str_udplistener));
    if (listener == NULL) return NULL;

    // Prepare a socket using IPv4 and UDP
    if ((listener->socketFD = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        free(listener);
        return NULL;
    }

    // Buffer
    listener->buffer.size = bufferSize;
    listener->buffer.dataSize = 0;
    listener->buffer.data = malloc(sizeof(bufferSize));
    if (listener->buffer.data == NULL)  {
        free(listener);
        return NULL;
    }

    // Port
    listener->port = port;

    // Server
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Socket opening
    if (bind(listener->socketFD, (const struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        free(listener->buffer.data);
        free(listener);
        return NULL;
    }
    
    // Returning the listener ready
    return listener;
}

void closeUDPListener(UDPListener listener){
    if (listener == NULL) return;

    // Close socket by id
    close(listener->socketFD);

    // Free memory
    free(listener->buffer.data);
    free(listener);
}

char* listenUDP(UDPListener listener){
    struct sockaddr_in client;
    socklen_t len;

    // Waiting for new client data
    listener->buffer.dataSize = recvfrom(listener->socketFD, listener->buffer.data, listener->buffer.size, MSG_WAITALL, (struct sockaddr *restrict) &client, (socklen_t *restrict)&len);
    
    return inet_ntoa(client.sin_addr);
}