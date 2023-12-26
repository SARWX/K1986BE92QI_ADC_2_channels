#include "DMA_for_proj.h"
#include "MDR32F9Qx_dma.h"
#include "MDR32F9Qx_rst_clk.h"
#include "defines_for_proj.h"

// Внешние переменные
extern uint16_t DAC_table[];
extern uint16_t MainArrayForADC[];
extern uint16_t AlternateArrayForADC[];	

// Структуры для DMA
DMA_ChannelInitTypeDef sDMA_ADC1;
DMA_ChannelInitTypeDef sDMA_TIM2;
DMA_CtrlDataInitTypeDef sDMA_PriCtrlData_ADC1;				// Основная структура канала для ADC1
DMA_CtrlDataInitTypeDef sDMA_AltCtrlData_ADC1;				// Альтернативная структура канала для ADC1
DMA_CtrlDataInitTypeDef sDMA_PriCtrlData_TIM2;
DMA_CtrlDataInitTypeDef sDMA_AltCtrlData_TIM2;


// Настройка DMA
void SetupDMA() 
{
	// Разрешить тактирование DMA
	RST_CLK_PCLKcmd (RST_CLK_PCLK_DMA | RST_CLK_PCLK_SSP1 |
	RST_CLK_PCLK_SSP2, ENABLE);

	// Запретить все прерывания, в том числе от SSP1 и SSP2
	NVIC->ICPR[0] = WHOLE_WORD;
	NVIC->ICER[0] = WHOLE_WORD;

	// Сбросить все настройки DMA
	DMA_DeInit();
	DMA_StructInit (&sDMA_ADC1);		// Проинициализировать sDMA_ADC1 стандартными значениями
	
	// Заполняем структуру sDMA_PriCtrlData_ADC1 для АЦП 1
	sDMA_PriCtrlData_ADC1.DMA_SourceBaseAddr =															// Адрес откуда будем брать измерения 
	(uint32_t)(&(MDR_ADC->ADC1_RESULT));																		// Соответственно это регистр ADC1_RESULT
	sDMA_PriCtrlData_ADC1.DMA_DestBaseAddr = (uint32_t)(MainArrayForADC);		// Адрес куда будем писать наши измерения
	sDMA_PriCtrlData_ADC1.DMA_CycleSize = NUM_OF_MES;												// Сколько измерений (DMA передач) содержит 1 DMA цикл
	sDMA_PriCtrlData_ADC1.DMA_SourceIncSize = DMA_SourceIncNo;							// Адрес ADC1_RESULT не требует инкремента, он статичен
	sDMA_PriCtrlData_ADC1.DMA_DestIncSize = DMA_DestIncHalfword;						// Адрес места, куда будем писать измерения будет инкрементироваться на 16 бит, т.к. АЦП 12 битный и в 8 бит он не поместится
	sDMA_PriCtrlData_ADC1.DMA_MemoryDataSize =															// Скажем DMA, Что мы работаем с 16 битными данными
	DMA_MemoryDataSize_HalfWord;	
	sDMA_PriCtrlData_ADC1.DMA_NumContinuous = DMA_Transfers_1024;						// Сколько передач может пройти между процедурой арбитража
	sDMA_PriCtrlData_ADC1.DMA_SourceProtCtrl = DMA_SourcePrivileged;				// Память, откуда берем значения кэшируемая (не факт)
	sDMA_PriCtrlData_ADC1.DMA_DestProtCtrl = DMA_DestCacheable;							// Память, куда пишем значения кэшируемая (не факт)
	sDMA_PriCtrlData_ADC1.DMA_Mode = DMA_Mode_PingPong;											// Режим "Пинг-понг" ст. 385 спецификации к К1986ВЕ92QI

	// Заполним структуру sDMA_AltCtrlData_ADC1 для АЦП 1	
	sDMA_AltCtrlData_ADC1.DMA_SourceBaseAddr =															// Адрес откуда будем брать измерения 
	(uint32_t)(&(MDR_ADC->ADC1_RESULT));																		// Соответственно это регистр ADC1_RESULT
	sDMA_AltCtrlData_ADC1.DMA_DestBaseAddr = (uint32_t) (AlternateArrayForADC);		// Адрес куда будем писать наши измерения (+ размер массива / 2 * 2 байта)
	sDMA_AltCtrlData_ADC1.DMA_CycleSize = NUM_OF_MES;												// Сколько измерений (DMA передач) содержит 1 DMA цикл
	sDMA_AltCtrlData_ADC1.DMA_SourceIncSize = DMA_SourceIncNo;							// Адрес ADC1_RESULT не требует инкремента, он статичен
	sDMA_AltCtrlData_ADC1.DMA_DestIncSize = DMA_DestIncHalfword;						// Адрес места, куда будем писать измерения будет инкрементироваться на 16 бит
	sDMA_AltCtrlData_ADC1.DMA_MemoryDataSize =															// Скажем DMA, Что мы работаем с 16 битными данными
	DMA_MemoryDataSize_HalfWord;
	sDMA_AltCtrlData_ADC1.DMA_NumContinuous = DMA_Transfers_1024;						// Сколько передач может пройти между процедурой арбитража
	sDMA_AltCtrlData_ADC1.DMA_SourceProtCtrl = DMA_SourcePrivileged;				// Память, откуда берем значения кэшируемая (не факт)
	sDMA_AltCtrlData_ADC1.DMA_DestProtCtrl = DMA_DestCacheable;							// Память, куда пишем значения кэшируемая (не факт)
	sDMA_AltCtrlData_ADC1.DMA_Mode = DMA_Mode_PingPong;											// Режим "Пинг-понг" ст. 385 спецификации к К1986ВЕ92QI
	
	// Заполним структуру для 1ого канала 
	sDMA_ADC1.DMA_PriCtrlData = &sDMA_PriCtrlData_ADC1;											// Укажем основную структуру
	sDMA_ADC1.DMA_AltCtrlData = &sDMA_AltCtrlData_ADC1;											// Укажем альтернативную структуру
	sDMA_ADC1.DMA_Priority = DMA_Priority_Default;													// Обычный уровень приоритетности (нужен для арбитража)
	sDMA_ADC1.DMA_UseBurst = DMA_BurstClear;
	sDMA_ADC1.DMA_SelectDataStructure =	DMA_CTRL_DATA_PRIMARY;							// в качестве базовой берем основную структуру
	
	// Проинициализируем первый канал
	DMA_Init(DMA_Channel_ADC1, &sDMA_ADC1);
	MDR_DMA->CHNL_REQ_MASK_CLR = 1 << DMA_Channel_ADC1;
	MDR_DMA->CHNL_USEBURST_CLR = 1 << DMA_Channel_ADC1;
}

void DMA_IRQHandler() 
{
	if(DMA_GetFlagStatus(DMA_Channel_TIM2, DMA_FLAG_CHNL_ALT) == RESET) 
	{
		DMA_CtrlInit(DMA_Channel_TIM2, DMA_CTRL_DATA_ALTERNATE, &sDMA_AltCtrlData_TIM2);	// реинициализируем альтернативную структуру
	}
	
	else  
	{
		DMA_CtrlInit(DMA_Channel_TIM2, DMA_CTRL_DATA_PRIMARY, &sDMA_PriCtrlData_TIM2);		// реинициализируем основную структуру
	}
}