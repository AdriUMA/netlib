#include "udp/listener.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 55155
#define BUFFERSIZE 1024

Listener listener;

void signalHandler(int handler) {
    if (handler == SIGINT){
        closeListener(listener);
        exit(EXIT_SUCCESS);
    }
}

void listenerHandler() {
    listener = openListener(PORT, BUFFERSIZE);
    if (listener == NULL) exit(EXIT_FAILURE);

    while(1)
    {
        waitFrame(listener);
        printf("%s\n", (const char*)listener->buffer.data);
        fflush(stdout);
    }    
    
    closeListener(listener);
}

int main () {
    // Signal interruption handler
    signal(SIGINT, signalHandler);

    listenerHandler();
    
    return EXIT_SUCCESS;
}