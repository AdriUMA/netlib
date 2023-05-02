#ifndef NETLIB_TCP_LISTENER_H
#define NETLIB_TCP_LISTENER_H

#ifndef NETLIB_BUFFER
#define NETLIB_BUFFER
typedef struct str_buffer {
    unsigned size;
    void* data;
    unsigned dataSize;
} Buffer;
#endif

/*listener struct*/
typedef struct str_tcplistener {
    unsigned port;
    int socketFD;
    Buffer buffer;
}* TCPListener;

/** @brief Allocate in memory and open listener socket
 *  @param port
 *  @param bufferSize
 *  @return Pointer to struct in memory or NULL if socket or memory are busy 
 */
TCPListener openTCPListener(unsigned port, unsigned bufferSize);

/** @brief Close socket and free memory
 *  @param listener
 */
void closeTCPListener(TCPListener listener);

/** @brief Sleep waiting for a frame
 *  @param listener
 *  @return Source address
 */
char* listenTCP(TCPListener listener);

#endif
