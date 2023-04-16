#ifndef ADDRESSLIST_H
#define ADDRESSLIST_H

#define ADDRESS_SIZE 15

typedef struct str_addressList* AddressList;

struct str_addressList {
    char address[ADDRESS_SIZE];
    AddressList next;
};

void createList(AddressList* addressList);

void deleteList(AddressList* addressList);

void insertAddress(AddressList* addressList, char* address);

void removeAddress(AddressList* addressList, char* address);

#endif