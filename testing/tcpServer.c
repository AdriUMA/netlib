#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error al crear el socket");
        exit(1);
    }

    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(55155);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error al vincular el socket");
        exit(1);
    }

    if (listen(sockfd, 1) < 0) {
        perror("Error al esperar conexiones");
        exit(1);
    }

    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
        perror("Error al aceptar la conexión");
        exit(1);
    }

    char buffer[256];
    int n = recv(newsockfd, buffer, sizeof(buffer), 0);
    if (n < 0) {
        perror("Error al leer los datos");
        exit(1);
    }

    printf("Datos recibidos: %s\n", buffer);

    close(newsockfd);
    close(sockfd);

    return 0;
}