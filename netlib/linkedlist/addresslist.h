#ifndef NETLIB_LINKEDLIST_ADDRESSLIST_H
#define NETLIB_LINKEDLIST_ADDRESSLIST_H

#define ADDRESS_SIZE 20

typedef struct str_addressList* AddressList;

struct str_addressList {
    char address[ADDRESS_SIZE];
    AddressList next;
};

void createAddressList(AddressList* addressList);

void deleteAddressList(AddressList* addressList);

void insertAddress(AddressList* addressList, char* address);

void removeAddress(AddressList* addressList, char* address);

#endif