#include "listener.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

TCPListener openTCPListener(unsigned port, unsigned maxConnections){
    // Allocate Memory for the listener struct.
    TCPListener listener = malloc(sizeof(struct str_tcplistener));
    if (listener == NULL) return NULL;

    // Prepare a socket using IPv4 and TCP
    if ((listener->socketFD = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
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
        free(listener);
        return NULL;
    }
    
    // If listener is ready, prepare max connections
    if(listen(listener->socketFD, maxConnections) < 0){
        close(listener->socketFD);
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
    free(listener);
}

TCPClient acceptTCP(TCPListener listener){
    TCPClient client = malloc(sizeof(struct str_tcpclient));
    if (client == NULL) return NULL;
    
    socklen_t size = sizeof(client->clientInfo);
    
    // Wait until accept
    client->socket = accept(listener->socketFD, (struct sockaddr *) &client->clientInfo, &size);
    
    return client;
}

void listenTCP(Buffer buffer, TCPClient client){
    // Read client data
    buffer->dataSize = recv(client->socket, buffer->data, buffer->size, 0);

    // Desconnection(?)
    if(buffer->dataSize == 0) close(client->socket);
}

int replyTCP(Buffer buffer, TCPClient client){
    return send(client->socket, buffer->data, buffer->dataSize, 0);
}

void closeClient(TCPClient client){
    // Close client port
    close(client->socket);

    // Free memory
    free(client);
}