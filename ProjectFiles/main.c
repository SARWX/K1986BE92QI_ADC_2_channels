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
#include "ili9341_interface.h"
#include "delay.h"
#include "compress.h"

/* Макроподстановки --------------------------------------------------------------*/
#include "defines.h"
/* Внешние переменные ------------------------------------------------------------*/
int command_recived = 0;
char buffer[BUFFER_LENGTH];
extern char rec_buf[];							// Массив в котором записана переданная команда
// массивы для АЦП
uint16_t main_array_for_ADC[NUM_OF_MES];		// Массив измерений АЦП для заполнения сновной структурой DMA
uint16_t alternate_array_for_ADC[NUM_OF_MES];	// Массив измерений АЦП для заполнения альтернативной структурой DMA
// элементы управления
uint16_t tuner = NUM_OF_MES;					// Управление разверткой
uint16_t coordinate_x = 0;
uint16_t coordinate_y = 0;
/* -------------------------------------------------------------------------------*/

int main(void) 
{
	Setup_CPU_Clock();
	VCom_Configuration();
	Setup_ADC();
	Setup_DMA();
//		test();			/// TETTSSSTTT 
	USB_CDC_Init((uint8_t *)buffer, 1, SET);
	Setup_USB();		
	set_sin_DAC_table(1000);
	Setup_DAC();
	Setup_SPI();
	Setup_ili9341();
	Setup_TIM2();
 
	// Включение АЦП и DMA для АЦП
	ADC1_Cmd (ENABLE);						// разрешаем работу ADC1
	ADC2_Cmd (ENABLE);						// разрешаем работу ADC2

// 	/* Main loop */
//	ili9341_setaddress(0,0,319,239);
	// Тест с отключением прерываний
	// __disable_irq();
	// NVIC_EnableIRQ(USB_IRQn);
// 	// Включить таймер
// 	TIMER_Cmd(MDR_TIMER2, ENABLE);








// // // TEST OF GUI
// ili9341_clear(BLACK);
// display_main_menu();

// // TRAP
// int row_num = 1;
// while (1)
// {
// 	// draw_arrow(320 - 48, 240 - 13 - 38, 1, GREEN);
// 	// draw_box(row_num++, BLUE);
// 	// if (row_num == 5)
// 	// 	row_num = 1;
// 	// draw_box(row_num, GREEN);
// 	// delay_ms(100);
// 	// draw_arrow(320 - 48, 240 - 13 - 38, 1, BLUE);
// 	// delay_ms(100);

// 	// Тест рисования
// 	ILI9341_TouchGetCoordinates(&coordinate_x, &coordinate_y);
// 	if ((coordinate_x * coordinate_y) != 0)
// 		draw_touch_cursor(coordinate_x, coordinate_y);
// }
	


// TEST
// execute_command("set 2.0 0.0 !");


	while (1) 
	{
		// Проверим, не ожидает ли исполнения команда
		if (command_recived == 1) 
		{
			// Надо приостановить работу АЦП
			ADC1_Cmd(DISABLE);
			command_recived = 0;
			execute_command(rec_buf);
			// Почистим буфер
			for(int i = 0; i < BUFFER_LENGTH; i++) 
			{
				buffer[i] = 0;
			}
			// Восстанавливаем работу АЦП
			ADC1_Cmd(ENABLE);
		}

		// Определим значение управляющего элемента и усредним 
		// tuner = (tuner + ((MDR_ADC->ADC2_RESULT >> 8) << 8)) / 2;
//		tuner = ((MDR_ADC->ADC2_RESULT >> 8) << 8);
		
		// 1 стадия - заполнение буфера, с использованием основной структуры DMA, параллельная передача буфера альтернативной по USB
		while (DMA_GetFlagStatus(DMA_Channel_ADC1, DMA_FLAG_CHNL_ALT) == 0) ;						// ждем, когда DMA перейдет на альтернативную структуру
		DMA_CtrlInit(DMA_Channel_ADC1, DMA_CTRL_DATA_PRIMARY, &ADC1_primary_DMA_structure);			// реинициализируем основную структуру
		convert_to_8_bit(main_array_for_ADC, NUM_OF_MES);
		USB_CDC_SendData((uint8_t *)main_array_for_ADC, NUM_OF_MES);					// отправка буфера основной структуры DMA по USB
	
		// {
		// 	display_signal((uint16_t *)main_array_for_ADC, NUM_OF_MES, 1, ((tuner >> 8)));
		// }

		// 2 стадия - заполнение буфера, с использованием альтернативной структуры DMA, параллельная передача буфера основной по USB
		while (DMA_GetFlagStatus(DMA_Channel_ADC1, DMA_FLAG_CHNL_ALT) != 0) ;						// ждем, когда DMA перейдет на основную структуру
		DMA_CtrlInit(DMA_Channel_ADC1, DMA_CTRL_DATA_ALTERNATE, &ADC1_alternate_DMA_structure);		// реинициализируем альтернативную структуру
		convert_to_8_bit(alternate_array_for_ADC, NUM_OF_MES);
		USB_CDC_SendData((uint8_t *)alternate_array_for_ADC, NUM_OF_MES );			// отправка буфера альтернативной структуры DMA по USB

		// {
		// 	display_signal((uint16_t *)alternate_array_for_ADC, NUM_OF_MES, 1, ((tuner >> 8)));
		// }
	}	
}
