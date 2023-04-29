#include "../netlib/netlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    TCPSender sender;
    
    sender = openTCPSender("127.0.0.1", 55155, 1024);

    if (sender == NULL){
        printf("ERROR");
        exit(EXIT_FAILURE);
    }    

    sendTCP(sender, (void *)"Hola testeo", strlen("Hola testeo")+1);

    return 0;
}