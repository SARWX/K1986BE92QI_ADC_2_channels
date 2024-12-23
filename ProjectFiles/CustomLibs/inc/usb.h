/**
  ******************************************************************************
  * @file    usb.h
  * @author  ICV
  * @version V1.0.0
  * @date    08/05/2024
  * @brief   USB ADC initialization Header File.
  * ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef USB_init
#define USB_init

#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_usb_handlers.h"
#include "MDR32F9Qx_ssp.h"

#include <string.h>

#include "ring_buffer.h"

#define HL_RX_BUFFER_SIZE 256   // Can be larger if desired
// #define HL_RX_BUFFER_SIZE 10   // Can be larger if desired

typedef enum
{
	USB_CDC_RX_BUFFER_OK = 0U,
	USB_CDC_RX_BUFFER_NO_DATA
} USB_CDC_RX_BUFFER_StatusTypeDef;

void Setup_USB();

void VCom_Configuration();

USB_Result USB_CDC_RecieveData(uint8_t *Buffer, uint32_t Length);

void USB_CDC_FlushringBufferRx_FS();

USB_Result USB_CDC_GetLineCoding(uint16_t wINDEX, USB_CDC_LineCoding_TypeDef *DATA);

USB_Result USB_CDC_SetLineCoding(uint16_t wINDEX, const USB_CDC_LineCoding_TypeDef *DATA);

void USB_PrintDebug(char *format, ...);

void USB_Print_SPI_Buffers(char *prefix, uint8_t bytes,uint16_t* SPI_TX_Buf,uint16_t* SPI_RX_Buf);

int USB_Print_HEX(uint8_t bytes, uint16_t* buf);

char *extract_USB_command();

void USB_Flush();

uint8_t* getStart();

void USB_Print(char *format, ...);

#endif /* USB_init */

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE usb.h */