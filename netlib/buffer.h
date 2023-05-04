#ifndef NETLIB_BUFFER
#define NETLIB_BUFFER

typedef struct str_buffer {
    unsigned size;
    void* data;
    unsigned dataSize;
}* Buffer;

/** @brief Open buffer allocating memory
 *  @param size Buffer data size in bytes
 *  @return Pointer to the buffer
 */
Buffer openBuffer(unsigned size);

/** @brief Close buffer (free memory)
 *  @param buffer Will be pointing to NULL
 */
void closeBuffer(Buffer buffer);

/** @brief Prepare a buffer with string fill 
 *  @param string
 *  @param buffer Open buffer to be filled
 */
void stringToBuffer(Buffer buffer, char* string);

#endif