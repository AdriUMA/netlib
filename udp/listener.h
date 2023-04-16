#ifndef LISTENER_H
#define LISTENER_H

#include <netinet/in.h>
#include <sys/socket.h>

typedef struct str_buffer {
    unsigned size;
    void* data;
    unsigned dataSize;
} Buffer;

/*listener struct*/
typedef struct str_listener {
    unsigned port;
    int socketFD;
    Buffer buffer;
}* Listener;

/** @brief Allocate in memory and open listener socket
 *  @param port
 *  @param bufferSize
 *  @return Pointer to struct in memory or NULL if socket or memory are busy 
 */
Listener openListener(unsigned port, unsigned bufferSize);

/** @brief Close socket and free memory
 *  @param listener
 */
void closeListener(Listener listener);

/** @brief Sleep waiting for a frame
 *  @param listener
 *  @return Source address
 */
char* waitFrame(Listener listener);

#endif
