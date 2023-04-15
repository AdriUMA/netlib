#include "addressList.h"
#include <stdlib.h>
#include <string.h>

void createList(AddressList *addressList){
    *addressList = NULL;
}

void deleteList(AddressList *address){
    AddressList previous = NULL;
    AddressList current = *address;

    while (current != NULL) {
        previous = current;
        current = current->next;
        free(previous);
    }
}

void insertAddress(AddressList* addressList, char* address){
    AddressList newAddress = malloc(sizeof(AddressList));
    if(newAddress == NULL) return;

    newAddress->next = NULL;
    strcpy(newAddress->address,address);

    if(*addressList == NULL){
        *addressList = newAddress;
    }else{
        AddressList previous = NULL;
        AddressList current = *addressList;

        while (current != NULL)
        {
            if(strcmp(current->address, address)){
                free(newAddress);
                return;
            }

            previous = current;
            current = current->next;
        }

        previous->next = newAddress;
    }
}

void removeAddress(AddressList* addressList, char* address){
    if(addressList == NULL) return;

    AddressList previous = NULL;
    AddressList current = *addressList;

    while(current != NULL && strcmp(current->address, address) == 1){
        previous = current;
        current = current->next;
    }

    if(current != NULL){

        if(*addressList == current){
            *addressList = current->next;
        }else{
            previous = current->next;
        }
        free(current);

    }
}