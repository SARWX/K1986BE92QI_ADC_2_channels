/**
  ******************************************************************************
  * @file    SPI_init.c
  * @author  ICV
  * @version V1.0.0
  * @date    17/05/2024
  * @brief   This file contains initialization of SPI (SSP1)
  * 		 also, initialize pins, that we need to use
  * 		 display and touch screen
  * ******************************************************************************
  */

#include "MDR32F9Qx_ssp.h"
#include "MDR32F9Qx_port.h"
#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"
#include "delay.h"
#include "SPI_init.h"

SSP_InitTypeDef SSP1_struct;	

/**
  * @brief  Configure SPI for: \n 
  * 1) Display ili9341 (plus RESET, DC, CS) \n
  * 2) Touch XPT2046 (plus IRQ, CS) 
  * @param  None
  * @retval None
  */
void Setup_SPI(void)
{
	// Подключаем тактирование к блоку SPI, портам B и F 
    RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_SSP1), ENABLE);
    RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTF), ENABLE);

	// инициализация RESET и DC
	PORT_InitTypeDef Port_sruct;
	PORT_StructInit(&Port_sruct);
	Port_sruct.PORT_Pin		= (Pin_DC_Display | Pin_Reset_Display);
	Port_sruct.PORT_OE		= PORT_OE_OUT;
	Port_sruct.PORT_SPEED	= PORT_SPEED_MAXFAST;
	Port_sruct.PORT_MODE	= PORT_MODE_DIGITAL;
	PORT_Init(Port_DC_Reset_Display, &Port_sruct);

	// инициализация CS
	Port_sruct.PORT_Pin     = Pin_SPI_CS_Display;
	PORT_Init(Port_SPI_CS_Display, &Port_sruct);
	Port_SPI_CS_Display->RXTX |= Pin_SPI_CS_Display;
	Port_sruct.PORT_Pin     = Pin_SPI_CS_Touch;
	PORT_Init(Port_SPI_CS_Touch, &Port_sruct);
	Port_SPI_CS_Touch->RXTX |= Pin_SPI_CS_Touch;

	// инициализация MOSI, SCK, MISO
	Port_sruct.PORT_Pin     = (Pin_SPI_MOSI | Pin_SPI_CLK);
	Port_sruct.PORT_FUNC	= PORT_FUNC_ALTER;
	PORT_Init(Port_SPI, &Port_sruct);
	Port_sruct.PORT_Pin		= (Pin_SPI_MISO);
	Port_sruct.PORT_OE      = PORT_OE_IN;
	PORT_Init(Port_SPI, &Port_sruct);
	
	// Настройка для Touch
	Port_sruct.PORT_FUNC	= PORT_FUNC_PORT;
	Port_sruct.PORT_Pin		= (Pin_IRQ_Touch);
	Port_sruct.PORT_OE		= PORT_OE_IN;
	PORT_Init(Port_IRQ_Touch, &Port_sruct);

	// инициализация SPI
	SSP_BRGInit(MDR_SSP1, SSP_HCLKdiv1);	// Подключить SSP1 peripheral clock	
	SSP_StructInit(&SSP1_struct);
	SSP_Init(MDR_SSP1, &SSP1_struct);
	SSP_Cmd(MDR_SSP1, ENABLE); 
};

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE SPI_init.c */
