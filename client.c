#include "udp/listener.h"
#include "udp/sender.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>

// Ports
#define SERVER_PORT 55154
#define LISTENER_PORT 55155
// Buffer and connection
#define SERVER_BUFFER 1024
#define NOTICE_CONNECT "::::::::::CONNECT::::::::::\0"
#define NOTICE_DISCONNECT "::::::::::DISCONNECT::::::::::\0"

// Dad will be the sender
pid_t senderPid;
Sender sender;

// Child will be the listener
pid_t childPid;
Listener listener;

void signalHandler(int signal){
    if (signal == SIGINT){
        if (childPid == 0) {
            if (listener != NULL) closeListener(listener);
            exit(EXIT_SUCCESS);
        }else{
            kill(childPid, SIGINT);
            wait(NULL);

            if (sender != NULL){
                // If sender is available, send to server our disconnection
                sendFrame(sender, NOTICE_DISCONNECT, strlen(NOTICE_DISCONNECT)+1);
                closeSender(sender);
            }

            exit(EXIT_SUCCESS);
        }
    }
}

void listenerManager();
void senderManager();

int main() {
    // Signal manager
    signal(SIGINT, signalHandler);

    // Proccess division
    senderPid = getpid();
    childPid = fork();

    if (childPid < 0){
        perror("Error opening child proccess");
    }else{
        if (childPid == 0){
            listenerManager();
        }else {
            senderManager();
        }
    }

    return EXIT_SUCCESS;
}

void listenerManager(){
    // Open listener
    listener = openListener(LISTENER_PORT, SERVER_BUFFER);
    
    // Error opening listener socket
    if (listener == NULL){
        perror("\nError opening listener\n");
        kill(senderPid, SIGINT);
    }

    // Listening
    while (1) {
        waitFrame(listener);
        printf("\n> %s\n", (const char*)listener->buffer.data);
    }

    // Interruption exception
    perror("\nUnexpected error: Listener stop working\n");
    closeListener(listener);
}

void senderManager() {
    

    int infoLen = 20;
    char serverAddress[infoLen];
    char name[infoLen];
    char* buffer;
    unsigned bufferInitialPosition;

    // Server address and name
    printf("Server address: ");
    scanf("%s", serverAddress);
    serverAddress[infoLen-1] = '\0';

    printf("Name: ");
    scanf("\n%[^\n]", name);
    name[infoLen-1] = '\0';

    // Header (format -> 'name :') 
    bufferInitialPosition = sizeof(char)*(strlen(name)+2);
    buffer = malloc(SERVER_BUFFER);
    
    if (buffer == NULL) kill(senderPid, SIGINT);

    strcpy(buffer, name);
    strcat(buffer, ": ");

    // Open sender
    sender = openSender(serverAddress, SERVER_PORT, SERVER_BUFFER);

    // Error opening sender socket
    if (sender == NULL){
        perror("\nError opening sender\n");
        kill(senderPid, SIGINT);
    }

    // Notice to the server our connection
    sendFrame(sender, NOTICE_CONNECT, strlen(NOTICE_CONNECT)+1);

    // Read and send loop
    while (1) {
        scanf("\n%[^\n]", &buffer[bufferInitialPosition]);
        sendFrame(sender, (void*)buffer, strlen(buffer)+1);
    }

    // Interruption exception
    perror("\nUnexpected error: Sender stop working\n");
    closeSender(sender);
}