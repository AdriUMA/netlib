#ifndef SENDER_H
#define SENDER_H

typedef struct str_sender {
    char* address;
    unsigned port;
    int socketFD;
    unsigned bufferSize;
}* Sender;

/** @brief Allocate in memory and open sender socket
 *  @param address Server address
 *  @param port Server listener port
 *  @param bufferSize Server buffer
 *  @return Pointer to struct in memory or NULL if socket or memory are busy 
 */
Sender openSender(char* address, unsigned port, unsigned bufferSize);

/** @brief Close socket and free memory
 *  @param sender
 */
void closeSender(Sender sender);

/** @brief Send a number of bytes
 *  @param data Bytes
 *  @param dataLength Number of bytes
 *  @return Returns the number sent, or -1 for errors.
 */
int sendFrame(Sender sender, void* data, unsigned dataLength);

#endif