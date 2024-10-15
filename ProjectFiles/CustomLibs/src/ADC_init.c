/**
  ******************************************************************************
  * @file    ADC_init.c
  * @author  ICV
  * @version V1.0.0
  * @date    08/05/2024
  * @brief   This file contains initialization of ADC.
  * ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_adc.h"
#include "ADC_init.h"
#include "defines.h"
#include "Command_system.h"
#include "MDR32F9Qx_rst_clk.h"
// #include "MDR32Fx.h"                     // НЕ НУЖНО ВКЛЮЧАТЬ СЮДА ТО, ЧТО УЖЕ ЕСТЬ В ЗАГОЛОВОЧНОМ ФАЙЛЕ

#define MIN_ADC_PRESCALER ADC_CLK_div_8
#define MAX_ADC_PRESCALER ADC_CLK_div_2048
#define ADC_PRESCALER_TO_INT(ADC_PRESCALER) (1 << ((int)(ADC_PRESCALER) >> ADC1_CFG_REG_DIVCLK_Pos))
#define INT_TO_ADC_PRESCALER(INT) ((ADCx_Prescaler)((__builtin_ctz(INT) << ADC1_CFG_REG_DIVCLK_Pos)))

#define DELAY_GO_TO_CLK_TICS(DELAY_GO) (28 + 1 + DELAY_GO)  // Минимум 29 тактов на преобразование, точное количество определяет ADCx_structure.ADC_DelayGo

// Структуры для АЦП
ADC_InitTypeDef ADC_structure;
ADCx_InitTypeDef ADCx_structure;

// Структура для порта
extern PORT_InitTypeDef port_init_structure;

/**
  * @brief  Init ADCs: 
  * programm uses 2 ADCs, 1 for transmiting data to USB (2 channels) 
  * and second for control functions.
  * @param  None
  * @retval None
  */
void Setup_ADC() 
{
	// Подключаем тактирование к блоку АЦП, портам A и C 
    RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_ADC), ENABLE);
    RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD), ENABLE);

	// Инициализируем контроллер прерывний (NVIC)
    SCB->AIRCR = AIRCR_SETTING;
    SCB->VTOR = VECTOR_TABLE_OFFSET;

    // Запрещаем все прерывания
    NVIC->ICPR[0] = WHOLE_WORD;			// Регистр сброса состояния ожидания для прерывания ICPR
    NVIC->ICER[0] = WHOLE_WORD;			// Регистр запрета прерываний IСER
	NVIC->ISER[0] = (1<<ADC_IRQn);	    // Регистр разрешения прерываний ISER

	// Сбрасываем настройки порта D
    PORT_DeInit(MDR_PORTD);

	// Конфигурируем выводы для АЦП 1 и 2
    port_init_structure.PORT_Pin   = PORT_Pin_0 | PORT_Pin_1;	// АЦП 1 и 2 расположены на PD0 и PD1 (см. распиновку)
    port_init_structure.PORT_OE    = PORT_OE_IN;                // Режим на вход
    port_init_structure.PORT_MODE  = PORT_MODE_ANALOG;		    // Аналоговый вход
    PORT_Init(MDR_PORTD, &port_init_structure);					// Инициализация выводов заданной структурой
	
    // Настройка АЦП для осцилографа   
    ADC_DeInit();														        // Сбросить все прежние настройки АЦП
    ADC_StructInit(&ADC_structure);											    // Проинициализировать структуру стандартными значениями
	ADC_Init (&ADC_structure);												    // Применить конфигурацию, занесенную в ADC_structure
    ADCx_StructInit (&ADCx_structure);                                          // Проинициализировать структуру для отдельного канала стандартными значениями
    ADCx_structure.ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;                 // Источник тактирования - ЦПУ (т.е. от HSE)
    ADCx_structure.ADC_SamplingMode     = ADC_SAMPLING_MODE_CYCLIC_CONV;	    // Режим работы (циклические преобразования, а не одиночное)
    ADCx_structure.ADC_ChannelSwitching = ADC_CH_SWITCHING_Enable;			    // Переключение каналов разрешено, АЦП 1 будет вссегда работать на PD0,// PD1
    // ADCx_structure.ADC_ChannelNumber    = ADC_CH_ADC0;					    // Указываем канал АЦП 1 (ADC0 = АЦП 1, т.к. у Миландр он то первый, то нулевой)
    ADCx_structure.ADC_Channels         = (ADC_CH_ADC0_MSK | ADC_CH_ADC1_MSK);	// Маска для каналов 0 и 1 (АЦП 1 будет оцифровывать их поочередно)
    ADCx_structure.ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;			    // Опорное напряжение от внутреннего источника
    ADCx_structure.ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;		    // Выбираем неточный источник опорного напряжения
    ADCx_structure.ADC_Prescaler        = MIN_ADC_PRESCALER;					    // Задаем скорость работы АЦП, ИМЕННО ЭТОЙ НАСТРОЙКОЙ ЗАДАЕТСЯ СКОРОСТЬ РАБОТЫ УСТРОЙСТВА
	ADCx_structure.ADC_DelayGo          = 0x3;								    // сколько тактов на преобразование
    ADC1_Init (&ADCx_structure);											    // Применяем настройки к АЦП 1
    
    // Настройка АЦП для регулировки
    ADCx_structure.ADC_SamplingMode     = ADC_SAMPLING_MODE_CYCLIC_CONV;		    // Режим работы (циклические преобразования, а не одиночное)
    ADCx_structure.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;				      // Переключение каналов разрешено, АЦП 1 будет вссегда работать на PD0,// PD1
    ADCx_structure.ADC_ChannelNumber    = ADC_CH_ADC1;
   // ADCx_structure.ADC_Channels         = (ADC_CH_ADC1_MSK);	// Маска для каналов 0 и 1 (АЦП 1 будет оцифровывать их поочередно)
    ADCx_structure.ADC_Prescaler        = ADC_CLK_div_2048;						          // Задаем скорость работы АЦП, ИМЕННО ЭТОЙ НАСТРОЙКОЙ ЗАДАЕТСЯ СКОРОСТЬ РАБОТЫ УСТРОЙСТВА
    ADC2_Init (&ADCx_structure);													                      // Применяем настройки к АЦП 2


    // Разрешаем прерывания от АЦП
//    ADC1_ITConfig((ADCx_IT_END_OF_CONVERSION), ENABLE);
}

/**
  * @brief  Changes number of active channels in ADC 
  * You may want to increase speed twice 
  * in this case use 1 channel
  * @param  None
  * @retval None
  */
void change_adc_chan_num(int num_adc_chan)
{
    if (num_adc_chan == 1)
    {
        ADCx_structure.ADC_Prescaler        = MIN_ADC_PRESCALER;					    // Задаем скорость работы АЦП, ИМЕННО ЭТОЙ НАСТРОЙКОЙ ЗАДАЕТСЯ СКОРОСТЬ РАБОТЫ УСТРОЙСТВА
        ADCx_structure.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable; // Переключение каналов разрешено, АЦП 1 будет вссегда работать на PD0,// PD1
        ADCx_structure.ADC_Channels         = (ADC_CH_ADC0_MSK);	      // Маска для каналов 0 и 1 (АЦП 1 будет оцифровывать их поочередно)
    }
    else
    {
        ADCx_structure.ADC_Prescaler        = MIN_ADC_PRESCALER;					    // Задаем скорость работы АЦП, ИМЕННО ЭТОЙ НАСТРОЙКОЙ ЗАДАЕТСЯ СКОРОСТЬ РАБОТЫ УСТРОЙСТВА
        ADCx_structure.ADC_ChannelSwitching = ADC_CH_SWITCHING_Enable;			        // Переключение каналов разрешено, АЦП 1 будет вссегда работать на PD0,// PD1
        ADCx_structure.ADC_Channels         = (ADC_CH_ADC0_MSK | ADC_CH_ADC1_MSK);	// Маска для каналов 0 и 1 (АЦП 1 будет оцифровывать их поочередно)
    }
    ADC1_Init (&ADCx_structure);  // Применяем настройки к АЦП 1
}

/**
  * @brief Reconfigures the ADC clock based on the input frequency and mode.
  * This function calculates the required ADC prescaler to achieve the desired
  * frequency based on the input frequency and the number of ADC channels
  * active in the specified mode. The ADC prescaler is adjusted accordingly.
  * @param input_freq The desired ADC frequency in Hz.
  * @param mode The operating mode setting for the ADC, which determines the 
  *             number of active ADC channels.
  * @retval ErrorStatus 
  *         - SUCCESS if the ADC frequency is successfully set; 
  *         - ERROR if the requested frequency cannot be achieved.
  */
ErrorStatus reconfig_ADC_clock(uint32_t input_freq, enum mode_setting mode)
{
    ADC1_Cmd(DISABLE);
    ErrorStatus new_freq_set = ERROR;
    // 1 - вычислить границы
    static const int min_prescaler = ADC_PRESCALER_TO_INT(MIN_ADC_PRESCALER);
    static const int max_prescaler = ADC_PRESCALER_TO_INT(MAX_ADC_PRESCALER);
    int conversion_ticks = DELAY_GO_TO_CLK_TICS(ADCx_structure.ADC_DelayGo);
    uint32_t max_adc_freq = (HSE_FREQ * CPU_PLL) / 
        (min_prescaler * conversion_ticks);
    uint32_t min_adc_freq = (HSE_FREQ * CPU_PLL) / 
        (max_prescaler * conversion_ticks);
    // 2 - узнать сколько каналов задействовано в текущем режиме
    int num_of_adc_channels = (((mode >> 1) & 0x1) + 1);
    // 3 - вычислить требуемую частоту
    uint32_t req_freq = input_freq * num_of_adc_channels;
    // 4 - попытаться установить частоту:
    for(int prescaler = max_prescaler; prescaler >= min_prescaler; prescaler /= 2)
    {
        if (((max_adc_freq * min_prescaler) / prescaler) == req_freq)
        {
            ADCx_structure.ADC_Prescaler = INT_TO_ADC_PRESCALER(prescaler);
            ADC1_Init (&ADCx_structure);  // Применяем настройки к АЦП 1
            new_freq_set = SUCCESS;
        }
    }
    ADC1_Cmd(ENABLE);
    return(new_freq_set);  
}
/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE ADC_init.c */