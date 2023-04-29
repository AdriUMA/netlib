#include "listener.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


TCPListener openTCPListener(unsigned port, unsigned bufferSize){
    // Allocate Memory for the listener struct.
    TCPListener listener = malloc(sizeof(struct str_tcplistener));
    if (listener == NULL) return NULL;

    // Prepare a socket using IPv4 and TCP
    if ((listener->socketFD = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        free(listener);
        return NULL;
    }

    // Buffer
    listener->buffer.size = bufferSize;
    listener->buffer.dataSize = 0;
    listener->buffer.data = malloc(sizeof(bufferSize));
    if (listener->buffer.data == NULL)  {
        close(listener->socketFD);
        free(listener);
        return NULL;
    }

    // Port
    listener->port = port;

    // Server
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    // Socket opening
    if (bind(listener->socketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        close(listener->socketFD);
        free(listener->buffer.data);
        free(listener);
        return NULL;
    }
    
    // Returning the listener ready
    return listener;
}

void closeTCPListener(TCPListener listener){
    if (listener == NULL) return;

    // Close socket by id
    close(listener->socketFD);

    // Free memory
    free(listener->buffer.data);
    free(listener);
}

char* listenTCP(TCPListener listener){
    int client_socket;
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    // Waiting for accept connection
    client_socket = accept(listener->socketFD, (struct sockaddr *) &client_addr, &len);

    // Waiting for new client data
    if(client_socket >= 0) listener->buffer.dataSize = recv(client_socket, listener->buffer.data, listener->buffer.size, MSG_WAITALL);
    
    return inet_ntoa(client_addr.sin_addr);
}