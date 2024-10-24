/**
  ******************************************************************************
  * @file    DAC_init.c
  * @author  ICV
  * @version V1.1.0
  * @date    19/10/2024
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

// Таблица для периодических  сигналов
uint16_t DAC_table[SIN_RES * 2];

// Внешние структуры DMA
extern DMA_CtrlDataInitTypeDef TIM2_primary_DMA_structure;
extern DMA_CtrlDataInitTypeDef TIM2_alternate_DMA_structure;

/**
  * @brief  Init DAC: 
  * Setup and enable DAC
  * @param  None
  * @retval None
  */
void Setup_DAC(void) 
{
	// Подключаем тактирование к блоку ЦАП, и порту E 
    RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_DAC), ENABLE);
    RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTE), ENABLE);
	// Сбрасываем настройки порта E
    PORT_DeInit(MDR_PORTE);
	// Конфигурируем выводы для ЦАП
	PORT_InitTypeDef port_struct_DAC;
    PORT_StructInit(&port_struct_DAC);
    port_struct_DAC.PORT_Pin   = PORT_Pin_0;		// PE0
    port_struct_DAC.PORT_OE    = PORT_OE_IN;		// Режим на вход
    port_struct_DAC.PORT_MODE  = PORT_MODE_ANALOG;	// Аналоговый вход (согласно спецификации)
    PORT_Init(MDR_PORTE, &port_struct_DAC);			// Инициализация выводов заданной структурой	
	DAC_DeInit();									// Сбросить настройки ЦАП
	// Настройка ЦАП 1
	DAC1_Init(DAC1_AVCC);							// AVcc - опорное напряжение
	DAC1_Cmd(ENABLE);
	// Настройка ЦАП 2
	DAC2_Init(DAC2_AVCC);							// AVcc - опорное напряжение
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
void Setup_TIM2(void) 
{
	RST_CLK_PCLKcmd((RST_CLK_PCLK_TIMER2), ENABLE);
	TIMER_DeInit(MDR_TIMER2);
	TIMER_BRGInit(MDR_TIMER2, TIMER_HCLKdiv1);		// Предделитель для TIM2
	// Заполним структуру для TIM2
	TIMER_CntInitTypeDef TIM2_cnt_struct;	
	TIMER_CntStructInit(&TIM2_cnt_struct);
	TIM2_cnt_struct.TIMER_CounterMode = TIMER_CntMode_ClkFixedDir;			// Счет без направления изменения счета
	TIM2_cnt_struct.TIMER_CounterDirection = TIMER_CntDir_Up;				// Счет в сторону увеличения
	TIM2_cnt_struct.TIMER_FilterSampling = TIMER_FDTS_TIMER_CLK_div_2;		// Вспомогательная частота для фильтра в 4 раза меньше основной
	TIM2_cnt_struct.TIMER_ARR_UpdateMode = TIMER_ARR_Update_Immediately;	// Изменение ARR таймера по переполнению
	TIM2_cnt_struct.TIMER_IniCounter = 0;									// Инициализационное значение таймера
	TIM2_cnt_struct.TIMER_Prescaler = PRESCALER_T2;							// делим на PRESCALER_T2:  HSE_FREQ * CPU_PLL / (CPU_DIV * PRESCALER_T2)
	TIM2_cnt_struct.TIMER_Period = PERIOD_T2;								// Значение ARR (делим частоту еще на PERIOD_T2)
	TIMER_CntInit(MDR_TIMER2, &TIM2_cnt_struct);	// Итоговая частота ЦАПа = HSE_FREQ * CPU_PLL / (CPU_DIV * PRESCALER_T2 * PERIOD_T2)
	// Включить таймер
	TIMER_Cmd(MDR_TIMER2, ENABLE);
	TIMER_SetChnCompare (MDR_TIMER2, TIMER_CHANNEL3, 4);	// 4		PE2
	TIMER_SetChnCompare (MDR_TIMER2, TIMER_CHANNEL1, 10);	// 10		PE1
}

/**
  * @brief  Init ports for DEMUX control: 
  * Configures ports and TIM2 channels
  * to generate signals for demultiplexer
  * @param  None
  * @retval None
  */
void Setup_DEMUX_for_DAC(void) 
{
	// Сконфигурируем пин PE2 и PE1 для управления демультиплексором
	RST_CLK_PCLKcmd (RST_CLK_PCLK_PORTE | RST_CLK_PCLK_TIMER2, ENABLE);
	PORT_InitTypeDef port_struct_DEMUX;
    PORT_StructInit(&port_struct_DEMUX);
	PORT_StructInit(&port_struct_DEMUX);
	port_struct_DEMUX.PORT_FUNC = PORT_FUNC_ALTER;
	port_struct_DEMUX.PORT_OE = PORT_OE_OUT;
	port_struct_DEMUX.PORT_MODE = PORT_MODE_DIGITAL;
	port_struct_DEMUX.PORT_Pin = (PORT_Pin_2 | PORT_Pin_1);		// PE1 и PE2
	port_struct_DEMUX.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_Init (MDR_PORTE, &port_struct_DEMUX);
	// Сконфигурируем управление демультиплексором
	// Общие настройки каналов
	TIMER_ChnInitTypeDef TIM2_chn_init_struct;
	TIMER_ChnStructInit (&TIM2_chn_init_struct);
	TIM2_chn_init_struct.TIMER_CH_Number = TIMER_CHANNEL3;				// PE2 - 3 канал альтернативная функция (прямой канал)
	TIM2_chn_init_struct.TIMER_CH_Mode = TIMER_CH_MODE_PWM;
	TIM2_chn_init_struct.TIMER_CH_REF_Format = TIMER_CH_REF_Format3;
	TIMER_ChnInit (MDR_TIMER2, &TIM2_chn_init_struct);
	TIM2_chn_init_struct.TIMER_CH_Number = TIMER_CHANNEL1;				// PE1 - 1 канал альтернативная функция (инвертированный канал)
	TIMER_ChnInit (MDR_TIMER2, &TIM2_chn_init_struct);
	// Настройка выходных сигналов
	TIMER_ChnOutInitTypeDef TIM2_chn_out_init_struct;
	TIMER_ChnOutStructInit (&TIM2_chn_out_init_struct);
	TIM2_chn_out_init_struct.TIMER_CH_Number = TIMER_CHANNEL3;
	TIM2_chn_out_init_struct.TIMER_CH_DirOut_Polarity =
	TIMER_CHOPolarity_NonInverted;
	TIM2_chn_out_init_struct.TIMER_CH_DirOut_Source = TIMER_CH_OutSrc_REF;
	TIM2_chn_out_init_struct.TIMER_CH_DirOut_Mode = TIMER_CH_OutMode_Output;
	TIM2_chn_out_init_struct.TIMER_CH_NegOut_Polarity =
	TIMER_CHOPolarity_NonInverted;
	TIM2_chn_out_init_struct.TIMER_CH_NegOut_Source = TIMER_CH_OutSrc_REF;
	TIM2_chn_out_init_struct.TIMER_CH_NegOut_Mode = TIMER_CH_OutMode_Output;
	TIMER_ChnOutInit (MDR_TIMER2, &TIM2_chn_out_init_struct);
	// Копируем конфигурацию для канала 1 (PE1)
	TIM2_chn_out_init_struct.TIMER_CH_Number = TIMER_CHANNEL1;
	TIMER_ChnOutInit (MDR_TIMER2, &TIM2_chn_out_init_struct);
	TIMER_DMACmd(MDR_TIMER2, TIMER_STATUS_CNT_ARR, ENABLE);
	// Включим демультиплексор PE7 = 0 (0 = ON)
	PORT_InitTypeDef port_struct_DAC_DEMUX;
    PORT_StructInit(&port_struct_DAC_DEMUX);
	port_struct_DAC_DEMUX.PORT_Pin = PORT_Pin_7;
	port_struct_DAC_DEMUX.PORT_OE = PORT_OE_OUT;
	port_struct_DAC_DEMUX.PORT_SPEED = PORT_SPEED_MAXFAST;
	port_struct_DAC_DEMUX.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_Init(MDR_PORTE, &port_struct_DAC_DEMUX);
	PORT_ResetBits(MDR_PORTE, PORT_Pin_7); 	// Включить демультиплексор
}

/**
  * @brief  Init DAC: 
  * This function set DAC table so that DAC will give us
  * sinusoid with specified frequence.
  * @param  freq - frequency of sinusoid
  * @param  chan - DAC channel (may be 1 or 2)
  * @retval None
  */
void set_sin_DAC_table(int freq, int chan) 
{
	chan--;											// Приведем chan к 0 или 1
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
		DAC_table[(i * 2 + (chan - 1))] = 
			(int)(sin(i * angle_inc) * SIN_AMPLITUDE) +	// Вычисляем значение sin для i,
			SIN_MEDIUM_LINE;							// с учетом средней линии
	}
	DAC_table[0] = SIN_MEDIUM_LINE;			// Первое значение sin - это средняя линия 
	DAC_table[tics - 1] = SIN_MEDIUM_LINE;	// Последнее значение sin - это средняя линия

	TIM2_primary_DMA_structure.DMA_CycleSize = (tics*2);	// Сколько измерений (DMA передач) содержит 1 DMA цикл
	TIM2_alternate_DMA_structure.DMA_CycleSize = (tics*2);	// Сколько измерений (DMA передач) содержит 1 DMA цикл
}

/**
  * @brief  Changes total number of DAC channels:
  * Configures DEMUX ports
  * switch control ports: 2 DAC channels
  * const control ports: 1 DAC channel
  * @param  num_dac_chan - desired numbe of channels
  * @retval None
  */
void change_dac_chan_num(int num_dac_chan)
{
	PORT_InitTypeDef port_struct_DEMUX;
    PORT_StructInit(&port_struct_DEMUX);
	if (num_dac_chan == 1)
	{
		port_struct_DEMUX.PORT_FUNC = PORT_FUNC_PORT;
		port_struct_DEMUX.PORT_OE = PORT_OE_OUT;
		port_struct_DEMUX.PORT_MODE = PORT_MODE_DIGITAL;
		port_struct_DEMUX.PORT_Pin = (PORT_Pin_2 | PORT_Pin_1);	// PE1 и PE2
		port_struct_DEMUX.PORT_SPEED = PORT_SPEED_SLOW;
		PORT_Init (MDR_PORTE, &port_struct_DEMUX);
		// Задаем комбинацию для канала
		PORT_SetBits(MDR_PORTE, PORT_Pin_2 | PORT_Pin_1); 	// 1 1
	}
	else
	{
		port_struct_DEMUX.PORT_FUNC = PORT_FUNC_ALTER;
		port_struct_DEMUX.PORT_OE = PORT_OE_OUT;
		port_struct_DEMUX.PORT_MODE = PORT_MODE_DIGITAL;
		port_struct_DEMUX.PORT_Pin = (PORT_Pin_2 | PORT_Pin_1);	// PE1 и PE2
		port_struct_DEMUX.PORT_SPEED = PORT_SPEED_MAXFAST;
		PORT_Init (MDR_PORTE, &port_struct_DEMUX);
	}
}

/**
  * @brief  Reconfigs timer for dac_mode:
  * checks if current TIM2 frequency is
  * ok for dac_mode, if it is, just resets
  * counter, if not aditionaly lower TIM2 freq 
  * @param  None
  * @retval None
  */
void reconfig_TIM_dac_mode(void)
{
	// Проверить надо ли занижать частоту
	int period = TIMER_GetCntAutoreload(MDR_TIMER2);
	int prescaler = TIMER_GetCntPrescaler(MDR_TIMER2);
	if ((period * prescaler) < (PRESCALER_T2_DAC_MODE * PERIOD_T2))
	{
		TIMER_SetCntPrescaler(MDR_TIMER2, PRESCALER_T2_DAC_MODE);
		TIMER_SetCntAutoreload(MDR_TIMER2, PERIOD_T2);
	}
	// Сбросить таймер (надо, чтобы каналы демультиплесора
	// всегда однозначно соотносились с порядковыми номерами
	// индексов в массивах)
	MDR_TIMER2->CNT = 0;	
}

/**
  * @brief  Set desired freq for DAC:
  * counts combination of prescaler and
  * period of TIM2 to reach desired 
  * frequency, changes theese parameters
  * @param  None
  * @retval None
  */
ErrorStatus reconfig_DAC_clock(uint32_t input_freq, enum mode_setting mode)
{
	ErrorStatus new_freq_set = ERROR;
    // 1 - вычислить границы
	static const int y = PRESCALER_T2 * PERIOD_T2;
	static const int min_dac_freq = 1;
	static const int max_dac_freq = HSE_FREQ * CPU_PLL / y;
	
	// 2 - узнать сколько каналов задействовано в текущем режиме
    int num_of_dac_channels = ((mode & 0x1) + 1);

	// 3 - вычислить требуемую частоту
	int req_freq = input_freq * num_of_dac_channels;

	// 4 - Найти результирующую комбинацию 
	int x = (int)(HSE_FREQ * CPU_PLL / req_freq);

	// 5 - проверить, что частота не выйдет за максимум
	x = x >= y ? x : y; 

	// 6 - задаим переменные параметры
	int tim_period = PERIOD_T2;
	int tim_prescaler = PRESCALER_T2;

	// 7 - найдем значение периода, кратное требуемой частоте
	while(tim_period <= x)
	{
		if((x % tim_period) == 0) 
		{
			tim_prescaler = (int)(x / tim_period);

			TIMER_SetCntPrescaler(MDR_TIMER2, tim_prescaler);
			TIMER_SetCntAutoreload(MDR_TIMER2, tim_period);
			
			new_freq_set = SUCCESS;
			break;
		}
		else
		{
			tim_period++;
		}
	}
	return(new_freq_set);
}

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE DAC_init.c */