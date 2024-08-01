/**
  ******************************************************************************
  * @file    USB_init.c
  * @author  ICV
  * @version V1.0.0
  * @date    08/05/2024
  * @brief   This file contains initialization of USB CDC
  * ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_usb_handlers.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_ssp.h"
#include "MDR32F9Qx_port.h"
#include <string.h>
#include "USB_init.h"
#include "defines.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

extern PORT_InitTypeDef port_init_structure;
static USB_Clock_TypeDef USB_Clock_InitStruct;
static USB_DeviceBUSParam_TypeDef USB_DeviceBUSParam;
static MDR_SSP_TypeDef SSP_InitStruct;
SSP_InitTypeDef sSSP;
PORT_InitTypeDef port_init_structure;
extern uint8_t *buffer;
char rec_buf[BUFFER_LENGTH];
static uint8_t DoubleBuf[BUFFER_LENGTH * 2];
extern int command_recived;

char *start;
char *end;
char tokens[5][BUFFER_LENGTH * 2]; //usb parsing tokens pointers array
char debugString[100];			   //debug

#ifdef USB_CDC_LINE_CODING_SUPPORTED
static USB_CDC_LineCoding_TypeDef LineCoding;
#endif /* USB_CDC_LINE_CODING_SUPPORTED */

/**
  * @brief  Configures and enables USB peripheral
  * @param  None
  * @retval None
  */
void Setup_USB(void) 
{
	/* Enables the CPU_CLK clock on USB */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_USB, ENABLE);

	/* Device layer initialization */
	USB_Clock_InitStruct.USB_USBC1_Source = USB_C1HSEdiv2; // HSE / 2 = 8MHz
	USB_Clock_InitStruct.USB_PLLUSBMUL = USB_PLLUSBMUL6;   // 8MHz * 6 = 48MHz
	USB_DeviceBUSParam.MODE = USB_SC_SCFSP_Full;
	USB_DeviceBUSParam.SPEED = USB_SC_SCFSR_12Mb;
	USB_DeviceBUSParam.PULL = USB_HSCR_DP_PULLUP_Set;
	USB_DeviceInit(&USB_Clock_InitStruct, &USB_DeviceBUSParam);

	/* Enable all USB interrupts */
	USB_SetSIM(USB_SIS_Msk);
	USB_DevicePowerOn();
	
	/* Enable interrupt on USB */
#ifdef USB_INT_HANDLE_REQUIRED
	NVIC_EnableIRQ(USB_IRQn);
#endif /* USB_INT_HANDLE_REQUIRED */
	USB_DEVICE_HANDLE_RESET;
}

/**
  * @brief  Configures Communications Device Class 
  * @param  None
  * @retval None
  */
void VCom_Configuration(void) 
{
	#ifdef USB_CDC_LINE_CODING_SUPPORTED
		//LineCoding.dwDTERate = 9600;
		LineCoding.dwDTERate = 16000000;
		LineCoding.bCharFormat = 0;
		LineCoding.bParityType = 0;
		LineCoding.bDataBits = 8;
	#endif /* USB_CDC_LINE_CODING_SUPPORTED */
}

/**
  * @brief  Callback function for reciving data through USB CDC 
  * @param  None
  * @retval result of the reception @ref USB_Result
  */
USB_Result USB_CDC_RecieveData(uint8_t *buffer, uint32_t Length) 
{
	memcpy(rec_buf, buffer, BUFFER_LENGTH);
	command_recived = 1;
	return USB_SUCCESS;
}

#ifdef USB_CDC_LINE_CODING_SUPPORTED

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

USB_Result USB_CDC_SetLineCoding(uint16_t wINDEX, const USB_CDC_LineCoding_TypeDef *DATA) {
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

/**
  * @brief  this function makes formated string and
  * 		transmits it via USB, helpful for debug
  * @param  format - formated string 
  * @retval None
  */
void USB_Print(char *format, ...)
{
	va_list argptr;
	va_start(argptr, format);

	vsprintf(debugString, format, argptr);
	va_end(argptr);
	USB_CDC_SendData((uint8_t *)debugString, strlen(debugString));
}
/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE USB_init.c */