/**
  ******************************************************************************
  * @file    spi.c
  * @author  ICV
  * @version V1.0.0
  * @date    17/05/2024
  * @brief   This file contains initialization of SPI (SSP1)
  * 		 also, initialize pins, that we need to use
  * 		 display and touch screen
  * ******************************************************************************
  */

#include "spi.h"
#include "pins.h"
#include "gpio.h"
#include "usb.h"

#include <stdio.h>

#define BufferSize 16

uint16_t SPI_TX_Buf[BufferSize];	/* buffer for data sent over SPI */
uint16_t SPI_RX_Buf[BufferSize];	/* buffer for data received over SPI */


/**
 * @brief Array containing all SPI modes with their respective configurations.
 */
const struct SPImode SPIModes[4] = { //All SPI modes
		{0, SSP_SPO_Low,	SSP_SPH_1Edge},
		{1, SSP_SPO_Low,	SSP_SPH_2Edge},
		{2, SSP_SPO_High,	SSP_SPH_1Edge},
		{3, SSP_SPO_High,	SSP_SPH_2Edge}
};

/**
 * @brief Structure for storing the standard configuration of the SSP (Serial Peripheral Interface).
 * 
 * This structure is used to initialize the SSP module with parameters, which provide the basic configuration for communication.
 * 
 * @note This configuration doesn't specify specific communication parameters, 
 * 		 so after copying the config, you may need to modify certain values as per the application requirements.
 */
const SSP_InitTypeDef SSP_DefaultConfig =
{
    .SSP_SCR                    = 0x0F,
    .SSP_CPSDVSR                = 2,
    .SSP_Mode                   = SSP_ModeMaster,
    .SSP_WordLength             = SSP_WordLength8b,
    .SSP_SPH                    = SSP_SPH_1Edge,
    .SSP_SPO                    = SSP_SPO_Low,
    .SSP_FRF                    = SSP_FRF_SPI_Motorola,
    .SSP_HardwareFlowControl    = SSP_HardwareFlowControl_None,
};


/**
 * @brief Sends a specified number of bytes over SPI without receiving data.
 * 
 * This function transmits data from the `SPI_TX_Buf` buffer over the SPI bus. It ensures that the 
 * SPI transmit FIFO buffer is empty before sending each byte and waits until the SPI is no longer 
 * busy after completing the transmission.
 * 
 * @param bytes : The number of bytes to send from the `SPI_TX_Buf`.
 * @retval None
 * 
 */
void SPI_Send_Bytes(uint8_t bytes) {

	for (uint8_t j = 0; j < bytes; j++)
	{
		// Wait until the SPI transmit FIFO buffer is empty.
		while (SSP_GetFlagStatus(MDR_SSP1, SSP_FLAG_TFE) == RESET)	 //  while (SSP_GetFlagStatus(MDR_SSP1, SSP_FLAG_TNF) == RESET)
			;
		// Send the next byte from the transmit buffer.
		SSP_SendData(MDR_SSP1, SPI_TX_Buf[j]);
	}
	// Wait until the SPI is no longer busy.
	while (SSP_GetFlagStatus(MDR_SSP1, SSP_FLAG_BSY) == SET)
		;
}

/**
 * @brief Sends and reads a specified number of bytes over SPI.
 * 
 * This function transmits data from the `SPI_TX_Buf` buffer and simultaneously receives data into 
 * the `SPI_RX_Buf` buffer over the SPI bus. It ensures the transmit FIFO buffer is empty before 
 * sending each byte and waits until the SPI is no longer busy before receiving the corresponding data.
 * 
 * @param bytes : The number of bytes to send from `SPI_TX_Buf` and to read into `SPI_RX_Buf`.
 * @retval None
 * 
 */
void SPI_SendRead_Bytes(uint8_t bytes) {

	for (uint8_t j = 0; j < bytes; j++)
	{
		// Wait until the transmit FIFO buffer is empty
		while (SSP_GetFlagStatus(MDR_SSP1, SSP_FLAG_TFE) == RESET)
			;
		// Send the next byte from the transmission buffer
		SSP_SendData(MDR_SSP1, SPI_TX_Buf[j]);
		// Wait until SPI is no longer busy before proceeding
		while (SSP_GetFlagStatus(MDR_SSP1, SSP_FLAG_BSY) == SET)
			;
		
		// Read the received data into the reception buffer
		SPI_RX_Buf[j] = SSP_ReceiveData(MDR_SSP1);
	}

	// wait until SPI will be `not busy`
	while (SSP_GetFlagStatus(MDR_SSP1, SSP_FLAG_BSY) == SET)
		;
}

/**
 * @brief Sends a message over SPI and toggles a specified Chip Select (CS) pin.
 * 
 * This function takes a hexadecimal message as input, processes it into a byte buffer 
 * for SPI transmission, and sends the data byte-by-byte over SPI. It manages the 
 * CS pin by resetting it before the transmission and setting it after the 
 * transmission completes, ensuring proper SPI communication. The message should 
 * be a string representing hexadecimal values (e.g., "1A2B3C").
 * In SPI will be sent byte representation (e.g. "1A2B3C" -> (uint8_t)[26, 43, 60])
 * 
 * @param mes         : Pointer to a null-terminated string containing the message to send.
 *                      The string must contain an even number of characters and represent 
 *                      hexadecimal values (e.g., "1A2B").
 * @param MDR_LE_PORT : Pointer to the port controlling the Chip Select (CS) line.
 * @param MDR_LE_PIN  : Pin number in the specified port that serves as the CS line.
 * @retval None.
 * 
 */
void SPI_SendRead_HEX(char *mes, MDR_PORT_TypeDef *MDR_LE_PORT, uint32_t MDR_LE_PIN) {
    uint16_t bytes = strlen(mes) / 2;  	// Calculate the number of bytes from the hex string length.
    uint16_t nextData;					// at one variable we get 2 bytes
    char HexBuffer[2] = {0, 0};  			// Buffer to store each hex pair.

    for (uint8_t j = 0; j < bytes; j++) {
        strncpy(HexBuffer, mes + j * 2, 2);  	// Extract a pair of hex characters.
        sscanf(HexBuffer, "%hx", &nextData);  	// Convert the hex pair to a 16-bit integer.	??????? Ну вообще в 8 конечно ???????
        SPI_TX_Buf[j] = nextData;  				// Store the byte in the transmission buffer. 
    }

    PORT_ResetBits(MDR_LE_PORT, MDR_LE_PIN);  // Set CS low to begin SPI communication.
    SPI_SendRead_Bytes(bytes);                // Send the message and optionally read the response.
    PORT_SetBits(MDR_LE_PORT, MDR_LE_PIN);    // Set CS high to end SPI communication.
}

/**
  * @brief : send message over SPI and USB
  * 
  * function takes HEX string, 
  * converts it to bytes and sends it over SPI, 
  * also dublicate sended message over USB
  * 														/////////////////НЕТ ЭТО НЕ ТАК
  * @param  mes - HEX string to send, 
  * (token, that we get after parsing).
  * It is supposed to be HEX string,
  * function will convert it to byte.
  * @param  MDR_LE_PORT - port of CS
  * @param  MDR_LE_PIN - CS pin
  * @retval None.
  * 
  */
void SPI_SendReadHexWithUSBLog(char *mes, MDR_PORT_TypeDef *MDR_LE_PORT, uint32_t MDR_LE_PIN) {
	uint16_t bytes = strlen(mes) / 2;			// 0xFF = 255 (1 byte)
	SPI_SendRead_HEX(mes, MDR_LE_PORT, MDR_LE_PIN);
	USB_Print_HEX(bytes, SPI_RX_Buf);
}

/**
  * @brief : switches SPI mode
  * you can dynamically switch SPI mode
  * @param  spi - number of SSP to reconfigure.
  * @param  mode - number of SPI mode (watch struct SPImode).
  * @retval None.
  * 
  */
void SetSPIMode(uint8_t spi, uint8_t mode) {
	if (spi > 1) 
		return; //wrong spi number
	if (mode > 3) 
		return; //wrong mode number
	
	MDR_SSP_TypeDef* SSP = spi? MDR_SSP2 : MDR_SSP1; 
	
	SSP_Cmd(SSP, DISABLE);
	SSP_DeInit(SSP);	
	InitSPI(SSP, SPIModes[mode]);
	USB_PrintDebug("SPI %d, mode %d\n", spi, mode);					// зачем????? 
	
}

/**
  * @brief : configures SSP modeule
  * with specified SPI mode 
  * @param  SSP - pointer to the MDR_SSP_TypeDef (MDR_SSP1 / MDR_SSP2).
  * @param  SPImode - structure describing SPI mode.
  * @retval None.
  * 
  */
void InitSPI(MDR_SSP_TypeDef* SSP, struct SPImode SPImode) {	
    SSP_InitTypeDef sSSP = SSP_DefaultConfig;
	sSSP.SSP_SPH = SPImode.CPHA;
	sSSP.SSP_SPO = SPImode.CPOL;
	SSP_Init(SSP, &sSSP);

	/* Enable SSP */
	SSP_Cmd(SSP, ENABLE);
}

/**
  * @brief : Configures MDR_SSP1.
  * 
  * Also configures 2 CS pins, RESET pin
  * and LED pin										// Может вынести в отдельную функцию / библиотеку ?????
  * Configure SSP1 pins: FSS-PF2, CLK-PF1, RXD-PF3, TXD-PF0
  * Configure PORTF pins 0, 1, 2, 3
  * 
  * @ingroup have_same
  * @param  None
  * @retval None
  * 
  * @ingroup have_the_same
  */
void Setup_SPI(const struct spi_aux_pin aux_pins[], int aux_pins_num) {
    PORT_InitTypeDef PORT_InitStructure;
    PORT_StructInit(&PORT_InitStructure);

	// SPI MISO
	PORT_InitStructure.PORT_Pin = (SPI_RX_Pin);
	PORT_InitStructure.PORT_OE = PORT_OE_IN;
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_ALTER;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_Init(SPI_Port, &PORT_InitStructure);

	// SPI CLK
	PORT_InitStructure.PORT_Pin = (SPI_CLK_Pin); //(PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2);
	PORT_InitStructure.PORT_OE = PORT_OE_OUT;
	PORT_Init(SPI_Port, &PORT_InitStructure);

	// SPI MOSI
	PORT_InitStructure.PORT_Pin = (SPI_TX_Pin); //(PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2);
	PORT_InitStructure.PORT_PULL_DOWN = PORT_PULL_DOWN_ON;									// ?????? Зачем DOWN, надо ведь UP
	PORT_Init(SPI_Port, &PORT_InitStructure);

	// Initialization specified Chip Selects
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
	for(int i = 0; i < aux_pins_num; i++)
	{
		struct spi_aux_pin cs = aux_pins[i];
		PORT_InitStructure.PORT_Pin = (cs.pin);
		PORT_Init(cs.port, &PORT_InitStructure);
		if(cs.init_val == 1) 
			PORT_SetBits(cs.port, cs.pin);				// CS = 1
		else if (cs.init_val == 0)
			PORT_ResetBits(cs.port, cs.pin);			// CS = 0
	}

	// Initializes the SSPx peripheral clock according to the specified parameters
	SSP_BRGInit(MDR_SSP1, SSP_HCLKdiv16);
	
	InitSPI(MDR_SSP1,SPIModes[0]);
}


//deprecated
void SPI_SendThenRead(char *mes, uint8_t bytesToRead, MDR_PORT_TypeDef *MDR_LE_PORT, uint32_t MDR_LE_PIN) {
	uint16_t bytes = strlen(mes) / 2;
	uint16_t nextData;
	char HexBuffer[2] = {0};
	for (uint8_t j = 0; j < bytes; j++)
	{
		strncpy(HexBuffer, mes + j * 2, 2);
		//USB_PrintDebug("%s\n", HexBuffer);
		sscanf(HexBuffer, "%hx", &nextData);
		SPI_TX_Buf[j] = nextData;
	}

	PORT_ResetBits(MDR_LE_PORT, MDR_LE_PIN);
	SPI_SendRead_Bytes(bytes);
	SPI_SendRead_Bytes(bytesToRead);
	PORT_SetBits(MDR_LE_PORT, MDR_LE_PIN);
}


/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE spi.c */
