#include "buffer.h"
#include <stdlib.h>
#include <string.h>

Buffer openBuffer(unsigned size){
    Buffer buffer = malloc(sizeof(struct str_buffer));
    buffer->data = malloc(size);
    buffer->dataSize = 0;
    buffer->size = size;

    return buffer;
}

void closeBuffer(Buffer buffer) {
    free(buffer->data);
    free(buffer);
}

void bytesIntoBuffer(Buffer buffer, void* bytes, unsigned length){
    char* ptrData = buffer->data;
    char* ptrBytes = bytes;

    for (int i = 0; i < length; i++)
        *(ptrData+1) = *(ptrBytes+1);    
}


void stringIntoBuffer(Buffer buffer, char* string){
    strcpy(buffer->data, string);
    buffer->dataSize = strlen(string)+1;
}