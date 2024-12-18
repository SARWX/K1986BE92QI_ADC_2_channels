/**
  ******************************************************************************
  * @file    sys_CLK_init.c
  * @author  ICV
  * @version V1.1.0
  * @date    19/10/2024
  * @brief   This file contains initialization of System Core Clock
  * ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
#include <stdint.h>
#include "sys_CLK_init.h"
#include "defines.h"
#include "delay.h"

/**
  * @brief  Switch to the HSE, configure and enable PLL 
  * @param  None
  * @retval None
  */
void Setup_CPU_Clock(void) 
{
	// Подлючаем HSE 
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);
	if (RST_CLK_HSEstatus() != SUCCESS)
	{
		// если не установилась частота, то будет светодиод мигать
		PORT_InitTypeDef GPIOInitStruct;
		RST_CLK_PCLKcmd (RST_CLK_PCLK_PORTC, ENABLE);
		GPIOInitStruct.PORT_Pin = PORT_Pin_2;
		GPIOInitStruct.PORT_OE = PORT_OE_OUT;
		GPIOInitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
		GPIOInitStruct.PORT_MODE = PORT_MODE_DIGITAL;
   		PORT_Init(MDR_PORTC, &GPIOInitStruct);
	 	while (1)
		{
			PORT_SetBits(MDR_PORTC, PORT_Pin_2); 	// Включить светодиод
			delay_ms(200);
			PORT_ResetBits(MDR_PORTC, PORT_Pin_2); 	// Выключить светодиод
			delay_ms(200);
		}
	}
	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul8);
	RST_CLK_CPU_PLLcmd(ENABLE);
	RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);
	RST_CLK_CPU_PLLuse(ENABLE);
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
}

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE sys_CLK_init.c */