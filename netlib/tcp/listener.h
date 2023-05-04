#ifndef NETLIB_TCP_LISTENER_H
#define NETLIB_TCP_LISTENER_H

#include "../buffer.h"
#include <netinet/in.h>

/*listener struct*/
typedef struct str_tcplistener {
    unsigned port;
    int socketFD;
}* TCPListener;

/*client struct*/
typedef struct str_tcpclient {
    struct sockaddr_in clientInfo;
    int socket;
}* TCPClient;

/** @brief Allocate in memory and open listener socket
 *  @param port
 *  @param maxConnections Open connection limit
 *  @return Pointer to struct in memory or NULL if socket or memory are busy 
 */
TCPListener openTCPListener(unsigned port, unsigned maxConnections);

/** @brief Close socket and free memory
 *  @param listener
 */
void closeTCPListener(TCPListener listener);

/** @brief Sleep waiting for new client
 *  @param listener
 *  @return Client
 */
TCPClient acceptTCP(TCPListener listener);

/** @brief Sleep waiting for a frame from connected client
 *  @param buffer If data length is zero, client is disconnecting
 *  @param client
 */
void listenTCP(Buffer buffer, TCPClient client);

/** @brief Send response to a client
 *  @param buffer Response
 *  @param client
 *  @return Bytes sent. -1 if error
 */
int replyTCP(Buffer buffer, TCPClient client);

/** @brief Close client connections
 *  @param client
 */
void closeClient(TCPClient client);

#endif
