#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_usb_handlers.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_ssp.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_adc.h"
#include "MDR32F9Qx_dac.h"
#include "MDR32F9Qx_dma.h"
#include "MDR32F9Qx_timer.h"

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

// Собственные библиотеки
#include "DMA_for_proj.h"
#include "DAC_for_proj.h"
#include "ADC_for_proj.h"
#include "SysCLK_for_proj.h"
#include "USB_for_proj.h"

#include "defines_for_proj.h"
/* Внешние переменные ---------------------------------------------------------*/
extern uint8_t *Buffer;

// Массивы для АЦП
uint16_t MainArrayForADC[NUM_OF_MES];						// Массив измерений АЦП для заполнения сновной структурой DMA
uint16_t AlternateArrayForADC[NUM_OF_MES];			// Массив измерений АЦП для заполнения альтернативной структурой DMA

// Структуры для DMA
extern DMA_ChannelInitTypeDef sDMA_ADC1;
extern DMA_ChannelInitTypeDef sDMA_TIM2;
extern DMA_CtrlDataInitTypeDef sDMA_PriCtrlData_ADC1;				// Основная структура канала для ADC1
extern DMA_CtrlDataInitTypeDef sDMA_AltCtrlData_ADC1;				// Альтернативная структура канала для ADC1
extern DMA_CtrlDataInitTypeDef sDMA_PriCtrlData_TIM2;
extern DMA_CtrlDataInitTypeDef sDMA_AltCtrlData_TIM2;

/* ---------------------------------------------------------------------------*/
static void StageOneDMA();														// Первый этап работы 
static void StageTwoDMA();														// Второй этап работы

int main(void) 
{
	VCom_Configuration();
	SetupADC();
	SetupDMA();
	USB_CDC_Init(Buffer, 1, SET);
	Setup_CPU_Clock();
	Setup_USB();
	
	// Включение АЦП и DMA для АЦП
	ADC1_Cmd (ENABLE);																	// Разрешение работы ADC1
	DMA_Cmd(DMA_Channel_ADC1, ENABLE);									// Разрешаение работы DMA с каналом ADC1

	// Основной цикл
	while (1) 
	{
		StageOneDMA();
		StageTwoDMA();
	}	
}

// 1 стадия - заполнение буфера, с использованием основной структуры DMA, 
// параллельная передача буфера альтернативной по USB
void StageOneDMA()
{
		while (DMA_GetFlagStatus(DMA_Channel_ADC1, DMA_FLAG_CHNL_ALT) == 0);								// ждем, когда DMA перейдет на альтернативную структуру
		DMA_CtrlInit(DMA_Channel_ADC1, DMA_CTRL_DATA_PRIMARY, &sDMA_PriCtrlData_ADC1);			// реинициализируем основную структуру
		USB_CDC_SendData((uint8_t *)(MainArrayForADC), ((NUM_OF_MES) * 2 ));								// отправка буфера основной структуры DMA по USB
}

// 2 стадия - заполнение буфера, с использованием альтернативной структуры DMA,
// параллельная передача буфера основной по USB
void StageTwoDMA()
{
		while (DMA_GetFlagStatus(DMA_Channel_ADC1, DMA_FLAG_CHNL_ALT) != 0);								// ждем, когда DMA перейдет на основную структуру
		DMA_CtrlInit(DMA_Channel_ADC1, DMA_CTRL_DATA_ALTERNATE, &sDMA_AltCtrlData_ADC1);		// реинициализируем альтернативную структуру
		USB_CDC_SendData((uint8_t *)(AlternateArrayForADC), ((NUM_OF_MES) * 2));						// отправка буфера альтернативной структуры DMA по USB

}
