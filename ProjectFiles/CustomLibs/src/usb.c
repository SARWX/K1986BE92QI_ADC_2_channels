/**
  ******************************************************************************
  * @file    usb.c
  * @author  ICV
  * @version V1.2.0
  * @date    05/12/2024
  * @brief   This file contains initialization of USB CDC 
  * 		 and all related functions
  * ******************************************************************************
  */

#include "usb.h"
#include "defines.h"
#include "dac.h"

#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_usb_handlers.h"
#include "MDR32F9Qx_ssp.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


//#define DEBUG

#ifdef USB_CDC_LINE_CODING_SUPPORTED
static USB_CDC_LineCoding_TypeDef LineCoding;
#endif /* USB_CDC_LINE_CODING_SUPPORTED */

uint8_t ringBufferRx[HL_RX_BUFFER_SIZE];   	/* Receive buffer (ring buffer) */
volatile uint16_t ringBufferWritePos = 0; 	/* Receive buffer write position */
volatile uint16_t ringBufferReadPos = 0; 	/* Receive buffer read position */

uint8_t ringBufferCache[HL_RX_BUFFER_SIZE]; 			/* caching buffer (USB recive) */
uint8_t stringBuffer[HL_RX_BUFFER_SIZE];	/* buffer for extracted command */ 

uint16_t bytesAvailable;	// ?????????????????
char *start = (char *)ringBufferCache;		/* pointer start position in USB recive buffer */
char *end = (char *)ringBufferCache;			/* pointer end position in USB recive buffer */
char *lastStartFound = (char *)ringBufferCache;	/* last found start position of the command */ 
char *lastEndFound = (char *)ringBufferCache;	/* last found end position of the command */
char tempString[100];

/**
 * @brief	USB Device layer setup and powering on
 * @param	None
 * @retval None
 * @ingroup have_same
 */
void Setup_USB(void) 
{
	/* Enables the CPU_CLK clock on USB */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_USB, ENABLE);
	/* Device layer initialization */
	USB_Clock_TypeDef USB_Clock_InitStruct;
	USB_Clock_InitStruct.USB_USBC1_Source = USB_C1HSEdiv2; // HSE / 2 = 8MHz
	USB_Clock_InitStruct.USB_PLLUSBMUL = USB_PLLUSBMUL6;   // 8MHz * 6 = 48MHz
	USB_DeviceBUSParam_TypeDef USB_DeviceBUSParam;
	USB_DeviceBUSParam.MODE = USB_SC_SCFSP_Full;
	USB_DeviceBUSParam.SPEED = USB_SC_SCFSR_12Mb;
	USB_DeviceBUSParam.PULL = USB_HSCR_DP_PULLUP_Set;
	USB_DeviceInit(&USB_Clock_InitStruct, &USB_DeviceBUSParam);
	/* Enable all USB interrupts */
	 USB_SetSIM(USB_SIS_SCTDONE_Set);
	USB_DevicePowerOn();
	/* Enable interrupt on USB */
#ifdef USB_INT_HANDLE_REQUIRED
	NVIC_EnableIRQ(USB_IRQn);
#endif /* USB_INT_HANDLE_REQUIRED */
	USB_DEVICE_HANDLE_RESET;
}

/**
 * @brief	Example-relating data initialization
 * @param	None
 * @retval None
 * @ingroup have_same
 */
void VCom_Configuration()
{
#ifdef USB_CDC_LINE_CODING_SUPPORTED
	// LineCoding.dwDTERate = 4800;
	LineCoding.dwDTERate = 10000000;
	LineCoding.bCharFormat = 0;
	LineCoding.bParityType = 0;
	LineCoding.bDataBits = 8;
#endif /* USB_CDC_LINE_CODING_SUPPORTED */
}

/**
 * @brief	USB_CDC_HANDLE_DATA_RECEIVE implementation - data echoing
 * @param	Buffer: Pointer to the user's buffer with received data
 * @param	Length: Length of data
 * @retval @ref USB_Result.
 */
#ifdef SHFKIT
extern int strict_command_recived;

	USB_Result USB_CDC_RecieveData(uint8_t *Buffer, uint32_t Length)
	{
		strict_command_recived = 1;
		uint16_t tempHeadPos = ringBufferWritePos; // Increment temp head pos while writing, then update main variable when complete

		for (uint32_t i = 0; i < Length; i++)
		{
			ringBufferRx[tempHeadPos] = Buffer[i];
			tempHeadPos = (uint16_t)((uint16_t)(tempHeadPos + 1) % HL_RX_BUFFER_SIZE);
			if (tempHeadPos == ringBufferReadPos)
			{
				return USB_ERROR;
			}
		}

		ringBufferWritePos = tempHeadPos;
		return USB_SUCCESS;
	}
#elif defined(PCR)
	extern int dac_mode;
	char rec_buf[BUFFER_LENGTH];
	extern int command_recived;
	volatile enum dac_mode_state usb_dac_mode_state = not_init;
USB_Result USB_CDC_RecieveData(uint8_t *buffer, uint32_t Length) 
{
	if (dac_mode == 0)
	{
		memcpy(rec_buf, buffer, BUFFER_LENGTH);
		command_recived = 1;
		return USB_SUCCESS;
	}
	return USB_SUCCESS;
}
#endif

/**
 * @brief : function clears receive buffer for USB.
 * 
 * Also function null positions:
 * - Receive buffer write position (ringBufferWritePos)
 * - Receive buffer read position (ringBufferReadPos)
 * 
 * @param  None.
 * @retval None.
 */
void USB_CDC_FlushringBufferRx_FS()
{
	memset(ringBufferRx, 0, HL_RX_BUFFER_SIZE);
	ringBufferWritePos = 0;
	ringBufferReadPos = 0;
}

#ifdef USB_CDC_LINE_CODING_SUPPORTED

/**
 * @brief	USB_CDC_HANDLE_GET_LINE_CODING implementation example
 * @param	wINDEX: Request value 2nd word (wIndex)
 * @param	DATA: Pointer to the USB_CDC Line Coding Structure
 * @retval @ref USB_Result.
 */
USB_Result USB_CDC_GetLineCoding(uint16_t wINDEX, USB_CDC_LineCoding_TypeDef *DATA)
{
	assert_param(DATA);
	if (wINDEX != 0)
	{
		/* Invalid interface */
		return USB_ERR_INV_REQ;
	}

	/* Just store received settings */
	*DATA = LineCoding;
	return USB_SUCCESS;
}

/**
 * @brief	USB_CDC_HANDLE_SET_LINE_CODING implementation example
 * @param	wINDEX: Request value 2nd word (wIndex)
 * @param	DATA: Pointer to the USB_CDC Line Coding Structure
 * @retval @ref USB_Result.
 */
USB_Result USB_CDC_SetLineCoding(uint16_t wINDEX, const USB_CDC_LineCoding_TypeDef *DATA)
{
	assert_param(DATA);
	if (wINDEX != 0)
	{
		/* Invalid interface */
		return USB_ERR_INV_REQ;
	}

	/* Just send back settings stored earlier */
	LineCoding = *DATA;
	return USB_SUCCESS;
}

#endif /* USB_CDC_LINE_CODING_SUPPORTED */

void USB_PrintDebug(char *format, ...)
{
#ifdef DEBUG
	va_list argptr;
	va_start(argptr, format);

	vsprintf(tempString, format, argptr);
	va_end(argptr);
	// CDC_Transmit_FS((uint8_t *)tempString,strlen(tempString) );
	USB_CDC_SendData((uint8_t *)tempString, strlen(tempString));
//	delayTick(timeout);
#endif
}

/**
 * @brief Prints SPI transmission and reception buffers in hexadecimal format.
 * 
 * This function takes the given SPI transmission (`SPI_TX_Buf`) and reception (`SPI_RX_Buf`) buffers, 
 * formats them into a string in hexadecimal format, and sends the formatted string to USB for printing. 
 * The `prefix` string is added at the beginning of the output for identification.
 * 
 * @param  prefix  A string that will be added at the beginning of the output for identification.
 * @param  bytes   The number of bytes to process from the buffers.
 * @param  SPI_TX_Buf  A pointer to the buffer holding the SPI transmission data.
 * @param  SPI_RX_Buf  A pointer to the buffer holding the SPI reception data.
 * @retval None
 */
void USB_Print_SPI_Buffers(char *prefix, uint8_t bytes, uint16_t* SPI_TX_Buf, uint16_t* SPI_RX_Buf) {
    // Start with the prefix and initialize temp buffer for formatting
    strcpy(tempString, prefix);
    char temp[10];

    // Format and append the SPI transmission buffer in hex
    for (uint8_t i = 0; i < bytes; i++) {
        sprintf(temp, "%02X", SPI_TX_Buf[i]);
        strcat(tempString, temp);
    }

    // Add a space between transmission and reception data
    strcat(tempString, " ");

    // Format and append the SPI reception buffer in hex
    for (uint8_t i = 0; i < bytes; i++) {
        sprintf(temp, "%02X", SPI_RX_Buf[i]);
        strcat(tempString, temp);
    }

    // Add a newline character to the end
    strcat(tempString, "\n");

    // Print the formatted string to USB
    USB_Print(tempString);
}

/**
  * @brief : Converts a buffer of 16-bit values into a hexadecimal string and sends it via USB.
  * 
  * @param  bytes : Number of 16-bit values in the buffer.
  * @param  buf   : Pointer to the buffer containing 16-bit values to be converted and sent.
  * @retval None
  */
int USB_Print_HEX(uint8_t bytes, uint16_t* buf)
{
	uint32_t ts_size = (2 * bytes + 1);
	char *tmp_str = malloc(sizeof(uint8_t) * ts_size);
	if (!tmp_str)
		return(-1);
		
    char *ptr = tmp_str;        	// Указатель для перемещения и записи в буфер.
    for (uint8_t i = 0; i < bytes; i++) {

		// каждый раз обозначаем сколько места у нас осталось
		// печатаем по 2 символа 16-ричного формата
        ptr += snprintf(ptr, (((uint32_t)tmp_str + ts_size) - (uint32_t)ptr), "%02X", buf[i]);
    }

    USB_Print(tmp_str);  // Отправить полученную строку по USB.

	free(tmp_str);

	return(0);
}

/**
 * @brief Processes incoming USB data and extracts a command framed by '<' and '>'.
 * 
 * This function checks the USB receive buffer for new data, identifies commands 
 * enclosed in '<...>' markers, and extracts the command into `stringBuffer`. 
 * It updates pointers to track the last found start and end markers and marks
 * the processed command as completed by replacing the markers with '='.
 * 
 * @retval !0 : A command was successfully extracted, marked as completed.
 * @retval 0  : No command was found or processed.
 */
char *extract_USB_command() {
	bytesAvailable = GetRingBufferBytesAvailable();
	if (bytesAvailable > 0) {
		if (CopyRingBufferToBuffer(ringBufferCache, bytesAvailable) == USB_CDC_RX_BUFFER_OK) {		// всегда возвращает OK
			if(start == NULL && end) *end='='; //wrong commands		// Не понял, когда это может быть? и почему надо *end='='; ???????
			if(end == NULL){end = (char *)ringBufferCache;}		// Когда это может быть ???????
			if(start == NULL){start =(char *)ringBufferCache;}	// Когда это может быть ???????
		}
	}

	if (end != NULL && start != NULL )
	{	
		start = strchr_from_ring_buffer((char *)ringBufferCache,HL_RX_BUFFER_SIZE, lastStartFound ,'<');	// устанавливаем границы нашей команды
		end = strchr_from_ring_buffer((char *)ringBufferCache,HL_RX_BUFFER_SIZE, lastEndFound ,'>');		// команда обрамляется <...>
	}

	if (end != NULL && start != NULL )	// если нашли команду
	{
		lastStartFound=start;	// обновим последние найденные позиции
		lastEndFound=end;		// начала и конца команды
		copyRingBufferExcludingBounds((char *)ringBufferCache, HL_RX_BUFFER_SIZE, start, end, (char *)stringBuffer);
		// mark command as completed
		*start = '=';		// '<'  -->  '='
		*end = '=';			// '>'  -->  '='
		return (char *)stringBuffer;
	} 

	return (char *)0;
}

/**
 * @brief Clears the USB reception buffers and resets the pointers.
 * 
 * This function clears the `ringBufferCache` and `ringBufferRx` by setting all bytes to zero using `memset`. 
 * It also resets the `lastStartFound` and `lastEndFound` pointers to the beginning of the `ringBufferCache` buffer. 
 * This ensures that the buffers are empty and ready for the next data reception.
 * 
 * @retval None
 */
void USB_Flush() {
    // Clear the ringBufferCache and ringBufferRx by setting all bytes to zero
    memset(ringBufferCache, 0, HL_RX_BUFFER_SIZE);
    memset(ringBufferRx, 0, HL_RX_BUFFER_SIZE);
    
    // Reset the start and end pointers to the beginning of ringBufferCache
    lastStartFound = (char *)ringBufferCache;
    lastEndFound = (char *)ringBufferCache;
}

/**
 * @brief Sends a formatted string over USB.
 * 
 * This function formats a string using a variable argument list, stores it in a temporary buffer, 
 * and transmits it via USB. It supports standard printf-style formatting.
 * 
 * @param format : A format string specifying how to format the output.
 * @param ...    : Additional arguments providing values to be formatted according to the `format` string.
 * @retval None
 */
void USB_Print(char *format, ...)
{
    va_list argptr;  /* Declare a variable to hold the variable argument list */

    va_start(argptr, format);  // Initialize the argument list with the format string

    vsprintf(tempString, format, argptr);  // Format the string and store it in the temporary buffer
    va_end(argptr);  // Clean up the variable argument list

    USB_CDC_SendData((uint8_t *)tempString, strlen(tempString));  // Send the formatted string over USB.
}

uint8_t* getStart() {
	return stringBuffer;
}

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE usb.c */
