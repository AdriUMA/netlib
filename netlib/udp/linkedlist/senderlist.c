#include "senderlist.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void createUDPSenderList(UDPSenderList* senderList){
    *senderList = NULL;
}

void deleteUDPSenderList(UDPSenderList* senderList){
    UDPSenderList previous = NULL;
    UDPSenderList current = *senderList;

    while (current != NULL) {
        // Iterate to the next node
        previous = current;
        current = current->next;

        // Close Socket and free Sender memory
        closeUDPSender(previous->sender);

        // Free list memory
        free(previous);
    }

    *senderList = NULL;
}

UDPSender insertUDPSender(UDPSenderList* senderList, char* address, unsigned port, unsigned bufferSize){
    // Sender to add
    UDPSenderList newSender = malloc(sizeof(struct str_udpsenderlist));
    if(newSender == NULL) return NULL;

    // New sender inicialization
    newSender->next = NULL;

    // If the list is empty
    if(*senderList == NULL){
        *senderList = newSender;

        // Open socket
        newSender->sender = openUDPSender(address, port);

        // If fails
        if(newSender->sender == NULL){
            // List will keep empty
            *senderList = NULL;

            // Free memory
            free(newSender);
            return NULL;
        }

    }else{
        UDPSenderList previous = NULL;
        UDPSenderList current = *senderList;

        // Iterates all the list
        while (current != NULL)
        {
            // If address exits in the list
            if(strcmp(current->sender->address, address) == 0){
                // Free memory                
                free(newSender);
                return NULL;
            }

            previous = current;
            current = current->next;
        }

        previous->next = newSender;

        // Open socket
        newSender->sender = openUDPSender(address, port);

        // If fails
        if(newSender->sender == NULL){
            // List will not change
            previous->next = NULL;

            // Free memory
            free(newSender);
            return NULL;
        }
    }

    return newSender->sender;
}

void removeUDPSender(UDPSenderList* senderList, char* address){
    if(*senderList == NULL) return;

    UDPSenderList current = *senderList;
    UDPSenderList previous = current;

    // If first element is the target
    if(strcmp(current->sender->address, address) == 0){
        // senderList will point to the second
        *senderList = current->next;

        // Then, free memory
        closeUDPSender(current->sender);
        free(current);
        return;
    }else{
        current = current->next;
    }

    // Iterates and stop when the address matches
    while(current != NULL && strcmp(current->sender->address, address) != 0){
        previous = current;
        current = current->next;
    }
    
    // If current is equal NULL, no elements has to be removed 
    if(current != NULL){
        // Previous point to the next->next
        previous->next = current->next;

        // Free memory
        closeUDPSender(current->sender);
        free(current);
    }
}