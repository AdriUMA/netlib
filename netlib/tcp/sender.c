#include "sender.h"

#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct sockaddr_in server;

TCPSender openTCPSender(char* address, unsigned port, unsigned bufferSize){
    TCPSender sender;

    // Allocate memory for the sender
    if ((sender = malloc(sizeof(struct str_tcpsender))) == NULL) return NULL;

    // Init IPv4-TCP socket
    if ((sender->socketFD = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        free(sender);
        return NULL;
    }

    // Init sender
    if ((sender->address = malloc(sizeof(char)*(strlen(address)+1))) == NULL) { 
        close(sender->socketFD);
        free(sender);
        return NULL;
    }
    strcpy(sender->address, address);
    sender->bufferSize = bufferSize;
    sender->port = port;

    // Server conf
    server.sin_family = AF_INET;
    server.sin_port = htons(sender->port);
    server.sin_addr.s_addr = inet_addr(sender->address);

    // Establish connection
    if (connect(sender->socketFD, (struct sockaddr *)&server, sizeof(server)) < 0) {
        close(sender->socketFD);
        free(sender->address);
        free(sender);
        return NULL;
    }

    return sender;
}

void closeTCPSender(TCPSender sender){
    if (sender == NULL) return;
    
    // Close socket
    close(sender->socketFD);

    // Free memory
    free(sender->address);
    free(sender);
}

int sendTCP(TCPSender sender, void *data, unsigned int dataLength){
    // Send
    return sendto(sender->socketFD, data, dataLength, 0, (const struct sockaddr*)&server, sizeof(server));
}