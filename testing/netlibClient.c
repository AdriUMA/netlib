#include "env.h"
#include "../netlib/netlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>

TCPSender sender;

void handler (int signal) {
    if (signal == SIGINT){
        closeTCPSender(sender);
        exit(EXIT_SUCCESS);
    }
}

int main(){
    signal(SIGINT, handler);

    sender = openTCPSender("127.0.0.1", SERVER_PORT, SERVER_BUFFER);
    if (sender == NULL) exit(EXIT_FAILURE);

    char user[30] = "ATM";
    char str[SERVER_BUFFER - (2 + strlen(user))];
    char data[SERVER_BUFFER];

    while (1) {
        scanf("\n%[^\n]", str);

        strcpy(data, user);
        strcat(data, ": ");
        strcat(data, str);

        sendTCP(sender, data, strlen(data)+1);

        printf("send");
    }

    closeTCPSender(sender);
}