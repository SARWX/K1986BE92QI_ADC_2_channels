
/**
  ******************************************************************************
  * @file    pins.h
  * @author  ICV
  * @version V1.1.0
  * @date    09/11/2024
  * @brief   This file contains pin defines (you can change them or add yours)
  * ******************************************************************************
  */

 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef Pins
#define Pins

#define MIMINI

#define LE0_SPI0_Pin PORT_Pin_2 //pin 4
#define LE0_SPI0_Port MDR_PORTF

#ifndef MIMINI
	#define LE1_SPI0_Pin PORT_Pin_2 //pin 22
	#define LE1_SPI0_Port MDR_PORTE
#else
	#define LE1_SPI0_Pin PORT_Pin_0 //pin 42
	#define LE1_SPI0_Port MDR_PORTC
#endif


#define SPI_RESET_Pin PORT_Pin_1
#define SPI_RESET_Port MDR_PORTC

#define LED_Pin PORT_Pin_2
#define LED_Port MDR_PORTC
#define LED_CLK RST_CLK_PCLK_PORTC

/* Configure SSP1 pins: FSS-PF2, CLK-PF1, RXD-PF3, TXD-PF0 */
#define SPI_TX_Pin PORT_Pin_0
#define SPI_CLK_Pin PORT_Pin_1
#define SPI_RX_Pin PORT_Pin_3
#define SPI_Port MDR_PORTF

//////////// PCR ADI defines ////////////
// SPI
#define Port_SPI                MDR_PORTF
#define Pin_SPI_MOSI            PORT_Pin_0
#define Pin_SPI_CLK             PORT_Pin_1
#define Pin_SPI_MISO            PORT_Pin_3
// Display  
#define Port_DC_Reset_Display   MDR_PORTB
#define Pin_DC_Display          PORT_Pin_6
#define Pin_Reset_Display       PORT_Pin_7
#define Port_SPI_CS_Display     MDR_PORTD       // Был F, пришлось изменить на D, потому что 
                                                // не работает с нынешней конфигурацией JTAG
#define Pin_SPI_CS_Display      PORT_Pin_2
// Touch  
#define Port_SPI_CS_Touch       MDR_PORTB
#define Pin_SPI_CS_Touch        PORT_Pin_10
#define Port_IRQ_Touch          MDR_PORTB
#define Pin_IRQ_Touch           PORT_Pin_9

#endif /* Pins */

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE pins.h */
