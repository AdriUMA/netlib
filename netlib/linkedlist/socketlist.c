#include "socketlist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void createSocketList(SocketList *socketList){
    *socketList = NULL;
}

void deleteSocketList(SocketList *socketList){
    SocketList previous = NULL;
    SocketList current = *socketList;

    while (current != NULL) {
        previous = current;
        current = current->next;
        free(previous);
    }

    *socketList = NULL;
}

void insertSocket(SocketList* socketList, int socket, char* address){
    SocketList newSocket = malloc(sizeof(struct str_socketList));
    if(newSocket == NULL) return;

    newSocket->next = NULL;
    newSocket->socket = socket;
    strcpy(newSocket->address, address);

    if(*socketList == NULL){
        *socketList = newSocket;
    }else{
        SocketList previous = NULL;
        SocketList current = *socketList;

        while (current != NULL)
        {
            if(current->socket == socket){
                free(newSocket);
                return;
            }

            previous = current;
            current = current->next;
        }

        previous->next = newSocket;
    }
}

void removeSocket(SocketList* socketList, int socket, char* address){
    if(*socketList == NULL) return;

    SocketList current = *socketList;
    SocketList previous = current;

    if(current->socket == socket && strcmp(current->address, address) == 0){
        *socketList = current->next;
        free(current);
        return;
    }else{
        current = current->next;
    }

    while(current != NULL && current->socket != socket && strcmp(current->address, address) != 0){
        previous = current;
        current = current->next;
    }
    
    if(current != NULL){
        previous->next = current->next;
        free(current);
    }
}

int getSocket(SocketList* socketList, char* address){
    if(*socketList == NULL) return -1;

    SocketList current = *socketList;

    while(current != NULL){
        if (strcmp(current->address, address) == 0) return current->socket;
        current = current->next;
    }
    
    return -1;
}
