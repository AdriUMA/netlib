#ifndef SENDERLIST_H
#define SENDERLIST_H

#include "../udp/sender.h"

typedef struct str_senderList* SenderList;

struct str_senderList {
    Sender sender;
    SenderList next;
};

/** @brief List initialization
 *  @param senderList
 */
void createList(SenderList* senderList);

/** @brief Delete all the list.
 *  @param senderList
 */
void deleteList(SenderList* senderList);

/** @brief Add new sender to the list
 *  @param senderList
 *  @param address Listener (destination) address
 *  @param port Listener (destination) port
 *  @param bufferSize Listener (destination) buffer
 */
void insertSender(SenderList* senderList, char* address, unsigned port, unsigned bufferSize);

/** @brief Remove one sender by address.
 *  @param senderList
 *  @param address
 */
void removeSender(SenderList* senderList, char* address);

#endif