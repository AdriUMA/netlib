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
                Buffer buf = openBuffer(SERVER_BUFFER);
                stringIntoBuffer(buf, TERMINATED_MESSAGE);
                sendUDP(buf, aux->sender);
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
    listener = openUDPListener(SERVER_PORT);
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
    Buffer buffer = openBuffer(dataLength);
    buffer->data = data;
    buffer->dataSize = dataLength;
    // Iterates all clients and notice them
    while (senders != NULL) {
        sendUDP(buffer, senders->sender);
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
    Buffer buffer = openBuffer(SERVER_BUFFER);

    // Init list
    createUDPSenderList(&clients);
    Buffer buf = openBuffer(SERVER_BUFFER);

    while (1) {
        // Waiting for a new frame
        strcpy(clientAddress, listenUDP(buffer, listener));
        printf("%s", (const char*)buffer->data);
        
        //* ----- CASES ----- *//
        // Reading error
        if (buffer->dataSize == -1){
            printf("\nUnknown error reading frame\n");
        }
        // New client
        else if (strcmp((const char*)buffer->data, NOTICE_CONNECT) == 0){
            newClient = insertUDPSender(&clients, clientAddress, CLIENT_PORT, SERVER_BUFFER);
            stringIntoBuffer(buf, WELCOME_MESSAGE);
            sendUDP(buf, newClient);
            printf("\n(+) Client Conected: %s\n", clientAddress);
        }
        // Client log out
        else if (strcmp((const char*)buffer->data, NOTICE_DISCONNECT) == 0){
            if(alredyConnected(clientAddress) == 0){
                removeUDPSender(&clients, clientAddress);
                printf("\n(-) Client Disconected: %s\n", clientAddress);
            }
        }
        // Any data
        else {
            // Accept if address is in the list
            if (alredyConnected(clientAddress) == 0){
                noticeClients(buffer->data, buffer->dataSize);
                printf("\nFrame from: %s\n%s\n", clientAddress, (const char*)buffer->data);
            }
            // Refused data
            else{
                printf("\nREFUSED FROM: %s\nREFUSED DATA: %s\n", clientAddress, (const char*)buffer->data);
            }
        }
        fflush(stdout);
    }
}

