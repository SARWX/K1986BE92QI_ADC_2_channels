#include "defines.h"
#include "MDR32F9Qx_rst_clk.h"

void delay_tick(uint32_t count)	// Ждать count тактов процессора
{	
	while (count--) 
	{									// декремент счетчика	
		__NOP();				// Не делать ничего
	}
}

void delay_ms(uint32_t delay)
{
	delay_tick(delay * (HSE_FREQ / (1000 )));
}

void delay_us(uint32_t delay)
{
	delay_tick(delay * (HSE_FREQ / (1000000)));
}