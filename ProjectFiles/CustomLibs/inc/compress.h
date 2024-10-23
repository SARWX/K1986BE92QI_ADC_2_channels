/**
  ******************************************************************************
  * @file    compress.h
  * @author  ICV
  * @version V1.1.0
  * @date    19/10/2024
  * @brief   contains Header File.
  * ******************************************************************************
  */

#ifndef _COMPRESS_H_
#define _COMPRESS_H_

#include <stdint.h>

/** @defgroup __Specific_compress Specific compress functions
  * @{
  */

void convert_to_8_bit(uint8_t *arr, int size);
void convert_to_12_bit(uint8_t *arr, int size);
void convert_8_to_16_bit(uint8_t *arr, int size);

/** @} */ /* End of group __Specific_compress */

#endif /* compress */

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE compress.h */