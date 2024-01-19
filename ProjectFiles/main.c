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
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

// Собственные библиотеки
#include "DMA_for_proj.h"
#include "DAC_for_proj.h"
#include "ADC_for_proj.h"
#include "SysCLK_for_proj.h"
#include "USB_for_proj.h"
#include "Command_system.h"

/* Макроподстановки --------------------------------------------------------------*/
#include "defines_for_proj.h"
/* Внешние переменные ---------------------------------------------------------*/
int command_recived = 0;
static char Buffer[BUFFER_LENGTH];
char RcBuffer[BUFFER_LENGTH];
extern char RecBuf[];						// Массив в котором записана переданная команда
// массивы для АЦП
uint16_t ADC1_array_m[NUM_OF_MES];			// Массив измерений АЦП для заполнения сновной структурой DMA
uint16_t ADC1_array_a[NUM_OF_MES];			// Массив измерений АЦП для заполнения альтернативной структурой DMA

/* ---------------------------------------------------------------------------*/

int main(void) {
	VCom_Configuration();

	/* CDC layer initialization */
	SetupADC();
	SetupDMA();
	USB_CDC_Init((uint8_t *)Buffer, 1, SET);
	Setup_CPU_Clock();
	Setup_USB();
	Set_DAC_Table(100);
	SetupDAC();
	SetupTIM2();
	// Включение DMA для ЦАП
	DMA_Cmd(DMA_Channel_TIM2, ENABLE);
	// Включение АЦП и DMA для АЦП
	ADC1_Cmd (ENABLE);						// разрешаем работу ADC1
	DMA_Cmd(DMA_Channel_ADC1, ENABLE);		// разрешаем работу DMA с каналом ADC1

	/* Main loop */
	while (1) {
		if (command_recived == 1) {
			ADC1_Cmd (DISABLE);
			// strcpy(RcBuffer, Buffer);
			command_recived = 0;
			execute_command(RecBuf);
			for(int i = 0; i < BUFFER_LENGTH; i++) {
				Buffer[i] = 0;
			}
			ADC1_Cmd (ENABLE);
		}
		// 1 стадия - заполнение буфера, с использованием основной структуры DMA, параллельная передача буфера альтернативной по USB
		while (DMA_GetFlagStatus(DMA_Channel_ADC1, DMA_FLAG_CHNL_ALT) == 0)
			;					// ждем, когда DMA перейдет на альтернативную структуру
		DMA_CtrlInit(DMA_Channel_ADC1, DMA_CTRL_DATA_PRIMARY, &sDMA_PriCtrlData_ADC1);		// реинициализируем основную структуру
		USB_CDC_SendData((uint8_t *)(ADC1_array_m), ((NUM_OF_MES) * 2 ));					// отправка буфера основной структуры DMA по USB

		// 2 стадия - заполнение буфера, с использованием альтернативной структуры DMA, параллельная передача буфера основной по USB
		while (DMA_GetFlagStatus(DMA_Channel_ADC1, DMA_FLAG_CHNL_ALT) != 0)
			;					// ждем, когда DMA перейдет на основную структуру
		DMA_CtrlInit(DMA_Channel_ADC1, DMA_CTRL_DATA_ALTERNATE, &sDMA_AltCtrlData_ADC1);	// реинициализируем альтернативную структуру
		USB_CDC_SendData((uint8_t *)(ADC1_array_a), ((NUM_OF_MES) * 2 ));					// отправка буфера альтернативной структуры DMA по USB
	}	
}
