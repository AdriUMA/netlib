#include "env.h"
#include "../../netlib/netlib.h"
#include <arpa/inet.h>
#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>
#include <unistd.h>
#include <pthread.h>

TCPListener listener;
Buffer buffer;

void handler (int signal) {
	printf("\n[*] Stoping server");
    fflush(stdout);
	
	closeTCPListener(listener);
	closeBuffer(buffer);

	printf("\n[*] Shutdown\n");
    fflush(stdout);
	
	exit(EXIT_SUCCESS);
}

void *attend(void* tcpClient);

int main(){
    signal(SIGINT, handler);

    printf("\n[*] Starting http echo server. Port: %i", SERVER_PORT);
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
        
		pthread_t thread;

		if (pthread_create(&thread, NULL, attend, client) != 0) {
			printf("\n[*] Error creating thread");
        	fflush(stdout);
		}
    }

    closeTCPListener(listener);

}

void *attend(void* tcpClient){
		TCPClient client = (TCPClient)tcpClient;

        printf("\n[+] Connected %s:%i by %i local socket", inet_ntoa(client->clientInfo.sin_addr), client->clientInfo.sin_port, client->socket);
        fflush(stdout);

		listenTCP(buffer, client);

		printf("\n%s", (char*)buffer->data);
		fflush(stdout);
    	fflush(stdout);

		stringIntoBuffer(buffer, "HTTP/1.1 404 OK\nServer: Linux Server (Made with netlib in C)\nContent-Type: text/html\nConnection: Closed\n\n<html lang=\"es\">\n<body><p>HTTP simple echo server made with <a href=\"https://github.com/AdriUMA/netlib\">Netlib</a> in C</p></body></html>");
		replyTCP(buffer, client);
		
		fflush(stdout);

        printf("\n[-] Disonnected %s:%i by %i local socket", inet_ntoa(client->clientInfo.sin_addr), client->clientInfo.sin_port, client->socket);
        fflush(stdout);
        closeClient(client);
}