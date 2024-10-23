/**
  ******************************************************************************
  * @file    delay.c
  * @author  ICV
  * @version V1.1.0
  * @date    19/10/2024
  * @brief   This file contains declaration of delay functions
  * ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DELAY_H_
#define _DELAY_H_

#include <stdint.h>

/** @defgroup __Specific_delay Specific delay functions
  * @{
  */

void delay_tick(uint32_t count);
void delay_ms(uint32_t delay);
void delay_us(uint32_t delay);

/** @} */ /* End of group __Specific_delay */

#endif

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE delay.h */