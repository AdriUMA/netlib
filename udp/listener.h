#ifndef LISTENER_H
#define LISTENER_H

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

void closeListener(Listener listener);

int  waitFrame(Listener listener);

#endif
