#include "../netlib/netlib.h"
#include <stdio.h>
#include <string.h>

int main () {
    TCPListener listener = openTCPListener(55155, 1024);

    listenTCP(listener);

    return 0;
}