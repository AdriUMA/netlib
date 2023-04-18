#!/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
NETLIB_DIR=$SCRIPT_DIR/../netlib

SOURCE_FOLDER=$1
INPUT_FILE=$2
OUTPUT_FILE=$3

if [ ! -d $SCRIPT_DIR/bin ]; then
    mkdir $SCRIPT_DIR/bin
fi

gcc -g $SOURCE_FOLDER/$INPUT_FILE $NETLIB_DIR/linkedlist/addresslist.c $NETLIB_DIR/udp/sender.c $NETLIB_DIR/udp/listener.c $NETLIB_DIR/udp/linkedlist/senderlist.c -o $SCRIPT_DIR/bin/$OUTPUT_FILE
$SCRIPT_DIR/bin/$OUTPUT_FILE