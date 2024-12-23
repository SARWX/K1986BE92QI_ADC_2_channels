#include "gpio.h"
#include "pins.h"
#include "usb.h"


/**
 * @brief Structure for storing the standard configuration of the output port.
 * 
 * This structure is used to initialize the port pins with parameters,
 * which provide the basic configuration for working with outputs.
 * 
 * @note This configuration doesn't specify port pins
 * 		 so after coping config change pinnumber
 */
const PORT_InitTypeDef GPIO_DefaultOutStruct =
{
    .PORT_Pin       = 0,
    .PORT_OE        = PORT_OE_OUT,
    .PORT_PULL_UP   = PORT_PULL_UP_OFF,
    .PORT_PULL_DOWN = PORT_PULL_DOWN_OFF,
    .PORT_PD_SHM    = PORT_PD_SHM_OFF,
    .PORT_PD        = PORT_PD_DRIVER,
    .PORT_GFEN      = PORT_GFEN_OFF,
    .PORT_FUNC      = PORT_FUNC_PORT,
    .PORT_SPEED     = PORT_SPEED_MAXFAST,
    .PORT_MODE      = PORT_MODE_DIGITAL,
};

/** 
 * @brief This array of structures 
 * describes all used GPIO pins
 * 
 * @ingroup gpio.c ????
 */
const struct GPIOpin GPIO[13] = { //All GPIO pins
		{0,	63, PORT_Pin_0,		MDR_PORTA},
		{1,	62, PORT_Pin_1,		MDR_PORTA},
		{2,	61, PORT_Pin_2,		MDR_PORTA},
		{3,	60, PORT_Pin_3,		MDR_PORTA},
		{4,	59, PORT_Pin_4,		MDR_PORTA},
		{5,	58, PORT_Pin_5,		MDR_PORTA},
		{6,	57, PORT_Pin_6,		MDR_PORTA},
		{7,	56, PORT_Pin_7,		MDR_PORTA},
		{8,	55, PORT_Pin_10, 	MDR_PORTB},
		{9,	54, PORT_Pin_9,		MDR_PORTB},
		{10, 51, PORT_Pin_6,	MDR_PORTB},
		{11, 50, PORT_Pin_5,	MDR_PORTB},
		{12, 40, PORT_Pin_2,	MDR_PORTC} //LED pin
};

/**
  * @brief : function configures all
  * pins that used as simple GPIO
  * @param  None							// Давайте будем передавать массив структур GPIO[] для инициализаци ????????????
  * @retval None.
  */
void GPIO_InitOutputs() {
	PORT_InitTypeDef PORT_InitStructure = GPIO_DefaultOutStruct;

	for (int i = 0; i < 13; i++) {
		PORT_InitStructure.PORT_Pin = (GPIO[i].pinPortPinNumber);
		PORT_Init(GPIO[i].pinPort, &PORT_InitStructure);
	}
}

/**
 * @brief Configures the direction of a GPIO pin (input or output).
 * 
 * This function sets the direction (input or output) of a specified GPIO pin. 
 * It checks if the current direction matches the requested direction, and if not, 
 * it reconfigures the pin's direction by initializing the pin with the provided `direction`.
 * 
 * @param pinNumber : The GPIO pin number to configure.
 * @param direction : The direction of the pin (PORT_OE_OUT for output, PORT_OE_IN for input).
 * @retval None.
 */
void Switch_GPIO(int pinNumber, PORT_OE_TypeDef direction) {
    // Check if the current direction matches the desired direction

	PORT_OE_TypeDef cur_direction = (PORT_OE_TypeDef) ( 
		(	GPIO[pinNumber].pinPort->OE // 1 or 0
			& 
		(uint32_t)GPIO[pinNumber].pinPortPinNumber	) // 1 << pin number
			==		// convert to 1 / 0
		(uint32_t)GPIO[pinNumber].pinPortPinNumber
	);

    if (cur_direction != direction) 
	{
		PORT_InitTypeDef PORT_InitStructure = GPIO_DefaultOutStruct;

        // If not, reconfigure the pin's direction
        PORT_InitStructure.PORT_OE = direction;
        PORT_InitStructure.PORT_Pin = (GPIO[pinNumber].pinPortPinNumber);

        PORT_Init(GPIO[pinNumber].pinPort, &PORT_InitStructure);
        // Optional delay to prevent incorrect readings (commented out)
        // Delayms(10);
    }
}

/**
 * @brief Sets the state of a GPIO pin.
 * 
 * This function sets the state (high or low) of a specified GPIO pin. It first switches the 
 * GPIO pin using the `Switch_GPIO` function, then sets or resets the pin based on the provided 
 * `state` argument.
 * 
 * @param pinNumber : The GPIO pin number to configure.
 * @param state     : The desired state of the pin (1 for high, 0 for low).
 * @retval None
 * 
 * @ingroup gpio.c
 */
void WriteGPIO(int pinNumber, int state) {
	Switch_GPIO(pinNumber, PORT_OE_OUT);	// switch GPIO pin to output
	
	// Set the pin high if state is 1, else set it low.
	if(state) {
		// Set the pin high
		PORT_SetBits(GPIO[pinNumber].pinPort,GPIO[pinNumber].pinPortPinNumber);
	} else {
		// Set the pin low
		PORT_ResetBits(GPIO[pinNumber].pinPort,GPIO[pinNumber].pinPortPinNumber);
	}
}

/**
 * @brief Reads the state of a GPIO pin and prints it.
 * 
 * This function reads the input state of a specified GPIO pin and prints the result 
 * to the USB terminal using the `USB_Print` function. It first switches the GPIO pin using 
 * `Switch_GPIO` and then retrieves and prints the current input value of the pin.
 * 
 * @param pinNumber : The GPIO pin number to read.
 * @retval None.
 * 
 * @ingroup gpio.c
 */
void ReadGPIO(int pinNumber) {
	Switch_GPIO(pinNumber, PORT_OE_IN);	// switch GPIO pin to input
	
	// Print "1" if state is high, else print "0".
	USB_Print(
		"%d\n", 
		PORT_ReadInputDataBit(
			GPIO[pinNumber].pinPort,
			GPIO[pinNumber].pinPortPinNumber
		)
	);
}

/**
  * @brief : function executes next sequence:
  * 1) RESET 	-> 1 -> 0
  * 2) SPI_CLK 	-> 1 -> 0
  * 3) RESET 	-> 0 -> 1
  * 
  * This function is used for devices with a reset 
  * synchronizer. When the device needs not only a reset, 
  * but also several CLK pulses during the reset. 
  * Therefore the CLK pin is initialized to the GPIO 
  * so that it can be controlled and then back again.
  * 
  * @param  None.
  * @retval None.
  * 
  * @ingroup gpio.c
  */
void ResetRXTX() {
	PORT_InitTypeDef PORT_InitStructure = GPIO_DefaultOutStruct;

	PORT_SetBits(SPI_RESET_Port, SPI_RESET_Pin);
	PORT_ResetBits(SPI_RESET_Port, SPI_RESET_Pin);

	PORT_InitStructure.PORT_Pin = (SPI_CLK_Pin);
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
	PORT_Init(SPI_Port, &PORT_InitStructure);

	PORT_SetBits(SPI_Port, SPI_CLK_Pin);
//	delayTick(100);
	PORT_ResetBits(SPI_Port, SPI_CLK_Pin);

	PORT_InitStructure.PORT_FUNC = PORT_FUNC_ALTER;
	PORT_Init(SPI_Port, &PORT_InitStructure);

	PORT_ResetBits(SPI_RESET_Port, SPI_RESET_Pin);
	PORT_SetBits(SPI_RESET_Port, SPI_RESET_Pin);
}
