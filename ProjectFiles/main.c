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
#include "DMA_init.h"
#include "DAC_init.h"
#include "ADC_init.h"
#include "sys_CLK_init.h"
#include "USB_init.h"
#include "command_system.h"
#include "SPI_init.h"
#include "ili9341.h"

/* Макроподстановки --------------------------------------------------------------*/
#include "defines.h"
/* Внешние переменные ------------------------------------------------------------*/
int command_recived = 0;
char buffer[BUFFER_LENGTH];
extern char rec_buf[];							// Массив в котором записана переданная команда
// массивы для АЦП
uint16_t main_array_for_ADC[NUM_OF_MES];		// Массив измерений АЦП для заполнения сновной структурой DMA
uint16_t alternate_array_for_ADC[NUM_OF_MES];	// Массив измерений АЦП для заполнения альтернативной структурой DMA

/* -------------------------------------------------------------------------------*/

// TESTS
uint32_t count_dysplay = 0;
uint32_t count_dma_interrupts = 0;

int main(void) 
{

	VCom_Configuration();

	count_dysplay++;
	/* CDC layer initialization */
	Setup_ADC();

	count_dysplay++;
	Setup_DMA();

	count_dysplay++;
//		test();			/// TETTSSSTTT
	USB_CDC_Init((uint8_t *)buffer, 1, SET);
					
	count_dysplay++;
	Setup_CPU_Clock();
	

	
	count_dysplay++;
	Setup_USB();		
	count_dysplay++;
	set_DAC_table(100);
	count_dysplay++;
	Setup_DAC();
	count_dysplay++;
//	Setup_TIM2();
	NVIC_DisableIRQ(DMA_IRQn);
	count_dysplay++;

	Setup_SPI();
	Setup_ili9341();

	count_dysplay++;

	count_dysplay++;
	// Включение АЦП и DMA для АЦП
	ADC1_Cmd (ENABLE);						// разрешаем работу ADC1
	count_dysplay++;
	DMA_Cmd(DMA_Channel_ADC1, ENABLE);		// разрешаем работу DMA с каналом ADC1
	count_dysplay++;
	// Включение DMA для ЦАП
	DMA_Cmd(DMA_Channel_TIM2, ENABLE);

	/* Main loop */
	ili9341_setaddress(0,0,319,239);
	count_dysplay++;
//	NVIC_DisableIRQ(USB_IRQn);
	NVIC_EnableIRQ(DMA_IRQn);
//	NVIC_DisableIRQ(Timer2_IRQn);
//	__disable_irq();
	count_dysplay++;
	while (1) 
	{
		if (command_recived == 1) 
		{
			ADC1_Cmd (DISABLE);
			command_recived = 0;
			execute_command(rec_buf);

			for(int i = 0; i < BUFFER_LENGTH; i++) 
			{
				buffer[i] = 0;
			}
			ADC1_Cmd(ENABLE);
		}
		count_dysplay++;
		// 1 стадия - заполнение буфера, с использованием основной структуры DMA, параллельная передача буфера альтернативной по USB
		while (DMA_GetFlagStatus(DMA_Channel_ADC1, DMA_FLAG_CHNL_ALT) == 0) ;					// ждем, когда DMA перейдет на альтернативную структуру
		DMA_CtrlInit(DMA_Channel_ADC1, DMA_CTRL_DATA_PRIMARY, &ADC1_primary_DMA_structure);		// реинициализируем основную структуру
		count_dysplay++;
//		 USB_CDC_SendData((uint8_t *)(main_array_for_ADC), ((NUM_OF_MES) * 2 ));					// отправка буфера основной структуры DMA по USB
		 count_dysplay++;
	
	//	ili9341_pushcolour(RED);
//		NVIC_DisableIRQ(DMA_IRQn);
		dysplay_points((uint16_t *)main_array_for_ADC, NUM_OF_MES, 0);
//		NVIC_EnableIRQ(DMA_IRQn);
		// 2 стадия - заполнение буфера, с использованием альтернативной структуры DMA, параллельная передача буфера основной по USB
		while (DMA_GetFlagStatus(DMA_Channel_ADC1, DMA_FLAG_CHNL_ALT) != 0) ;					// ждем, когда DMA перейдет на основную структуру
		count_dysplay++;
		DMA_CtrlInit(DMA_Channel_ADC1, DMA_CTRL_DATA_ALTERNATE, &ADC1_alternate_DMA_structure);	// реинициализируем альтернативную структуру
		count_dysplay++;
//		 USB_CDC_SendData((uint8_t *)(alternate_array_for_ADC), ((NUM_OF_MES) * 2 ));			// отправка буфера альтернативной структуры DMA по USB
		 count_dysplay++;	
		// ili9341_pushcolour(YELLOW);
//		NVIC_DisableIRQ(DMA_IRQn);
		dysplay_points((uint16_t *)alternate_array_for_ADC, NUM_OF_MES, NUM_OF_MES);
		NVIC_EnableIRQ(DMA_IRQn);
		count_dysplay += 2;
	//	NVIC_EnableIRQ(DMA_IRQn);
	}	
}
