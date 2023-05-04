#include "sender.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

UDPSender openUDPSender(char* address, unsigned port){
    UDPSender sender;

    // Allocate memory for the sender
    if ((sender = malloc(sizeof(struct str_udpsender))) == NULL) return NULL;

    // Init IPv4-UDP socket
    if ((sender->socketFD = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
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

    // host
    sender->host.sin_family = AF_INET;
    sender->host.sin_port = htons(sender->port);
    sender->host.sin_addr.s_addr = inet_addr(sender->address);

    return sender;
}

void closeUDPSender(UDPSender sender){
    if (sender == NULL) return;
    
    // Close socket
    close(sender->socketFD);

    // Free memory
    free(sender->address);
    free(sender);
}

int sendUDP(Buffer buffer, UDPSender sender){
    return sendto(sender->socketFD, buffer->data, buffer->dataSize, 0, (const struct sockaddr*)&sender->host, sizeof(sender->host));
}