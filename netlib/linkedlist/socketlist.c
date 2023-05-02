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

void insertSocket(SocketList* socketList, int socket){
    SocketList newSocket = malloc(sizeof(struct str_socketList));
    if(newSocket == NULL) return;

    newSocket->next = NULL;
    newSocket->socket = socket;

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

void removeSocket(SocketList* socketList, int socket){
    if(*socketList == NULL) return;

    SocketList current = *socketList;
    SocketList previous = current;

    if(current->socket == socket){
        *socketList = current->next;
        free(current);
        return;
    }else{
        current = current->next;
    }

    while(current != NULL && current->socket != socket){
        previous = current;
        current = current->next;
    }
    
    if(current != NULL){
        previous->next = current->next;
        free(current);
    }
}