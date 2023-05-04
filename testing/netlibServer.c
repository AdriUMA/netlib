#include "env.h"
#include "../netlib/netlib.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>
#include <unistd.h>

TCPListener listener;
Buffer buffer;

void handler (int signal) {
    if (signal == SIGINT){
        closeTCPListener(listener);
        closeBuffer(buffer);
        exit(EXIT_SUCCESS);
    }
}

int main(){
    signal(SIGINT, handler);

    printf("\n[*] Starting server");
    fflush(stdout);

    listener = openTCPListener(SERVER_PORT, 10);
    buffer = openBuffer(SERVER_BUFFER);
    char addr[100];

    if (listener == NULL || buffer == NULL) exit(EXIT_FAILURE);

    printf("\n[*] Server started");
    fflush(stdout);

    while (1) {
        printf("\n[*] Waiting for new client");
        fflush(stdout);

        TCPClient client = acceptTCP(listener);
        
        printf("\n[+] Connected %s:%i by %i local socket", inet_ntoa(client->clientInfo.sin_addr), client->clientInfo.sin_port, client->socket);
        fflush(stdout);

        do {
            listenTCP(buffer, client);
            printf("\n%s", (char*)buffer->data);
            fflush(stdout);

            stringToBuffer(buffer, "RecievedSuccess");
            replyTCP(buffer, client);
            
            printf(" %u", buffer->dataSize);
            fflush(stdout);
            
            sleep(2);
        } while(buffer->dataSize > 0);

        printf("\n[-] Disonnected %s:%i by %i local socket", inet_ntoa(client->clientInfo.sin_addr), client->clientInfo.sin_port, client->socket);
        fflush(stdout);
        closeClient(client);
    }

    closeTCPListener(listener);

}