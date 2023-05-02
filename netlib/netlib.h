#ifndef NETLIB_H
#define NETLIB_H

#define NETLIB_VERSION SNAPSHOT

// Generic
#include "linkedlist/addresslist.h"

// UDP-oriented
#include "udp/listener.h"
#include "udp/sender.h"
#include "udp/linkedlist/senderlist.h"

// TCP-oriented
#include "tcp/listener.h"
#include "tcp/sender.h"

#endif