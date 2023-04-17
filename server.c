#include "ports.h"
#include "linkedlist/senderList.h"
#include "udp/listener.h"
#include "udp/sender.h"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WELCOME_MESSAGE "\n### -------------- SERVER ------------- ###\n### Connection established successfully ###\n### -------------- SERVER ------------- ###\n\0"
                                           
Listener listener;
SenderList clients;

void signalHandler(int signal){
    if(signal == SIGINT) {
        if (listener != NULL) closeListener(listener);
        deleteList(&clients);
        exit(EXIT_SUCCESS);
    }
}

void noticeClients(void* data, unsigned dataLength);
int alredyConnected(char* clientAddress);
void run();

int main () {
    // Signal handler
    signal(SIGINT, signalHandler);

    VERSION;

    // Open listener
    listener = openListener(SERVER_PORT, SERVER_BUFFER);
    if (listener == NULL) exit(EXIT_FAILURE);

    // Run server
    run();

    return EXIT_SUCCESS;
}

void noticeClients(void* data, unsigned dataLength){
    SenderList senders = clients;

    // Iterates all clients and notice them
    while (senders != NULL) {
        sendFrame(senders->sender, data, dataLength);
        senders = senders->next;
    }
}

int alredyConnected(char* clientAddress) {
    SenderList senders = clients;

    while (senders != NULL) {
        if (strcmp(senders->sender->address, clientAddress) == 0) return 0;
        senders = senders->next;
    }

    return -1;
}

void run(){
    char* clientAddress = malloc(30);
    Sender newClient = NULL;

    // Init list
    createList(&clients);

    while (1) {
        // Waiting for a new frame
        strcpy(clientAddress, waitFrame(listener));
        
        //* ----- CASES ----- *//
        // Reading error
        if (listener->buffer.dataSize == -1){
            printf("\nUnknown error reading frame\n");
        }
        // New client
        else if (strcmp((const char*)listener->buffer.data, NOTICE_CONNECT) == 0){
            newClient = insertSender(&clients, clientAddress, CLIENT_PORT, SERVER_BUFFER);
            sendFrame(newClient, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE)+1);
            printf("\n(+) Client Conected: %s\n", clientAddress);
        }
        // Client log out
        else if (strcmp((const char*)listener->buffer.data, NOTICE_DISCONNECT) == 0){
            removeSender(&clients, clientAddress);
            printf("\n(-) Client Disconected: %s\n", clientAddress);
        }
        // Any data
        else {
            // Accept if address is in the list
            if (alredyConnected(clientAddress) == 0){
                noticeClients(listener->buffer.data, listener->buffer.dataSize);
                printf("\nFrame from: %s\n%s\n", clientAddress, (const char*)listener->buffer.data);
            }
            // Refused data
            else{
                printf("\nREFUSED FROM: %s\nREFUSED DATA: %s\n", clientAddress, (const char*)listener->buffer.data);
            }
        }
        fflush(stdout);
    }

    
}