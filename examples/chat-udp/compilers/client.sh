#!/usr/bin/env bash

# Compiler parameters
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )/..
SOURCE_FILENAME=client.c
OUTPUT_FILENAME=client.bin

# Main compiler execution permision
chmod u+x $SCRIPT_DIR/../compiler.sh 

# Call compiler
$SCRIPT_DIR/../compiler.sh $SCRIPT_DIR $SOURCE_FILENAME $OUTPUT_FILENAME