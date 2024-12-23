#ifndef SPI_H
#define SPI_H

#include "MDR32F9Qx_ssp.h"
#include "MDR32F9Qx_port.h"

/**
 * @brief Structure defining SPI mode parameters.
 * @param mode
 * custom number of SPImode
 * @param CPOL
 * Clock polarity: Low or High
 * @param CPHA
 * Clock phase: 1Edge or 2Edge
 */
struct SPImode {
	uint8_t mode;					
	SSP_Clock_Polarity_TypeDef CPOL;
	SSP_Clock_Phase_TypeDef CPHA;	
};	

/** 
 * @struct spi_aux_pin
 * @brief Describes an auxiliary SPI pin for functionalities like CS or reset.
 *
 * This structure manages additional SPI-related pins, such as Chip Select (CS), 
 * reset pins, and other auxiliary pins.
 * @param init_val
 * 1 or 0 (-1 = NO INIT VAL)
 * @param pin
 * port pin number
 * @param port
 * GPIO port
 */
struct spi_aux_pin {
    int init_val;
    PORT_Pin_TypeDef pin;
    MDR_PORT_TypeDef* port;
};

void SPI_Send_Bytes(uint8_t bytes);

void SPI_SendRead_Bytes(uint8_t bytes);

void SPI_SendRead_HEX(char *mes, MDR_PORT_TypeDef *MDR_LE_PORT, uint32_t MDR_LE_PIN);

void SPI_SendReadHexWithUSBLog(char *mes, MDR_PORT_TypeDef *MDR_LE_PORT, uint32_t MDR_LE_PIN);

void SetSPIMode(uint8_t spi, uint8_t mode);

void InitSPI(MDR_SSP_TypeDef* SSP, struct SPImode SPImode);

void Setup_SPI(const struct spi_aux_pin cs_arr[], int aux_pins_num);

void SPI_SendThenRead(char *mes, uint8_t bytesToRead, MDR_PORT_TypeDef *MDR_LE_PORT, uint32_t MDR_LE_PIN);

#endif // SPI_H