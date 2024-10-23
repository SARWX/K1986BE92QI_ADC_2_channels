/**
  ******************************************************************************
  * @file    compress.c
  * @author  ICV
  * @version V1.1.0
  * @date    23/10/2024
  * @brief   This file contains compress / convert fuctions.
  * ***************************************************************************
  */

#include <stdint.h>

/**
 * @brief Function to leave only the high 8 bits
 * in the array of 2 byte data, in order to compress the array by 2 times 
 * @param size - set in the number of 16 bit elements
 * @retval None
*/
void convert_to_8_bit(uint8_t *arr, int size)
{
	// static uint8_t new_arr[NUM_OF_MES];
	for(int i = 0; i < (size*2); i++)
	{
		uint8_t high_byte = 0;
		high_byte |= ((arr[i*2] & 0xF0) >> 4);
		high_byte |= ((arr[((i*2)+1)] & 0x0F) << 4);
		arr[i] = high_byte;
	}
}

/**
 * @brief Function-Compressor 
 * compresses 12 bit measurements from 2 bytes into 12 bits
 * @param size - set in number of 16 bit elements
 * @retval None
*/
void convert_to_12_bit(uint8_t *arr, int size) 
{
    int i = 3, j = 4; 
    while (j < size*2)
    {
        if (((j+1)%4) == 0)
        {
            j++;
            continue;
        }
        // Возможны 2 случая:
		if ((i%2) == 0)
		{
			// Четный полубайт (младший полубайт)	0 - 1, 2 - 3, 4 - 5 ...
			arr[i/2] &= 0xF0;	// затерли младший полубайт
			if((j%2) == 0)
			{
			    // j тоже младший
			    arr[i/2] |= (arr[j/2] & 0x0F);
			}
			else
			{
			    // j старший
			    arr[i/2] |= ((arr[j/2] >> 4) & 0x0F);
			}
		}
		else
		{
			// Нечетный полубайт (старший полубайт)
			arr[i/2] &= 0x0F;       // затерли старший полубайт
			if((j%2) == 0)
			{
			    // j младший
			    arr[i/2] |= ((arr[j/2] << 4) & 0xF0);
			}
			else
			{
			    // j тоже старший
			    arr[i/2] |= (arr[j/2] & 0xF0);
			}
		}
		j++;
		i++;
    }
}

/**
 * @brief Function-Converter 
 * alligns 8 bit array to 16  bit array format
 * @param size - number of elements
 * @retval None
*/
void convert_8_to_16_bit(uint8_t *arr, int size)
{
	uint16_t *converted_arr = (uint16_t *)arr;
	for(size; size >= 0; --size)
	{
		converted_arr[size] = (uint16_t)arr[size];
	}
}

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE compress.c */
