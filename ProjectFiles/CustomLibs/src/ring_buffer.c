#include <stdlib.h>

#include "ring_buffer.h"
#include "usb.h"

extern uint8_t ringBufferRx[];
extern uint16_t ringBufferWritePos;
extern uint16_t ringBufferReadPos;

/**
 * @brief Calculates the number of available bytes in the ring buffer.
 * 
 * This function determines the number of bytes currently available 
 * for reading in the ring buffer based on the difference between 
 * the head (write) and tail (read) positions.
 * 
 * @note The function handles both cases:
 *       - When the head is ahead of the tail (linear difference).
 *       - When the head has wrapped around to the beginning of the buffer.
 * 
 * @retval The number of bytes available for reading from the ring buffer.
 */
uint16_t GetRingBufferBytesAvailable()
{
    int diff = (ringBufferWritePos - ringBufferReadPos);  // Difference between write and read positions
    if (diff >= 0)                                          // If the write position is ahead of the read position
        return (diff);                                      // The difference is the number of available bytes
    else                                                    // If the write position has wrapped around
        return (HL_RX_BUFFER_SIZE - (-diff));           // Calculate available bytes excluding the wrapped segment
}

/**
 * @brief Copies data from the provided buffer to the ring buffer.
 * 
 * This function writes the specified number of bytes from the input buffer `Buf`
 * into the ring buffer for further processing.
 * 
 * @param Buf Pointer to the buffer containing the data to be copied.
 * @param Len Number of bytes to copy from `Buf` to the ring buffer.
 * 
 * @retval USB_CDC_RX_BUFFER_OK       Data successfully copied.
 * @retval USB_CDC_RX_BUFFER_NO_DATA  Not enough space available in the ring buffer.
 */
uint8_t CopyBufferToRingBuffer(uint8_t *Buf, uint16_t Len)
{
	uint16_t bytesAvailable = GetRingBufferBytesAvailable();

	if (bytesAvailable < Len)
		return USB_CDC_RX_BUFFER_NO_DATA;

	for (uint8_t i = 0; i < Len; i++)
	{
		Buf[i] = ringBufferRx[ringBufferReadPos];
		ringBufferReadPos = (uint16_t)((uint16_t)(ringBufferReadPos + 1) % HL_RX_BUFFER_SIZE);
	}

	return USB_CDC_RX_BUFFER_OK;
}

/**
 * @brief Copies data from the ring buffer to the provided buffer.
 * 
 * This function reads the specified number of bytes from the ring buffer
 * and writes them to the provided buffer `Buf`.
 * 
 * @param Buf Pointer to the buffer where data will be copied.
 * @param Len Number of bytes to copy from the ring buffer to `Buf`.
 * 
 * @retval USB_CDC_RX_BUFFER_OK       Data successfully copied.
 * @retval USB_CDC_RX_BUFFER_NO_DATA  Not enough data available in the ring buffer.
 */
uint8_t CopyRingBufferToBuffer(uint8_t *Buf, uint16_t Len)
{
	uint16_t bytesAvailable = GetRingBufferBytesAvailable();				// Зачем, что мы тогда передаем в качестве Len ??????

	if (bytesAvailable < Len)
		return USB_CDC_RX_BUFFER_NO_DATA;		// NO_DATA будет в случае, когда bytesAvailable == HL_RX_BUFFER_SIZE	??????????

	for (uint16_t i = 0; i < Len; i++)
	{
		Buf[ringBufferReadPos] = ringBufferRx[ringBufferReadPos];	// copy a character from the ring buffer
		ringBufferReadPos = 
			(uint16_t)((uint16_t)(ringBufferReadPos + 1) 		// move the cursor to 1
			% HL_RX_BUFFER_SIZE);							// transfer to the beginning, in case of going abroad
	}

	return USB_CDC_RX_BUFFER_OK;
}

/**
 * @brief Copies data from a ring buffer, excluding the bounds defined by `start` and `end`.
 * @param buffer      Pointer to the start of the ring buffer.   НЕТ!!!!
 * @param bufferSize  Size of the ring buffer in bytes.
 * @param start       Pointer to the starting position (excluded from the copy).
 * @param end         Pointer to the ending position (excluded from the copy).
 * @param dest        Destination buffer where the data will be copied.
 * @retval None
 */
void copyRingBufferExcludingBounds(const char *buffer, int bufferSize, const char *start, const char *end, char *dest) {
    const char *current = start + 1;  // Start copying from the position after `start`.

    while (current != end) {
        *dest++ = *current;  // Copy the current character to the destination buffer.

        current++;  // Move to the next position.
        if (current >= buffer + bufferSize) {
            current = buffer;  // Wrap around to the beginning of the buffer if necessary.
        }
    }

    *dest = '\0';  // Null-terminate the destination string.
}

/**
 * @brief Searches for a character in a ring buffer starting from a specified position.
 * @param buffer      Pointer to the start of the buffer.
 * @param bufferSize  Size of the buffer in bytes.
 * @param start       Pointer to the starting position within the buffer.
 * @param c           Character to search for.
 * @retval Pointer to the first occurrence of the character, or NULL if not found.
 */
char* strchr_from_ring_buffer(const char *buffer, size_t bufferSize, const char *start, char c) {
    const char *current = start;

    // Iterate through the buffer, treating it as ring
    for (size_t i = 0; i < bufferSize; i++) {
        if (*current == c) {
            return (char *)current;  // Return the pointer if the character is found
        }

        // Move to the next position, wrapping around if necessary
        current++;
        if (current >= buffer + bufferSize) {
            current = buffer;  // Wrap back to the beginning of the buffer
        }
    }

    return NULL;  // Return NULL if the character is not found
}
