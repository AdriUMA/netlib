#include "../netlib/netlib.h"
#include <string.h>

int main () {
    TCPSender sender = openTCPSender("127.0.0.1", 55155, 1024);

    sendTCP(sender, (void *)"Hola testeo", strlen("Hola testeo")+1);

    return 0;
}