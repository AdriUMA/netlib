#include "udp/listener.h"
#include "udp/sender.h"
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 55155
#define BUFFERSIZE 1024
#define USERBUFFER 22

pid_t listenerPID, senderPID;
Listener listener;
Sender sender;

void signalHandler(int handler) {
    if (handler == SIGINT){
        if (listenerPID == 0) closeListener(listener);
        else {
            kill(listenerPID, SIGINT);
            closeSender(sender);
        }
        exit(EXIT_SUCCESS);
    }
}

void listenerHandler() {
    listener = openListener(PORT, BUFFERSIZE);
    if (listener == NULL) {
        kill(senderPID, SIGINT);
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        waitFrame(listener);
        printf("%s\n", (const char*)listener->buffer.data);
        fflush(stdout);
    }    
    
    closeListener(listener);
}

void senderHandler(char* address, char* username){
    sender = openSender(address, PORT, BUFFERSIZE);
    char header[USERBUFFER+2];
    
    char* message = malloc(sender->bufferSize);
    if (message == NULL) {
        kill(listenerPID, SIGINT);
        exit(EXIT_FAILURE);
    }

    header[0] = '\0';
    message[0] = '\0';

    strcat(header, username);
    strcat(header, ": ");
    strcat(message, header);

    while (1) {
        scanf("\n%[^\n]", (message+strlen(header)));
        
        message[BUFFERSIZE-1] = '\0';

        sendFrame(sender, message, strlen(message)+1);
    }

    free(message);
}

int main () {
    char address[128];
    char* username = malloc(USERBUFFER);
    if (username == NULL) exit(EXIT_FAILURE);

    // Address
    printf("\nReciever Address: ");
    scanf("%s", address);
    
    // Username
    printf("\nUsername: ");
    scanf("%s", username);

    if (strlen(username) < USERBUFFER){
        for (int i = strlen(username); i < USERBUFFER; i++) {
            username[i] = ' ';
        }
    }
    
    username[USERBUFFER-1] = '\0';
    
    // Fork and PIDs
    senderPID = getpid();
    listenerPID = fork();

    if (listenerPID < 0) exit(EXIT_FAILURE);

    // Signal interruption handler
    signal(SIGINT, signalHandler);

    // Proccess behaviour divisor
    if (listenerPID == 0){
        listenerHandler();
    }else{
        senderHandler(address, username);
    }
}