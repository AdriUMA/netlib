#ifndef NETLIB_UDP_LINKEDLIST_SENDERLIST_H
#define NETLIB_UDP_LINKEDLIST_SENDERLIST_H

#include "../sender.h"

typedef struct str_udpsenderlist* UDPSenderList;

struct str_udpsenderlist {
    UDPSender sender;
    UDPSenderList next;
};

/** @brief List initialization
 *  @param senderList
 */
void createUDPSenderList(UDPSenderList* senderList);

/** @brief Delete all the list.
 *  @param senderList
 */
void deleteUDPSenderList(UDPSenderList* senderList);

/** @brief Add new sender to the list
 *  @param senderList
 *  @param address Listener (destination) address
 *  @param port Listener (destination) port
 *  @param bufferSize Listener (destination) buffer
 *  @return Sender or NULL if socket opening fails
 */
UDPSender insertUDPSender(UDPSenderList* senderList, char* address, unsigned port, unsigned bufferSize);

/** @brief Remove one sender by address.
 *  @param senderList
 *  @param address
 */
void removeUDPSender(UDPSenderList* senderList, char* address);

#endif