#ifndef NETLIB_UDP_LISTENER_H
#define NETLIB_UDP_LISTENER_H

#include "../buffer.h"

/*listener struct*/
typedef struct str_udplistener {
    unsigned port;
    int socketFD;
}* UDPListener;

/** @brief Allocate in memory and open listener socket
 *  @param port
 *  @return Pointer to struct in memory or NULL if socket or memory are busy 
 */
UDPListener openUDPListener(unsigned port);

/** @brief Close socket and free memory
 *  @param listener
 */
void closeUDPListener(UDPListener listener);

/** @brief Sleep waiting for a frame
 *  @param buffer
 *  @param listener
 *  @return Source address
 */
char* listenUDP(Buffer buffer, UDPListener listener);

#endif
