#include "udp/listener.h"
#include "udp/sender.h"
#include "linkedlist/addressList.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

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

void noticeHosts(char* frameOwner, Buffer* buffer){
    Sender sender;
    AddressList current = addressList;

    while (current != NULL) {
        if (!strcmp(frameOwner, current->address)){
            sender = openSender(current->address, PORT, BUFFERSIZE);
            sendFrame(sender, buffer->data, buffer->dataSize);
            closeSender(sender);
        }
        current = current->next;
    }
}


void listenerHandler() {
    char* from;

    while(1)
    {
        from = waitFrame(listener);
        insertAddress(&addressList, from);

        printf("FROM: %s | DATA: %s\n", from, (const char*)listener->buffer.data);

        noticeHosts(from, &listener->buffer);

        fflush(stdout);
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