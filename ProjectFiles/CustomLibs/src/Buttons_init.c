#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "defines.h"

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
    NVIC->ICPR[0] = WHOLE_WORD;
    NVIC->ICER[0] = WHOLE_WORD;
	NVIC->ISER[0] = (1<<ADC_IRQn);

	// Сбрасываем настройки порта D
    PORT_DeInit(MDR_PORTD);

	// Конфигурируем выводы для АЦП 1 и 2
    port_init_structure.PORT_Pin   = PORT_Pin_0 | PORT_Pin_1;			    // АЦП 1 и 2 расположены на PD0 и PD1 (см. распиновку)
    port_init_structure.PORT_OE    = PORT_OE_IN;							          // Режим на вход
    port_init_structure.PORT_MODE  = PORT_MODE_ANALOG;					        // Аналоговый вход
    PORT_Init(MDR_PORTD, &port_init_structure);							          // Инициализация выводов заданной структурой