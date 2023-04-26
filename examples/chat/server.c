#include "ports.h"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

UDPListener listener;
UDPSenderList clients;

void signalHandler(int signal){
    if(signal == SIGINT) {
        if (listener == NULL || clients == NULL){
            closeUDPListener(listener);
            deleteUDPSenderList(&clients);
        }else {
            // If signal was triggered by user
            UDPSenderList aux = clients;

            while (aux != NULL) {
                sendUDP(aux->sender, TERMINATED_MESSAGE, strlen(TERMINATED_MESSAGE)+1);
                aux = aux->next;
            }

            closeUDPListener(listener);
            deleteUDPSenderList(&clients);
        }

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
    listener = openUDPListener(SERVER_PORT, SERVER_BUFFER);
    if (listener == NULL) {
        perror("Listener error");
        exit(EXIT_FAILURE);
    }

    // Run server
    run();

    return EXIT_SUCCESS;
}

void noticeClients(void* data, unsigned dataLength){
    UDPSenderList senders = clients;

    // Iterates all clients and notice them
    while (senders != NULL) {
        sendUDP(senders->sender, data, dataLength);
        senders = senders->next;
    }
}

int alredyConnected(char* clientAddress) {
    UDPSenderList senders = clients;

    while (senders != NULL) {
        if (strcmp(senders->sender->address, clientAddress) == 0) return 0;
        senders = senders->next;
    }

    return -1;
}

void run(){
    char* clientAddress = malloc(30);
    UDPSender newClient = NULL;

    // Init list
    createUDPSenderList(&clients);

    while (1) {
        // Waiting for a new frame
        strcpy(clientAddress, listenUDP(listener));
        
        //* ----- CASES ----- *//
        // Reading error
        if (listener->buffer.dataSize == -1){
            printf("\nUnknown error reading frame\n");
        }
        // New client
        else if (strcmp((const char*)listener->buffer.data, NOTICE_CONNECT) == 0){
            newClient = insertUDPSender(&clients, clientAddress, CLIENT_PORT, SERVER_BUFFER);
            sendUDP(newClient, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE)+1);
            printf("\n(+) Client Conected: %s\n", clientAddress);
        }
        // Client log out
        else if (strcmp((const char*)listener->buffer.data, NOTICE_DISCONNECT) == 0){
            if(alredyConnected(clientAddress) == 0){
                removeUDPSender(&clients, clientAddress);
                printf("\n(-) Client Disconected: %s\n", clientAddress);
            }
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

