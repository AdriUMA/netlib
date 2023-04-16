#include "udp/listener.h"
#include "udp/sender.h"
#include "linkedlist/addressList.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 55155
#define BUFFERSIZE 1024

Listener listener;
AddressList addressList;

void signalHandler(int handler) {
    if (handler == SIGINT){
        closeListener(listener);
        exit(EXIT_SUCCESS);
    }
}

void noticeHosts(char* frameOwner, const Buffer* buffer){
    Sender sender;
    AddressList current = addressList;

    while (current != NULL) {
        if (strcmp(frameOwner, current->address) != 0){
            sender = openSender(current->address, PORT, BUFFERSIZE);
            if (sender != NULL){
                sendFrame(sender, buffer->data, buffer->dataSize);
                closeSender(sender);
            }
        }
        current = current->next;
    }
}


void listenerHandler() {
    char from[20];
    char debug[BUFFERSIZE+100];

    printf("###DEBUG -> Entrando al listener\n");

    while(1)
    {
        strcpy(from, waitFrame(listener));

        // Send to other hosts new info
        noticeHosts(from, (const Buffer*)&listener->buffer);

        // Prepare debug log
        strcpy(debug, "FROM: ");
        strcat(debug, from);
        strcat(debug, " | DATA: ");
        strcat(debug, (const char*)listener->buffer.data);

        // Show debug
        printf("%s\n", debug);
        fflush(stdout);

        insertAddress(&addressList, from);
    }    
    
    closeListener(listener);
}


int main () {
    createList(&addressList);

    listener = openListener(PORT, BUFFERSIZE);
    if (listener == NULL) exit(EXIT_FAILURE);

    // Signal interruption handler
    signal(SIGINT, signalHandler);

    listenerHandler();
    
    return EXIT_SUCCESS;
}