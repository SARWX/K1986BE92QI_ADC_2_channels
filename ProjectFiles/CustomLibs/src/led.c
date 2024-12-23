#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"

#include "pins.h"
#include "delay.h"

void led_init()
{
  PORT_InitTypeDef GPIOInitStruct;
	RST_CLK_PCLKcmd (LED_CLK, ENABLE);
	GPIOInitStruct.PORT_Pin = LED_Pin;
	GPIOInitStruct.PORT_OE = PORT_OE_OUT;
	GPIOInitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
	GPIOInitStruct.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_Init(LED_Port, &GPIOInitStruct);
}

/**
  * @brief : simple blink function
  * it will long 2 seconds
  * @param  None.
  * @retval None.
  */
void LEDBlink_ms(uint32_t miliseconds) {
	PORT_SetBits(LED_Port, LED_Pin);
	delay_ms(miliseconds);
	PORT_ResetBits(LED_Port, LED_Pin);
	delay_ms(miliseconds);
}

void LEDBlink_ticks(uint32_t ticks) {
	PORT_SetBits(LED_Port, LED_Pin);
	delay_tick(ticks);
	PORT_ResetBits(LED_Port, LED_Pin);
	delay_tick(ticks);
}
