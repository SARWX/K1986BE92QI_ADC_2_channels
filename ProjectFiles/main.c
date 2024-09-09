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
int dac_mode = 0;
char buffer[BUFFER_LENGTH];
char buffer_2[BUFFER_LENGTH];					// буфер для DAC alt данных
extern char rec_buf[];							// Массив в котором записана переданная команда
// extern char rec_buf_2[];						// Массив в котором alt данные для ЦАП
// массивы для АЦП
uint16_t main_array_for_ADC[NUM_OF_MES];		// Массив измерений АЦП для заполнения сновной структурой DMA
uint16_t alternate_array_for_ADC[NUM_OF_MES];	// Массив измерений АЦП для заполнения альтернативной структурой DMA
// элементы управления
uint16_t tuner = NUM_OF_MES;					// Управление разверткой
uint16_t coordinate_x = 0;
uint16_t coordinate_y = 0;
// переменные для dac_mode
enum dac_mode_state dac_mode_state;				// Состояние DMA для ЦАПа в режиме dac_mode
// extern uint16_t DAC_table[];					// Массив для DAC, в main он нужен для dac_mode
extern uint8_t main_array_for_DAC[];
extern uint8_t alternate_array_for_DAC[];
/* -------------------------------------------------------------------------------*/

void Test_diode(void)
{
		PORT_InitTypeDef GPIOInitStruct;
		RST_CLK_PCLKcmd (RST_CLK_PCLK_PORTC, ENABLE);
		GPIOInitStruct.PORT_Pin = PORT_Pin_2;
		GPIOInitStruct.PORT_OE = PORT_OE_OUT;
		GPIOInitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
		GPIOInitStruct.PORT_MODE = PORT_MODE_DIGITAL;
   		PORT_Init(MDR_PORTC, &GPIOInitStruct);
		
		// если не установилась частота, то будет светодиод мигать
	 	while (1)
		{
			PORT_SetBits(MDR_PORTC, PORT_Pin_2); 	// Включить светодиод
			delay_tick(16e6);
			PORT_ResetBits(MDR_PORTC, PORT_Pin_2); 	// Выключить светодиод
			delay_tick(16e6);
		}
}

int main(void) 
	{
	Setup_CPU_Clock();
//	 Test_diode();
	VCom_Configuration();
	Setup_ADC();
	Setup_DMA();
//		test();			/// TETTSSSTTT 
	USB_CDC_Init((uint8_t *)buffer, 1, SET);
	Setup_USB();		
	// set_sin_DAC_table(1000, 1);
	// set_sin_DAC_table(1000, 2);
	Setup_DAC();
	// Setup_SPI();
	// Setup_ili9341();
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
	


////////////////// TESTS ////////////////////
// execute_command("set 2.0 0.0 !");
// DAC_MODE test
	strcpy (rec_buf, "dac_mode");
	command_recived = 1;	
// DEMUX test
	// strcpy (rec_buf, "set 0.0 1.0 !");
	// command_recived = 1;	


	while (1) 
	{
		// Проверим, не ожидает ли исполнения команда
		if (command_recived == 1) 
		{
			// Надо приостановить работу АЦП
			ADC1_Cmd(DISABLE);
			command_recived = 0;
			if(execute_command(rec_buf) == 1)		// Если пришла команда "dac_mode", то переходим в другой основной цикл
			{
				dac_mode = 1;
				goto dac_mode;
			}
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

	dac_mode:
	MDR_DAC->DAC2_DATA = 0;
	// Предустановка для работы в режиме dac_mode
	for(int i = 0; i < DAC_MODE_BUF_SIZE; i++)
	{
		//	(((uint8_t *)DAC_table))[i] = i;		// НЕ i А 0, это для теста
		main_array_for_DAC[i] = 100 * (i%2);
		alternate_array_for_DAC[i] = 100 * (i%2);
	}
	reconfig_DMA_dac_mode();		// Задать настройки DMA для dac_mode
	// Теперь все готово, можно включить TIM2
 	NVIC_EnableIRQ(DMA_IRQn);
	TIMER_Cmd(MDR_TIMER2, ENABLE);
	USB_CDC_SetReceiveBuffer(main_array_for_DAC, DAC_MODE_BUF_SIZE);		// Данные из USB помещаются в buffer
	dac_mode_state = main_state;
	// основной цикл для dac_mode
	int test_transit = 0;
	while (1)
	{
		// MDR_DAC->DAC2_DATA = 0;
		// // 1 стадия - заполнение буфера, с использованием основной структуры DMA, параллельная передача буфера альтернативной по DAC
		// USB_CDC_SetReceiveBuffer(main_array_for_DAC, 256);		// Данные из USB помещаются в buffer
		// // USB_CDC_ReceiveStop();
		// // USB_CDC_ReceiveStart();
		// // USB_DeviceReset();

		// while(dac_mode_state == alt_state);							// Ждем когда альтернативный массив будет прочитан	
		// // test_transit++;
		// // 2 стадия - заполнение буфера, с использованием альтернативной структуры DMA, параллельная передача буфера основной по DAC
		// // USB_CDC_ReceiveStop();
		// USB_CDC_SetReceiveBuffer(alternate_array_for_DAC, 256);	// Данные из USB помещаются в buffer
		// // USB_CDC_ReceiveStart();
		// // USB_DeviceReset();
		// while(dac_mode_state == main_state);						// Ждем когда основной массив будет прочитан
		
			// while (DMA_GetFlagStatus(DMA_Channel_TIM2, DMA_FLAG_CHNL_ALT) != RESET) ;						// ждем, когда DMA перейдет на альтернативную структуру
			// DMA_CtrlInit(DMA_Channel_TIM2, DMA_CTRL_DATA_ALTERNATE, &TIM2_alternate_DMA_structure);	// реинициализируем альтернативную структуру
			// while (DMA_GetFlagStatus(DMA_Channel_TIM2, DMA_FLAG_CHNL_ALT) == RESET) ;						// ждем, когда DMA перейдет на альтернативную структуру
			// DMA_CtrlInit(DMA_Channel_TIM2, DMA_CTRL_DATA_PRIMARY, &TIM2_primary_DMA_structure);		// реинициализируем основную структуру
 
		// test_transit++;
	}
}
