#ifndef LISTENER_H
#define LISTENER_H

#include <stdlib.h>
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


Listener openListener(unsigned port, unsigned bufferSize);

int closeListener(Listener listener);

int  waitFrame(Listener listener);

#endif
