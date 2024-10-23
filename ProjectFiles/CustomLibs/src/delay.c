/**
  ******************************************************************************
  * @file    delay.c
  * @author  ICV
  * @version V1.1.0
  * @date    19/10/2024
  * @brief   This file contains realisation of delay functions
  * ******************************************************************************
  */

#include "defines.h"
#include "MDR32F9Qx_rst_clk.h"

/**
 * @brief Performs a simple delay loop.
 * 
 * This function uses a decrementing loop to create a delay by performing no operations.
 * The length of the delay depends on the input counter value.
 * 
 * @param count The number of iterations for the delay loop.
 */
void delay_tick(uint32_t count)
{	
    while (count--) 
    {	
        __NOP();    /**< No Operation: Do nothing, used to create delay. */
    }
}

/**
 * @brief Delays execution for a specified number of milliseconds.
 * 
 * This function delays the program for a given number of milliseconds, 
 * based on the system clock frequency. It uses a simple loop to achieve the delay.
 * 
 * @param delay Number of milliseconds to delay.
 */
void delay_ms(uint32_t delay)
{
    delay_tick(delay * (HSE_FREQ / 1000)); /**< Converts delay to tick counts for milliseconds. */
}

/**
 * @brief Delays execution for a specified number of microseconds.
 * 
 * This function delays the program for a given number of microseconds, 
 * based on the system clock frequency. It uses a simple loop to achieve the delay.
 * 
 * @param delay Number of microseconds to delay.
 */
void delay_us(uint32_t delay)
{
    delay_tick(delay * (HSE_FREQ / 1000000)); /**< Converts delay to tick counts for microseconds. */
}


/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE delay.c */