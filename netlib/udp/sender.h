#ifndef NETLIB_UDP_SENDER_H
#define NETLIB_UDP_SENDER_H

typedef struct str_udpsender {
    char* address;
    unsigned port;
    int socketFD;
    unsigned bufferSize;
}* UDPSender;

/** @brief Allocate in memory and open sender socket
 *  @param address Server address
 *  @param port Server listener port
 *  @param bufferSize Server buffer
 *  @return Pointer to struct in memory or NULL if socket or memory are busy 
 */
UDPSender openUDPSender(char* address, unsigned port, unsigned bufferSize);

/** @brief Close socket and free memory
 *  @param sender
 */
void closeUDPSender(UDPSender sender);

/** @brief Send a number of bytes
 *  @param data Bytes
 *  @param dataLength Number of bytes
 *  @return Returns the number sent, or -1 for errors.
 */
int sendUDP(UDPSender sender, void* data, unsigned dataLength);

#endif