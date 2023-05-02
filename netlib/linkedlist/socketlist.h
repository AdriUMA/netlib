#ifndef NETLIB_LINKEDLIST_SOCKETLIST_H
#define NETLIB_LINKEDLIST_SOCKETLIST_H

#define ADDRESS_SIZE 20

typedef struct str_socketList* SocketList;

struct str_socketList {
    char address[ADDRESS_SIZE];
    int socket;
    SocketList next;
};

void createSocketList(SocketList* socketList);

void deleteSocketList(SocketList* socketList);

void insertSocket(SocketList* socketList, int socket, char* address);

void removeSocket(SocketList* socketList, int socket, char* address);

// 0 if exists, -1 if not
int getSocket(SocketList* socketList, char* address);

#endif