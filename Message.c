#include "udp/listener.h"
#include "udp/sender.h"
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
        else closeSender(sender);
        exit(EXIT_SUCCESS);
    }
}

void listenerHandler(char* username) {
    listener = openListener(PORT, BUFFERSIZE);
    if (listener == NULL) {
        kill(senderPID, SIGINT);
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        waitFrame(listener);
        printf("%s: %s\n", username, (const char*)listener->buffer.data);
    }    
    
    closeListener(listener);
}

void senderHandler(char* address, char* username){
    sender = openSender(address, PORT, BUFFERSIZE);

    char* message = malloc(sender->bufferSize);
    if (message == NULL) {
        kill(listenerPID, SIGINT);
        exit(EXIT_FAILURE);
    }

    strcpy(username, ": ");
    strcpy(username, message);

    while (1) {
        if (scanf("%s", message)) message[BUFFERSIZE-1] = '\0';
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
    username[USERBUFFER-1] = '\0';

    // Fork and PIDs
    senderPID = getpid();
    listenerPID = fork();

    // Proccess behaviour divisor
    if (listenerPID == 0){
        listenerHandler(username);
    }else{
        senderHandler(address, username);
    }
}