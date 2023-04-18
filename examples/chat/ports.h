#ifndef PORTS_H
#define PORTS_H

// Ports Version
#define VERSION printf("\nRunning ports version 0.1\n")

// Netlib
#include "../../netlib/netlib.h"

// Ports
#define SERVER_PORT 55154
#define CLIENT_PORT 55155

// Buffer and connection
// At least 64 bytes
#define SERVER_BUFFER 1024
#define NOTICE_CONNECT "::::::::::CONNECT::::::::::\0"
#define NOTICE_DISCONNECT "::::::::::DISCONNECT::::::::::\0"

#endif