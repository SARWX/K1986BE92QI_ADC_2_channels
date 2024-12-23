#ifndef GPIO_H
#define GPIO_H

#include "MDR32F9Qx_port.h"

/** @struct GPIOpin
 *  @brief This structure describes port pin
 * it is used to hold GPIO initialization 
 * @param pinNumber
 * just our own sequence number of the pin
 * @param pinPhysNumber
 * physical number of the pin
 * @param pinPortPinNumber
 * number of pin inside port group
 * @param pinPort
 * pointer to the port sructure
 */
struct GPIOpin {
	int pinNumber;
	int pinPhysNumber;
	PORT_Pin_TypeDef pinPortPinNumber;
	MDR_PORT_TypeDef* pinPort;
};	

void GPIO_InitOutputs();

void Switch_GPIO(int pinNumber, PORT_OE_TypeDef direction);

void WriteGPIO(int pinNumber, int state);

void ReadGPIO(int pinNumber);

void ResetRXTX();

#endif // GPIO_H