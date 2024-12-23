#ifndef USB_RING_BUF_H
#define USB_RING_BUF_H

#include <stdint.h>

uint16_t GetRingBufferBytesAvailable();

uint8_t CopyRingBufferToBuffer(uint8_t *Buf, uint16_t Len);

uint8_t CopyBufferToRingBuffer(uint8_t *Buf, uint16_t Len);

void copyRingBufferExcludingBounds(const char *buffer, int bufferSize, const char *start, const char *end, char *dest);

char* strchr_from_ring_buffer(const char *buffer, size_t bufferSize, const char *start, char c);



#endif // USB_RING_BUF_H