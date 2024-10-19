/**
  ******************************************************************************
  * @file    delay.c
  * @author  ICV
  * @version V1.1.0
  * @date    19/10/2024
  * @brief   This file contains declaration of delay functions
  * ******************************************************************************
  */

#include <stdint.h>
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DELAY_H_
#define _DELAY_H_

void delay_tick(uint32_t count);
void delay_ms(uint32_t delay);
void delay_us(uint32_t delay);


#endif

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE delay.h */