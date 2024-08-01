/**
  ******************************************************************************
  * @file    DAC_init.c
  * @author  ICV
  * @version V1.0.0
  * @date    08/05/2024
  * @brief   This file contains initialization of DAC, TIM2
  * and set_sin_DAC_table() function for initializing table of 
  * values for DAC with sinusoid.
  * ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_dac.h"
#include "MDR32F9Qx_timer.h"
#include "MDR32F9Qx_dma.h"
#include "DAC_init.h"
#include "defines.h"
#include <math.h>

// Переменные и массивы для ЦАП
int dac_inc_dec = 1;
int cur_dac_val = 0;

// Счетчик для ЦАП
int dac_cnt = 0;
uint16_t DAC_table[SIN_RES];

// Внешние структуры DMA
extern DMA_CtrlDataInitTypeDef TIM2_primary_DMA_structure;
extern DMA_CtrlDataInitTypeDef TIM2_alternate_DMA_structure;

// Структура для порта
extern PORT_InitTypeDef port_init_structure;
PORT_InitTypeDef PortInitStructure;

// Структура для таймера
TIMER_CntInitTypeDef Cnt_sTim2;
TIMER_ChnInitTypeDef TimerChnInitStructure;
TIMER_ChnOutInitTypeDef TimerChnOutInitStructure;

/**
  * @brief  Init DAC: 
  * Setup and enable DAC
  * @param  None
  * @retval None
  */
void Setup_DAC() 
{
	// Подключаем тактирование к блоку ЦАП, и порту E 
    RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_DAC), ENABLE);
    RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTE), ENABLE);

	// Сбрасываем настройки порта E
    PORT_DeInit(MDR_PORTE);
	
	// Конфигурируем выводы для ЦАП
    port_init_structure.PORT_Pin   = PORT_Pin_0;				//     PE9
    port_init_structure.PORT_OE    = PORT_OE_IN;				// Режим на вход
    port_init_structure.PORT_MODE  = PORT_MODE_ANALOG;			// Аналоговый вход (согласно спецификации)
    PORT_Init(MDR_PORTE, &port_init_structure);					// Инициализация выводов заданной структурой	
	
	DAC_DeInit();												// Сбросить настройки ЦАП
	// Настройка ЦАП 1
	DAC1_Init(DAC1_AVCC);										// AVcc - опорное напряжение
	DAC1_Cmd(ENABLE);
	// Настройка ЦАП 2
	DAC2_Init(DAC2_AVCC);										// AVcc - опорное напряжение
	DAC2_Cmd(ENABLE);			
}

/**
  * @brief  Init IIM2: 
  * Configure TIM2 frequence, also function configures
  * PE1 and PE2 to work as demultiplexing control outputs
  * at the end function enables timer
  * @param  None
  * @retval None
  */
void Setup_TIM2() 
{
	RST_CLK_PCLKcmd((RST_CLK_PCLK_TIMER2), ENABLE);
	TIMER_DeInit(MDR_TIMER2);
	TIMER_BRGInit(MDR_TIMER2, TIMER_HCLKdiv1);			// HCLK = 16 * 7 = 112 MHz
														// 112 / 4 = 28 MHz
														// Тактирование АЦП у нас 500 kHz, поэтому такую же частоту зададим и в ЦАП

	// Заполним структуру для TIM2
	TIMER_CntStructInit(&Cnt_sTim2);
	Cnt_sTim2.TIMER_CounterMode = TIMER_CntMode_ClkFixedDir;			// Счет без направления изменения счета
	Cnt_sTim2.TIMER_CounterDirection = TIMER_CntDir_Up;					// Счет в сторону увеличения
	// Cnt_sTim2.TIMER_EventSource = TIMER_EvSrc_TM2; 					// Событие по достижении TIM2 значения ARR
	Cnt_sTim2.TIMER_FilterSampling = TIMER_FDTS_TIMER_CLK_div_2;		// Вспомогательная частота для фильтра в 4 раза меньше основной
	Cnt_sTim2.TIMER_ARR_UpdateMode = TIMER_ARR_Update_Immediately;		// Изменение ARR таймера по переполнению
	Cnt_sTim2.TIMER_IniCounter = 0;										// Инициализационное значение таймера
	Cnt_sTim2.TIMER_Prescaler = PRESCALER_T2;							// делим на 12:  112 MHz / 4 / 12 
	Cnt_sTim2.TIMER_Period = PERIOD_T2 - 1;								// Значение ARR делим на 10:  112 MHz / 4 / 12 / 10
																		// Итоговая частота ЦАПа будет 250 кГц
	
	TIMER_CntInit(MDR_TIMER2, &Cnt_sTim2);


	// Сконфигурируем пин PE2 и PE1 для управления демультиплексором
	RST_CLK_PCLKcmd (RST_CLK_PCLK_PORTE | RST_CLK_PCLK_TIMER2, ENABLE);
	PORT_StructInit(&PortInitStructure);
	PortInitStructure.PORT_FUNC = PORT_FUNC_ALTER;
	PortInitStructure.PORT_OE = PORT_OE_OUT;
	PortInitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PortInitStructure.PORT_Pin = (PORT_Pin_2 | PORT_Pin_1);		// PE1 и PE2
	PortInitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_Init (MDR_PORTE, &PortInitStructure);
 
	// Сконфигурируем управление демультиплексором
	TIMER_ChnStructInit (&TimerChnInitStructure);
	TimerChnInitStructure.TIMER_CH_Number = TIMER_CHANNEL3;					// PE2 - 3 канал альтернативная функция (прямой канал)
	TimerChnInitStructure.TIMER_CH_Mode = TIMER_CH_MODE_PWM;
	TimerChnInitStructure.TIMER_CH_REF_Format = TIMER_CH_REF_Format3;
	TIMER_ChnInit (MDR_TIMER2, &TimerChnInitStructure);
	TimerChnInitStructure.TIMER_CH_Number = TIMER_CHANNEL1;					// PE1 - 1 канал альтернативная функция (инвертированный канал)
	TIMER_ChnInit (MDR_TIMER2, &TimerChnInitStructure);
	//
	TIMER_ChnOutStructInit (&TimerChnOutInitStructure);
	TimerChnOutInitStructure.TIMER_CH_Number = TIMER_CHANNEL3;
	TimerChnOutInitStructure.TIMER_CH_DirOut_Polarity =
	TIMER_CHOPolarity_NonInverted;
	TimerChnOutInitStructure.TIMER_CH_DirOut_Source = TIMER_CH_OutSrc_REF;
	TimerChnOutInitStructure.TIMER_CH_DirOut_Mode = TIMER_CH_OutMode_Output;
	TimerChnOutInitStructure.TIMER_CH_NegOut_Polarity =
	TIMER_CHOPolarity_NonInverted;
	TimerChnOutInitStructure.TIMER_CH_NegOut_Source = TIMER_CH_OutSrc_REF;
	TimerChnOutInitStructure.TIMER_CH_NegOut_Mode = TIMER_CH_OutMode_Output;
	TIMER_ChnOutInit (MDR_TIMER2, &TimerChnOutInitStructure);
	// Копируем конфигурацию для канала 1 (PE1)
	TimerChnOutInitStructure.TIMER_CH_Number = TIMER_CHANNEL1;
	TIMER_ChnOutInit (MDR_TIMER2, &TimerChnOutInitStructure);
	//NVIC_EnableIRQ(Timer2_IRQn);
	TIMER_DMACmd(MDR_TIMER2, TIMER_STATUS_CNT_ARR, ENABLE);
	
	// Включить таймер
	TIMER_Cmd(MDR_TIMER2, ENABLE);

	TIMER_SetChnCompare (MDR_TIMER2, TIMER_CHANNEL3, 5);	// 4
	TIMER_SetChnCompare (MDR_TIMER2, TIMER_CHANNEL1, 9);	// 10
	
}

/**
  * @brief  Init DAC: 
  * This function set DAC table so that DAC will give us
  * sinusoid with specified frequence.
  * @param  int
  * @retval None
  */
void set_sin_DAC_table(int freq) 
{
	freq = (int)((float)freq * CORRECTION_FACTOR); 	// Поправочный коэффициент
	int tics = (DISCRET_FREQ / freq);				// Сколько тиков таймера отвести на период синусоиды с частотой freq
	int divider = 1;								
	while(tics > SIN_RES)  							// Размер DAC_table ограничен SIN_RES
	{
		divider *= 2;								// Будем удваивать период таймера (разрешение будет падать) 
		tics /= 2;									// Будем делить пополам количество точек для записи в DAC_table
	}
	MDR_TIMER2->ARR = (PERIOD_T2 * divider - 1);	// Установить новый период таймера

	double angle_inc = (6.28318 / tics);			// Шаг таблицы в радианах
	for (int i = 0; i < (tics); i++)  
	{
		DAC_table[i] = (int) (sin(i*angle_inc) * SIN_AMPLITUDE) + SIN_MEDIUM_LINE;	// Вычисляем значение sin для i, с учетом средней линии
	}
	DAC_table[0] = SIN_MEDIUM_LINE;													// Первое значение sin - это средняя линия 
	DAC_table[tics - 1] = SIN_MEDIUM_LINE;											// Последнее значение sin - это средняя линия

	TIM2_primary_DMA_structure.DMA_CycleSize = (tics);								// Сколько измерений (DMA передач) содержит 1 DMA цикл
	TIM2_alternate_DMA_structure.DMA_CycleSize = (tics);							// Сколько измерений (DMA передач) содержит 1 DMA цикл
}

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE DAC_init.c */