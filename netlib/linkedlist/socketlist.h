#ifndef NETLIB_LINKEDLIST_SOCKETLIST_H
#define NETLIB_LINKEDLIST_SOCKETLIST_H

#define ADDRESS_SIZE 20

typedef struct str_socketList* SocketList;

struct str_socketList {
    int socket;
    SocketList next;
};

void createSocketList(SocketList* socketList);

void deleteSocketList(SocketList* socketList);

void insertSocket(SocketList* socketList, int socket);

void removeSocket(SocketList* socketList, int socket);

#endif