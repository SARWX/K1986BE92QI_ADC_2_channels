#include <stdint.h>

#ifndef _COMPRESS_H_
#define _COMPRESS_H_

void convert_to_8_bit(uint8_t *arr, int size);
void convert_to_12_bit(uint8_t *arr, int size);
void convert_8_to_16_bit(uint8_t *arr, int size);

#endif