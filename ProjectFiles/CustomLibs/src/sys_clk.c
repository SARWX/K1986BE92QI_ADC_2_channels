/**
  ******************************************************************************
  * @file    sys_clk.c
  * @author  ICV
  * @version V1.2.0
  * @date    05/12/2024
  * @brief   This file contains initialization of System Core Clock
  * ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
#include <stdint.h>
#include "sys_clk.h"
#include "defines.h"
#include "delay.h"
#include "pins.h"


/**
 * @brief Structure to define PLL configuration.
 */
typedef struct {
    RST_CLK_CPU_PLL_Source source;        /*!< Source for the PLL */
    RST_CLK_CPU_PLL_Multiplier multiplier;/*!< Multiplier for the PLL */
} PLL_config_struct;

/**
 * @brief Array of valid PLL configurations, indexed by PLL_configuration_t.
 */
static PLL_config_struct pll_configs[NOT_VALID_CONFIG];

/**
 * @brief Initialization of PLL configuration array.
 */
void init_pll_configs(void)
{
    pll_configs[FAST_CONFIG] = (PLL_config_struct){
        .source = RST_CLK_CPU_PLLsrcHSEdiv1,	// divide by 1, 
        .multiplier = RST_CLK_CPU_PLLmul8		// multiply by 8 to get 128 MHz
    };

    pll_configs[SLOW_CONFIG] = (PLL_config_struct){
        .source = RST_CLK_CPU_PLLsrcHSEdiv2,	// divide by 2, 
        .multiplier = RST_CLK_CPU_PLLmul4		// multiply by 4 to get 32 MHz
    };

    // Add more configurations here if necessary
}

/**
  * @brief  Trap for error in setting clock up
  * 		led will blink 
  * @param  None
  * @retval None
  */
void Clock_failed()
{
	// если не установилась частота, то будет светодиод мигать
	PORT_InitTypeDef GPIOInitStruct;
	RST_CLK_PCLKcmd (RST_CLK_PCLK_PORTC, ENABLE);
	GPIOInitStruct.PORT_Pin = LED_Pin;
	GPIOInitStruct.PORT_OE = PORT_OE_OUT;
	GPIOInitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
	GPIOInitStruct.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_Init(LED_Port, &GPIOInitStruct);
	while (1)
	{
		PORT_SetBits(LED_Port, LED_Pin); 	// Включить светодиод
		delay_tick(1e5);
		PORT_ResetBits(LED_Port, LED_Pin); 	// Выключить светодиод
		delay_tick(1e5);
	}
}

/**
  * @brief  Switch to the HSE, configure and enable PLL 
  * @param  None
  * @retval None
  */
void Setup_CPU_Clock(PLL_configuration_t pll_config) 
{
	// Init array of possible configs
	init_pll_configs();
	PLL_config_struct req_config = pll_configs[pll_config];

	// Enable HSE (High-Speed External oscillator)
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);

	// Check
	if (RST_CLK_HSEstatus() != SUCCESS)
	{
		Clock_failed();
	}

	// Configure PLL
	RST_CLK_CPU_PLLconfig(req_config.source, req_config.multiplier);
	
	// Enable CPU PLL
    RST_CLK_CPU_PLLcmd(ENABLE);

	// Check
	if (RST_CLK_CPU_PLLstatus() != SUCCESS) 
	{        
		Clock_failed();
    }

    // Set CPU clock prescaler to 1 (no division)
    RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);

    // Enable CPU PLL as the clock source
    RST_CLK_CPU_PLLuse(ENABLE);

    // Select CPU clock C3 (PLL output as the CPU clock source)
    RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
}

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE sys_clk.c */