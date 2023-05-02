#include "env.h"
#include "../netlib/netlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>

TCPListener listener;

void handler (int signal) {
    if (signal == SIGINT){
        closeTCPListener(listener);
        exit(EXIT_SUCCESS);
    }
}

int main(){
    signal(SIGINT, handler);

    listener = openTCPListener(SERVER_PORT, SERVER_BUFFER);
    char addr[100];

    if (listener == NULL) exit(EXIT_FAILURE);

    while (1) {
        strcpy(addr, listenTCP(listener));
        printf("%s -> %s\n", addr, (char*)listener->buffer.data);
        fflush(stdout);
    }

    closeTCPListener(listener);

}