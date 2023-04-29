#include "../netlib/netlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    TCPListener listener = openTCPListener(55155, 1024);

    if (listener == NULL) {
        printf("ERROR");
        exit(EXIT_FAILURE);
    }

    listenTCP(listener);

    return 0;
}