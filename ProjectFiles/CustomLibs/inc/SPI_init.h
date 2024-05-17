/**
  ******************************************************************************
  * @file    SPI_init.c
  * @author  ICV
  * @version V1.0.0
  * @date    08/05/2024
  * @brief   SPI initialization Header File.
  * ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SPI_init
#define SPI_init

// SPI
#define Port_SPI                MDR_PORTF
#define Pin_SPI_MOSI            PORT_Pin_0
#define Pin_SPI_CLK             PORT_Pin_1
#define Pin_SPI_MISO            PORT_Pin_3
// Display  
#define Port_DC_Reset_Display   MDR_PORTB
#define Pin_DC_Display          PORT_Pin_6
#define Pin_Reset_Display       PORT_Pin_7
  
#define Port_SPI_CS_Display     MDR_PORTF
#define Pin_SPI_CS_Display      PORT_Pin_2
// Touch  
#define Port_SPI_CS_Touch       MDR_PORTB
#define Pin_SPI_CS_Touch        PORT_Pin_10
#define Port_IRQ_Touch          MDR_PORTB
#define Pin_IRQ_Touch           PORT_Pin_9

void Setup_SPI(void);

#endif /* DAC_init */