#include "senderList.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void createList(SenderList* senderList){
    *senderList = NULL;
}

void deleteList(SenderList* senderList){
    SenderList previous = NULL;
    SenderList current = *senderList;

    while (current != NULL) {
        // Iterate to the next node
        previous = current;
        current = current->next;

        // Close Socket and free Sender memory
        closeSender(previous->sender);

        // Free list memory
        free(previous);
    }

    *senderList = NULL;
}

Sender insertSender(SenderList* senderList, char* address, unsigned port, unsigned bufferSize){
    // Sender to add
    SenderList newSender = malloc(sizeof(struct str_senderList));
    if(newSender == NULL) return NULL;

    // New sender inicialization
    newSender->next = NULL;

    // If the list is empty
    if(*senderList == NULL){
        *senderList = newSender;

        // Open socket
        newSender->sender = openSender(address, port, bufferSize);

        // If fails
        if(newSender->sender == NULL){
            // List will keep empty
            *senderList = NULL;

            // Free memory
            free(newSender);
            return NULL;
        }

    }else{
        SenderList previous = NULL;
        SenderList current = *senderList;

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
        newSender->sender = openSender(address, port, bufferSize);

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

void removeSender(SenderList* senderList, char* address){
    if(*senderList == NULL) return;

    SenderList current = *senderList;
    SenderList previous = current;

    // If first element is the target
    if(strcmp(current->sender->address, address) == 0){
        // senderList will point to the second
        *senderList = current->next;

        // Then, free memory
        closeSender(current->sender);
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
        closeSender(current->sender);
        free(current);
    }
}