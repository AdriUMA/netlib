#include "sender.h"

#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

TCPSender openTCPSender(char* address, unsigned port){
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
    sender->port = port;

    // host conf
    sender->host.sin_family = AF_INET;
    sender->host.sin_port = htons(sender->port);
    sender->host.sin_addr.s_addr = inet_addr(sender->address);

    // Establish connection
    if (connect(sender->socketFD, (struct sockaddr *)&sender->host, sizeof(sender->host)) < 0) {
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

int sendTCPSender(TCPSender sender, Buffer buffer){
    return sendto(sender->socketFD, buffer->data, buffer->dataSize, 0, (const struct sockaddr*)&sender->host, sizeof(sender->host));
}

int waitResponse(TCPSender sender, Buffer buffer){
    buffer->dataSize = recv(sender->socketFD, buffer->data, buffer->size, 0);
    return buffer->dataSize ;
}