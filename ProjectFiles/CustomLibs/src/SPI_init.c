#include "MDR32F9Qx_ssp.h"
#include "MDR32F9Qx_port.h"
#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"
#include "delay.h"

SSP_InitTypeDef SSP1_struct;	

void Setup_SPI(void)
{
	PORT_InitTypeDef Port_sruct;

	// Подключаем тактирование к блоку SPI, портам B и F 
    RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_SSP1), ENABLE);
    RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTF), ENABLE);

	// POT B - инициализация RESET и DC
	PORT_StructInit(&Port_sruct);
	Port_sruct.PORT_Pin       = (PORT_Pin_6 | PORT_Pin_7); // PB6 = DC, PB7 = RESET
	Port_sruct.PORT_OE        = PORT_OE_OUT;
	Port_sruct.PORT_SPEED     = PORT_SPEED_MAXFAST;
	Port_sruct.PORT_MODE      = PORT_MODE_DIGITAL;         // ???
	PORT_Init(MDR_PORTB, &Port_sruct);

	// TEST
//	for (int i = 0; i < 10; i++) {
//			MDR_PORTB->RXTX = (MDR_PORTB->RXTX ^ PORT_Pin_7);
//			delay_ms(100);
//		}
	// TEST

	// PORT F - инициализация CS
	Port_sruct.PORT_Pin       = PORT_Pin_2;		// PF2 = CS дисплея
	PORT_Init(MDR_PORTF, &Port_sruct);
	MDR_PORTF->RXTX |= PORT_Pin_2;				// cs дисплея = 1
	Port_sruct.PORT_Pin       = PORT_Pin_10;	// PB10 = CS тача
	PORT_Init(MDR_PORTB, &Port_sruct);
	MDR_PORTB->RXTX |= PORT_Pin_10;				// cs тача = 1
	
	// PORT F - инициализация MOSI, SCK
	Port_sruct.PORT_Pin       = (PORT_Pin_0 | PORT_Pin_1);
	Port_sruct.PORT_FUNC	   = PORT_FUNC_ALTER;
	PORT_Init(MDR_PORTF, &Port_sruct);
	// MISO	Port_sruct->PORT_Pin       = (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2);                // PF2 = CS
	Port_sruct.PORT_Pin       = (PORT_Pin_3);                // MISO
	Port_sruct.PORT_OE        = PORT_OE_IN;
	PORT_Init(MDR_PORTF, &Port_sruct);
	
	// Настройка для Touch
	Port_sruct.PORT_FUNC	   = PORT_FUNC_PORT;
	Port_sruct.PORT_MODE      = PORT_MODE_DIGITAL;
	Port_sruct.PORT_Pin       = (PORT_Pin_9);               // IRQn
	Port_sruct.PORT_OE        = PORT_OE_IN;
	PORT_Init(MDR_PORTB, &Port_sruct);
	

	// инициализация SPI
	SSP_BRGInit(MDR_SSP1, SSP_HCLKdiv1);		// Подключить SSP1 peripheral clock	
	SSP_StructInit(&SSP1_struct);
	SSP_Init(MDR_SSP1, &SSP1_struct);
	SSP_Cmd(MDR_SSP1, ENABLE); 

	// uint16_t data = 0;
	// SSP_SendData(MDR_SSP1, data);
	

};