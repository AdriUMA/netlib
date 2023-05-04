#include "env.h"
#include "../../netlib/netlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>
#include <unistd.h>

TCPSender sender;
Buffer buffer;

void handler (int signal) {
    if (signal == SIGINT){
        closeTCPSender(sender);
        closeBuffer(buffer);
        exit(EXIT_SUCCESS);
    }
}

int main(){
    signal(SIGINT, handler);

    int tries = 0;
    float waitForRetry = 0;

    while (sender == NULL && tries < 3) {
        sleep(waitForRetry);

        printf("\nConnecting to the server...");
        fflush(stdout);

        sender = openTCPSender("127.0.0.1", SERVER_PORT);
        tries++;

        waitForRetry = 1;
    }

    buffer = openBuffer(SERVER_BUFFER);
    if (sender == NULL || buffer == NULL) {
        printf("\nCould not connect\n");
        exit(EXIT_FAILURE);
    }
    
    printf("\nConnected\n");
    fflush(stdout);

    char user[30] = "Client";
    char str[SERVER_BUFFER - (2 + strlen(user))];
    char data[SERVER_BUFFER];

    do {
        scanf("\n%[^\n]", str);

        strcpy(data, user);
        strcat(data, ": ");
        strcat(data, str);

        stringToBuffer(buffer, data);

        sendTCPSender(sender, buffer);

        printf("Sent, waiting response from server...");
        fflush(stdout);

        waitResponse(sender, buffer);
        if(buffer->dataSize > 0) printf("\n[*] SERVER: %s\n", (char*)buffer->data);
        fflush(stdout);
    } while (buffer->dataSize > 0); 

    printf("\n\nThe server has been closed\n");
    fflush(stdout);

    closeTCPSender(sender);
}