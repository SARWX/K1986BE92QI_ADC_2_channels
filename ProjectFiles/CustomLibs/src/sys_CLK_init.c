#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
#include <stdint.h>
#include "sys_CLK_init.h"
#include "defines.h"

// задержка на count тактов 
void delay_tick(uint32_t count)	// Ждать count тактов процессора
{	
	while (count--) 
	{							// декремент счетчика	
		__NOP();				// Не делать ничего
	}
}

void Setup_CPU_Clock(void) 
{
	/* Подлючаем HSE */
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);

	if (RST_CLK_HSEstatus() != SUCCESS)
	{
		PORT_InitTypeDef GPIOInitStruct;
		RST_CLK_PCLKcmd (RST_CLK_PCLK_PORTC, ENABLE);
		GPIOInitStruct.PORT_Pin = PORT_Pin_2;
		GPIOInitStruct.PORT_OE = PORT_OE_OUT;
		GPIOInitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
		GPIOInitStruct.PORT_MODE = PORT_MODE_DIGITAL;
   		PORT_Init(MDR_PORTC, &GPIOInitStruct);
		
		// если не установилась частота, то будет светодиод мигать
		while (1) 
		{
			PORT_SetBits(MDR_PORTC, PORT_Pin_2); 	// Включить светодиод
			delay_tick(10000);
			PORT_ResetBits(MDR_PORTC, PORT_Pin_2); 	// Выключить светодиод
			delay_tick(10000);
		}
	}

	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul8); //  16 MHz
	
	RST_CLK_CPU_PLLcmd(ENABLE);

	if (RST_CLK_CPU_PLLstatus() != SUCCESS)
	{
		PORT_InitTypeDef GPIOInitStruct;
		RST_CLK_PCLKcmd (RST_CLK_PCLK_PORTC, ENABLE);
		GPIOInitStruct.PORT_Pin = PORT_Pin_2;
		GPIOInitStruct.PORT_OE = PORT_OE_OUT;
		GPIOInitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
		GPIOInitStruct.PORT_MODE = PORT_MODE_DIGITAL;
   		PORT_Init(MDR_PORTC, &GPIOInitStruct);
		/* Trap */ // та же ситуация, что и в предыдущем случае
		while (1) 
		{
			PORT_SetBits(MDR_PORTC, PORT_Pin_2); 	// Включить светодиод
			delay_tick(10000);
			PORT_ResetBits(MDR_PORTC, PORT_Pin_2); 	// Выключить светодиод
			delay_tick(10000);
		}
	}

	RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);
	RST_CLK_CPU_PLLuse(ENABLE);
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
}
