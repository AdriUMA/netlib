#include "ports.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// Dad will be the sender
pid_t senderPid;
UDPSender sender;

// Child will be the listener
pid_t childPid;
UDPListener listener;

int connection = 0;

void signalHandler(int signal){
    if (signal == SIGINT){
        if (childPid == 0) {
            if (listener != NULL) closeUDPListener(listener);
            exit(EXIT_SUCCESS);
        }else{
            kill(childPid, SIGINT);
            wait(NULL);

            if (sender != NULL){
                // If sender is available, send to server our disconnection
                sendUDP(sender, NOTICE_DISCONNECT, strlen(NOTICE_DISCONNECT)+1);
                closeUDPSender(sender);
            }

            exit(EXIT_SUCCESS);
        }
    }
    else if(signal == SIGUSR1){
        connection = 1;
    }
}

void listenerManager();
void senderManager();
int main() {
    // Signal manager
    signal(SIGINT, signalHandler);

    VERSION;

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
    listener = openUDPListener(CLIENT_PORT, SERVER_BUFFER);
    Buffer buffer = openBuffer(SERVER_BUFFER);

    // Error opening listener socket
    if (listener == NULL){
        perror("\nError opening listener");
        kill(senderPid, SIGINT);
    }

    // Listening
    while (1) {
        listenUDP(listener);
        if(connection == 0){
            // If connection is not established, we are waiting for server notice
            if (strcmp((const char*)buffer->data, WELCOME_MESSAGE) == 0){
                // If server notice us, we are connected
                connection = 1;
                kill(senderPid, SIGUSR1);
            }
        }
        printf("\n> %s\n", (const char*)buffer->data);
    }

    // Interruption exception
    perror("\nUnexpected error: Listener stop working");
    closeUDPListener(listener);
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
    sender = openUDPSender(serverAddress, SERVER_PORT, SERVER_BUFFER);

    // Error opening sender socket
    if (sender == NULL){
        perror("\nError opening sender\n");
        kill(senderPid, SIGINT);
    }

    // Notice to the server our connection
    printf("Waiting server response\n");

    signal(SIGUSR1, signalHandler);

    int sleepTime = 5;
    while(connection == 0 && sleepTime != 0){
        sendUDP(sender, NOTICE_CONNECT, strlen(NOTICE_CONNECT)+1);
        sleepTime--;
        sleep(1);
    }
    if(connection == 0){
        perror("\nServer not responding\n");
        kill(senderPid, SIGINT);
    }

    // Read and send loop
    while (connection) {
        scanf("\n%[^\n]", &buffer[bufferInitialPosition]);
        sendUDP(sender, (void*)buffer, strlen(buffer)+1);
    }

    // Interruption exception
    perror("\nUnexpected error: Sender stop working\n");
    closeUDPSender(sender);
}