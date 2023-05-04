#ifndef NETLIB_BUFFER
#define NETLIB_BUFFER

typedef struct str_buffer {
    unsigned size;          // Buffer size
    void* data;             // Data (bytes)
    unsigned dataSize;      // Data length (size>=dataSize)
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
 *  @param buffer Open buffer to be filled
 *  @param bytes
 *  @param length
 */
void bytesIntoBuffer(Buffer buffer, void* bytes, unsigned length);

/** @brief Prepare a buffer with string fill 
 *  @param buffer Open buffer to be filled
 *  @param string
 */
void stringIntoBuffer(Buffer buffer, char* string);

#endif