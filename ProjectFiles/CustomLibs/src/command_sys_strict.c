#include "command_sys_strict.h"
#include "usb.h"
#include "spi.h"
#include "gpio.h"
#include "pins.h"
#include "delay.h"

#include <stdlib.h>

#define BUFFER_LENGTH 128

char tokens[5][BUFFER_LENGTH * 2]; // usb parsing tokens pointers array


/**
 * @brief 
 * 
 * @param str - command to parse
 * @retval None.
 * 
 * @ingroup command_system.c
 */
void Parse(char *str) {
	char *rest = str;
	const char k[2] = ",";		/* separator in command */
	char *chunk = strtok(str, k); // find first token
	
	uint8_t num = 0; // tokens quantity

	// 1 - распарсили команды через запятые, поместили их в tokens[]
	while (chunk != NULL)
	{
		strcpy(tokens[num], chunk); // copy chunk as token
		num++;						// increase tokens counter
		chunk = strtok(NULL, k); 	// find next token
	}

	// 2 - обработаем полученные на шаге 1 команды
	for (uint8_t i = 0; i < num; i++)
	{
		uint8_t counter = 0;

		chunk = strtok(tokens[i], ".");	// find first token
		switch (chunk[0])	// Идентификация команды происходит по первому символу
		{
			// 'n' - probe symbol 
			// it is necessary for the PC to understand which COM port the MC is on
			case 'n':
				delay_ms(100);		// whait usb (it may still send message)
				USB_Print("SPI\n");
				break;

			case 's':
				ResetRXTX();

			// 'u' - send hexadecimal message over SPI
			// also dublicate message over USB
			case 'u': // Universal SPI0 LE0					???????? не очень понятна логика нейминга, не предлагаю его менять естественно, но расшифровать здесь ???????
				while (chunk != NULL)
				{
					if (counter != 0)		// первая лексема это код команды
					{
						USB_PrintDebug("%s\n", chunk);
						SPI_SendRead_HEX(chunk, LE0_SPI0_Port, LE0_SPI0_Pin);
					}
					counter++;
					chunk = strtok(NULL, ".");
				}
				break;

			case 'z': // Synth 089 48 bits
			case 'Y': // Synth mldr 32 READ
			case 'b': // Universal SPI0 LE1
				while (chunk != NULL)
				{
					if (counter != 0)
					{
						USB_PrintDebug("%s\n", chunk);
						SPI_SendRead_HEX(chunk, LE1_SPI0_Port, LE1_SPI0_Pin);
						//USB_Print_SPI_Buffers("SN ", 4, SPI_TX_Buf, SPI_RX_Buf);
					}
					counter++;
					chunk = strtok(NULL, ".");
				}
				break;

			case 'W': // Case for "W" command
						{
							uint8_t pin = 0;
							uint8_t value = 0;
							while (chunk != NULL) {
									if (counter == 1) {	// 1st token after 'W' is the pin number
											pin = (uint8_t)atoi(chunk);
									} else if (counter == 2) {	// 2nd token is the pin value
											value = (uint8_t)atoi(chunk);
									}
									counter++;
									chunk = strtok(NULL, ".");
							}
							// Call WriteGPIO with parsed pin and value
							WriteGPIO(pin, value);
							USB_PrintDebug("WriteGPIO called with pin %d, value %d\n", pin, value);
							break;
						}
			case 'R': // Read pin status
						{
							uint8_t pin = 0;
							uint8_t value = 0;
							while (chunk != NULL) {
									if (counter == 1) {	// 1st token after 'W' is the pin number
											pin = (uint8_t)atoi(chunk);
									} else if (counter == 2) {	// 2nd token is the pin value
											value = (uint8_t)atoi(chunk);
									}
									counter++;
									chunk = strtok(NULL, ".");
							}
							// Call WriteGPIO with parsed pin and value
							ReadGPIO(pin);
	//						USB_PrintDebug("WriteGPIO called with pin %d, value %d\n", pin, value);
							break;
						}
			case 'M': // Set SPI mode
						{
							uint8_t spi = 0;
							uint8_t mode = 0;
							while (chunk != NULL) {
									if (counter == 1) {	// 1st token after 'M' is the SPI number //0 or 1
											spi = (uint8_t)atoi(chunk);
									} else if (counter == 2) {	// 2nd token is the SPI Mode // 0..3
											mode = (uint8_t)atoi(chunk);
									}
									counter++;
									chunk = strtok(NULL, ".");
							}
							// Call SPI with parsed pin and value
							SetSPIMode(spi, mode);

							break;
						}
			case 'S': // SPI 32 bits with reset READ
				ResetRXTX();
			case 'U':
				while (chunk != NULL)
				{
					if (counter != 0)
					{
						USB_PrintDebug("%s\n", chunk);
						SPI_SendReadHexWithUSBLog(chunk, LE0_SPI0_Port, LE0_SPI0_Pin);
					}
					counter++;
					chunk = strtok(NULL, ".");
				}
				break;
			case 'B':
				while (chunk != NULL)
				{
					if (counter != 0)
					{
						USB_PrintDebug("%s\n", chunk);
						SPI_SendReadHexWithUSBLog(chunk, LE1_SPI0_Port, LE1_SPI0_Pin);
					}
					counter++;
					chunk = strtok(NULL, ".");
				}
				break;

			default:
				USB_PrintDebug("Unknown cmd: %s\n", tokens[i]);
	//			USB_Flush();
				break;
		}
	}
}
