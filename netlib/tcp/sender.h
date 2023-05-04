#ifndef NETLIB_TCP_SENDER_H
#define NETLIB_TCP_SENDER_H

#include "../buffer.h"

typedef struct str_tcpsender {
    char* address;
    unsigned port;
    int socketFD;
}* TCPSender;

/** @brief Allocate in memory and open sender socket
 *  @param address Server address
 *  @param port Server listener port
 *  @param bufferSize Server buffer
 *  @return Pointer to struct in memory or NULL if socket or memory are busy 
 */
TCPSender openTCPSender(char* address, unsigned port);

/** @brief Close socket and free memory
 *  @param sender
 */
void closeTCPSender(TCPSender sender);

/** @brief Send a number of bytes
 *  @param data Bytes
 *  @param dataLength Number of bytes
 *  @return Returns the number of bytes sent, or -1 for errors
 */
int sendTCPSender(TCPSender sender, Buffer buffer);

/** @brief Wait for server response
 *  @param sender
 *  @param buffer Data from server
 *  @return Returns the number of bytes recieved, or -1 for errors
 */
int waitResponse(TCPSender sender, Buffer buffer);

#endif