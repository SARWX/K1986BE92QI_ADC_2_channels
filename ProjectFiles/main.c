/**
  ******************************************************************************
  * @file    main.c
  * @author  ICV
  * @version V1.1.0
  * @date    19/10/2024
  * @brief   This file contains main logic of all project
  * ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
// Milandr SPL
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_usb_handlers.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_ssp.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_adc.h"
#include "MDR32F9Qx_dac.h"
#include "MDR32F9Qx_dma.h"
#include "MDR32F9Qx_timer.h"

// Стандартные библиотеки
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

// Собственные библиотеки
#include "dma.h"
#include "dac.h"
#include "adc.h"
#include "sys_clk.h"
#include "usb.h"
#include "command_sys_flex.h"
#include "spi.h"
#include "ili9341.h"
#include "ili9341_interface.h"
#include "delay.h"
#include "compress.h"

/* Макроподстановки --------------------------------------------------------------*/
#include "defines.h"
#include "pins.h"
/* Внешние переменные ------------------------------------------------------------*/
int command_recived = 0;		/* флаг получения команды */
int dac_mode = 0;				/* режим потоковой работы DAC */
char buffer[BUFFER_LENGTH];		/* буфер для получения USB команд */
extern char rec_buf[];			/* буфер для обработки USB команд*/
// char buffer_2[BUFFER_LENGTH];					// буфер для DAC alt данных

// массивы для АЦП
uint16_t main_array_for_ADC[NUM_OF_MES];		/* массив измерений АЦП для заполнения сновной структурой DMA */
uint16_t alternate_array_for_ADC[NUM_OF_MES];	/* массив измерений АЦП для заполнения альтернативной структурой DMA */

// элементы управления
uint16_t tuner = NUM_OF_MES;	/* управление разверткой */
uint16_t coordinate_x = 0;
uint16_t coordinate_y = 0;

// переменные для dac_mode
volatile enum dac_mode_state dac_mode_state;	/* Состояние DMA для ЦАПа в режиме dac_mode */
extern uint8_t main_array_for_DAC[];			/* массив для передачи в DAC основной структурой DMA */
extern uint8_t alternate_array_for_DAC[];		/* массив для передачи в DAC альтернативной структурой DMA */
/* -------------------------------------------------------------------------------*/

/** 
 * @brief This array of structures 
 * describes all used CS pins (for SPI)
 * 
 * for pinPhysNumber __-1 = NOTUSED__
 * for pinNumber __-1 = END__
 */
const struct spi_aux_pin spi_aux_pins[4] = {
	{1, Pin_SPI_CS_Display, Port_SPI_CS_Display},
	{1, Pin_SPI_CS_Touch, Port_SPI_CS_Display},
	// RESET & DC (currently not used)
	// {-1, Pin_DC_Display, Port_DC_Reset_Display},
	// {-1, Pin_Reset_Display, Port_DC_Reset_Display},
};

USB_Result test_usb(USB_EP_TypeDef EPx, uint8_t* Buffer, uint32_t Length)
{
    // Возвращаем успешный результат
    return USB_SUCCESS;
}

void pre_setup(void) 
{
	// Инициализируем контроллер прерывний (NVIC)
    SCB->AIRCR = AIRCR_SETTING;
    SCB->VTOR = VECTOR_TABLE_OFFSET;
    // Запрещаем все прерывания
    NVIC->ICPR[0] = WHOLE_WORD;	// Регистр сброса состояния ожидания для прерывания ICPR
    NVIC->ICER[0] = WHOLE_WORD;	// Регистр запрета прерываний IСER
}

void post_setup(void) 
{
	// Установим значение приоретета прерывания DMA
	NVIC_EnableIRQ(ADC_IRQn);
 	NVIC_EnableIRQ(DMA_IRQn);
	NVIC_SetPriority (DMA_IRQn, 1);
	NVIC_SetPriority (USB_IRQn, 0);
	// Разрешение работы DMA TIM2, ADC1
	DMA_Cmd(DMA_Channel_TIM2, ENABLE);
	DMA_Cmd(DMA_Channel_ADC1, ENABLE);
	// Включение АЦП
	ADC1_Cmd(ENABLE);
	ADC2_Cmd(ENABLE);
	// Запуск таймера
	TIMER_Cmd(MDR_TIMER2, ENABLE);
}

int main(void) 
{
	pre_setup();
	Setup_CPU_Clock(FAST_CONFIG);
	VCom_Configuration();
	Setup_ADC();
	Setup_DMA();
	USB_CDC_Init((uint8_t *)buffer, 1, SET);
	Setup_USB();		
	Setup_DAC();
	Setup_TIM2();
	Setup_DEMUX_for_DAC();

	Setup_SPI(spi_aux_pins, 2);
	
	post_setup();

	while (1) 
	{
		// Проверим, не ожидает ли исполнения команда
		if (command_recived == 1) 
		{
			// Замаскируем все каналы DMA
			MDR_DMA->CHNL_REQ_MASK_SET = WHOLE_WORD;
			command_recived = 0;
			if(execute_command(rec_buf) == 1)		// Если пришла команда "dac_mode",
			{
				dac_mode = 1;
				goto dac_mode;						// то переходим в другой основной цикл
			}
			// Почистим буфер
			for(int i = 0; i < BUFFER_LENGTH; i++) 
			{
				buffer[i] = 0;
			}
			// Снятие маскировки с DMA	
			MDR_DMA->CHNL_REQ_MASK_CLR = (
				1 << DMA_Channel_TIM2 | 
				1 << DMA_Channel_ADC1 | 
				1 << DMA_Channel_ADC2
				);
		}

		// 1 стадия - заполнение буфера, с использованием основной структуры DMA, параллельная передача буфера альтернативной по USB
		while (DMA_GetFlagStatus(DMA_Channel_ADC1, DMA_FLAG_CHNL_ALT) == 0) 						
			;	// ждем, когда DMA перейдет на альтернативную структуру
		DMA_CtrlInit(DMA_Channel_ADC1, DMA_CTRL_DATA_PRIMARY, &ADC1_primary_DMA_structure);			// реинициализируем основную структуру
		convert_to_8_bit((uint8_t *)main_array_for_ADC, NUM_OF_MES);
		USB_CDC_SendData((uint8_t *)main_array_for_ADC, NUM_OF_MES);								// отправка буфера основной структуры DMA по USB

		// 2 стадия - заполнение буфера, с использованием альтернативной структуры DMA, параллельная передача буфера основной по USB
		while (DMA_GetFlagStatus(DMA_Channel_ADC1, DMA_FLAG_CHNL_ALT) != 0)
			;	// ждем, когда DMA перейдет на основную структуру
		DMA_CtrlInit(DMA_Channel_ADC1, DMA_CTRL_DATA_ALTERNATE, &ADC1_alternate_DMA_structure);		// реинициализируем альтернативную структуру
		convert_to_8_bit((uint8_t *)alternate_array_for_ADC, NUM_OF_MES);
		USB_CDC_SendData((uint8_t *)alternate_array_for_ADC, NUM_OF_MES);							// отправка буфера альтернативной структуры DMA по USB
	}	

	dac_mode:
 	NVIC_DisableIRQ(DMA_IRQn);
	TIMER_Cmd(MDR_TIMER2, DISABLE);
	// Предустановка для работы в режиме dac_mode
	for(int i = 0; i < DAC_MODE_BUF_SIZE; i++)
	{
		main_array_for_DAC[i] = 100 * (i%2);
		alternate_array_for_DAC[i] = 100 * (i%2);
	}
	reconfig_TIM_dac_mode();
	reconfig_DMA_dac_mode();
	// Восстанавливаем работу DMA
	MDR_DMA->CHNL_REQ_MASK_CLR = (
		1 << DMA_Channel_TIM2 
		);
	TIMER_Cmd(MDR_TIMER2, ENABLE);
 	NVIC_EnableIRQ(DMA_IRQn);


	while (1)
	{
		// 1 - заполнение main
		while (dac_mode_state == main_state)
			;	// Ждем перехода на alt_state
		USB_Result result = USB_EP_doDataOut(USB_EP3, main_array_for_DAC, DAC_MODE_BUF_SIZE*2, test_usb);

		// 1 - заполнение alt
		while (dac_mode_state == alt_state)
			;	// Ждем перехода на main_state
		result = USB_EP_doDataOut(USB_EP3, alternate_array_for_DAC, DAC_MODE_BUF_SIZE*2, test_usb);
	}
}

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE main.c */
