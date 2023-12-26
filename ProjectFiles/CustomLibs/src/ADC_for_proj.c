#include "ADC_for_proj.h"
#include "MDR32F9Qx_rst_clk.h"
#include "defines_for_proj.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_adc.h"

// Структуры для АЦП
ADC_InitTypeDef sADC;
ADCx_InitTypeDef sADCx;

// Структура для порта
extern PORT_InitTypeDef PORT_InitStructure;

void SetupADC() 
{
		// Подключаем тактирование к блоку АЦП, портам A и C 
    RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_ADC), ENABLE);
    RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD), ENABLE);
	
		// Инициализируем контроллер прерывний (NVIC)
    SCB->AIRCR = AIRCR_SETTING;
    SCB->VTOR = VECTOR_TABLE_OFFSET;
	
    // Запрещаем все прерывания
    NVIC->ICPR[0] = WHOLE_WORD;
    NVIC->ICER[0] = WHOLE_WORD;
		NVIC->ISER[0] = (1<<ADC_IRQn);
	
		// Сбрасываем настройки порта D
    PORT_DeInit(MDR_PORTD);
	
		// Конфигурируем выводы для АЦП 1 и 2
    PORT_InitStructure.PORT_Pin   = PORT_Pin_0 | PORT_Pin_1;					// АЦП 1 и 2 расположены на PD0 и PD1 (см. распиновку)
    PORT_InitStructure.PORT_OE    = PORT_OE_IN;												// Режим на вход
    PORT_InitStructure.PORT_MODE  = PORT_MODE_ANALOG;									// Аналоговый вход
    PORT_Init(MDR_PORTD, &PORT_InitStructure);												// Инициализация выводов заданной структурой
		
		// Настройка АЦП
    ADC_DeInit();																											// Сбросить все прежние настройки АЦП
    ADC_StructInit(&sADC);																						// Проинициализировать структуру стандартными значениями
		ADC_Init (&sADC);																									// Применить конфигурацию, занесенную в sADC
    ADCx_StructInit (&sADCx);																					// Проинициализировать структуру для отдельного канала стандартными значениями
    sADCx.ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;								// Источник тактирования - ЦПУ (т.е. от HSE)
    sADCx.ADC_SamplingMode     = ADC_SAMPLING_MODE_CYCLIC_CONV;				// Режим работы (циклические преобразования, а не одиночное)
    sADCx.ADC_ChannelSwitching = ADC_CH_SWITCHING_Enable;							// Переключение каналов разрешено, АЦП 1 будет вссегда работать на PD0,// PD1
    sADCx.ADC_ChannelNumber    = ADC_CH_ADC0;													// Указываем канал АЦП 1 (ADC0 = АЦП 1, т.к. у Миландр он то первый, то нулевой)
    sADCx.ADC_Channels         = (ADC_CH_ADC0_MSK | ADC_CH_ADC1_MSK);	// Маска для каналов 0 и 1 (АЦП 1 будет оцифровывать их поочередно)
    sADCx.ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;						// Опорное напряжение от внутреннего источника
    sADCx.ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;					// Выбираем неточный источник опорного напряжения
    sADCx.ADC_Prescaler        = ADC_CLK_div_32;											// Задаем скорость работы АЦП, ИМЕННО ЭТОЙ НАСТРОЙКОЙ ЗАДАЕТСЯ СКОРОСТЬ РАБОТЫ УСТРОЙСТВА
		sADCx.ADC_DelayGo          = 0x2;																	// Отложенный запуск, необходиим для нормальной работы
    ADC1_Init (&sADCx);																								// Применяем настройки к АЦП 1
    
		// Разрешаем прерывания от АЦП
    ADC1_ITConfig((ADCx_IT_END_OF_CONVERSION), ENABLE);
}