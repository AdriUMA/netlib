#!/usr/bin/env bash

# Absolute routes
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
NETLIB_DIR=$SCRIPT_DIR/../netlib

# Parameters
SOURCE_FOLDER=$1
INPUT_FILE=$2
OUTPUT_FILE=$3

# Netlib compilation
NETLIB_GENERAL="$NETLIB_DIR/linkedlist/addresslist.c"
NETLIB_UDP="$NETLIB_DIR/udp/sender.c $NETLIB_DIR/udp/listener.c $NETLIB_DIR/udp/linkedlist/senderlist.c"
NETLIB_TCP="$NETLIB_DIR/tcp/sender.c $NETLIB_DIR/tcp/listener.c"
NETLIB="$NETLIB_GENERAL $NETLIB_UDP $NETLIB_TCP"

if [ ! -d $SCRIPT_DIR/bin ]; then
    mkdir $SCRIPT_DIR/bin
fi

gcc -g $SOURCE_FOLDER/$INPUT_FILE $NETLIB -o $SCRIPT_DIR/bin/$OUTPUT_FILE
$SCRIPT_DIR/bin/$OUTPUT_FILE