#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_adc.h"
#include "ADC_init.h"
#include "defines.h"
#include "MDR32F9Qx_rst_clk.h"

// Структуры для АЦП
ADC_InitTypeDef ADC_structure;
ADCx_InitTypeDef ADCx_structure;

// Структура для порта
extern PORT_InitTypeDef port_init_structure;

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
		NVIC->ISER[0] = (1<<ADC_IRQn);	// Регистр разрешения прерываний ISER

	// Сбрасываем настройки порта D
    PORT_DeInit(MDR_PORTD);

	// Конфигурируем выводы для АЦП 1 и 2
    port_init_structure.PORT_Pin   = PORT_Pin_0 | PORT_Pin_1;			    // АЦП 1 и 2 расположены на PD0 и PD1 (см. распиновку)
    port_init_structure.PORT_OE    = PORT_OE_IN;							          // Режим на вход
    port_init_structure.PORT_MODE  = PORT_MODE_ANALOG;					        // Аналоговый вход
    PORT_Init(MDR_PORTD, &port_init_structure);							          // Инициализация выводов заданной структурой
	
    // Настройка АЦП для осцилографа   
    ADC_DeInit();														                          // Сбросить все прежние настройки АЦП
    ADC_StructInit(&ADC_structure);												                    // Проинициализировать структуру стандартными значениями
	ADC_Init (&ADC_structure);													                          // Применить конфигурацию, занесенную в ADC_structure
    ADCx_StructInit (&ADCx_structure);											                    // Проинициализировать структуру для отдельного канала стандартными значениями
    ADCx_structure.ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;					      // Источник тактирования - ЦПУ (т.е. от HSE)
    ADCx_structure.ADC_SamplingMode     = ADC_SAMPLING_MODE_CYCLIC_CONV;		    // Режим работы (циклические преобразования, а не одиночное)
    ADCx_structure.ADC_ChannelSwitching = ADC_CH_SWITCHING_Enable;				      // Переключение каналов разрешено, АЦП 1 будет вссегда работать на PD0,// PD1
    ADCx_structure.ADC_ChannelNumber    = ADC_CH_ADC0;							            // Указываем канал АЦП 1 (ADC0 = АЦП 1, т.к. у Миландр он то первый, то нулевой)
    ADCx_structure.ADC_Channels         = (ADC_CH_ADC0_MSK | ADC_CH_ADC1_MSK);	// Маска для каналов 0 и 1 (АЦП 1 будет оцифровывать их поочередно)
    ADCx_structure.ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;				    // Опорное напряжение от внутреннего источника
    ADCx_structure.ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;			    // Выбираем неточный источник опорного напряжения
    ADCx_structure.ADC_Prescaler        = ADC_CLK_div_256;						          // Задаем скорость работы АЦП, ИМЕННО ЭТОЙ НАСТРОЙКОЙ ЗАДАЕТСЯ СКОРОСТЬ РАБОТЫ УСТРОЙСТВА
	ADCx_structure.ADC_DelayGo          = 0x2;									                  // Отложенный запуск, необходиим для нормальной работы
    ADC1_Init (&ADCx_structure);													                      // Применяем настройки к АЦП 1
    
    // Настройка АЦП для регулировки
    ADCx_structure.ADC_SamplingMode     = ADC_SAMPLING_MODE_SINGLE_CONV;		    // Режим работы (циклические преобразования, а не одиночное)
    ADCx_structure.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;				      // Переключение каналов разрешено, АЦП 1 будет вссегда работать на PD0,// PD1
    ADCx_structure.ADC_ChannelNumber    = ADC_CH_ADC0;
    ADCx_structure.ADC_Channels         = (ADC_CH_ADC0_MSK | ADC_CH_ADC1_MSK);	// Маска для каналов 0 и 1 (АЦП 1 будет оцифровывать их поочередно)
    ADCx_structure.ADC_Prescaler        = ADC_CLK_div_2048;						          // Задаем скорость работы АЦП, ИМЕННО ЭТОЙ НАСТРОЙКОЙ ЗАДАЕТСЯ СКОРОСТЬ РАБОТЫ УСТРОЙСТВА

    // Разрешаем прерывания от АЦП
//    ADC1_ITConfig((ADCx_IT_END_OF_CONVERSION), ENABLE);
}
