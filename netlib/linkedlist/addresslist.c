#include "addresslist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void createAddressList(AddressList *addressList){
    *addressList = NULL;
}

void deleteAddressList(AddressList *addressList){
    AddressList previous = NULL;
    AddressList current = *addressList;

    while (current != NULL) {
        previous = current;
        current = current->next;
        free(previous);
    }

    *addressList = NULL;
}

void insertAddress(AddressList* addressList, char* address){
    AddressList newAddress = malloc(sizeof(struct str_addressList));
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
            if(strcmp(current->address, address) == 0){
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
    if(*addressList == NULL) return;

    AddressList current = *addressList;
    AddressList previous = current;

    if(strcmp(current->address, address) == 0){
        *addressList = current->next;
        free(current);
        return;
    }else{
        current = current->next;
    }

    while(current != NULL && strcmp(current->address, address) != 0){
        previous = current;
        current = current->next;
    }
    
    if(current != NULL){

        previous->next = current->next;
        free(current);

    }
}