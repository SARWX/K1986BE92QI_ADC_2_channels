#include "MDR32F9Qx_dma.h"
#include "MDR32F9Qx_rst_clk.h"
#include "defines_for_proj.h"
#include "DMA_for_proj.h"

// Внешние переменные
extern uint16_t DAC_table[];
extern uint16_t ADC1_array_m[];
extern uint16_t ADC1_array_a[];	

// Структуры для DMA
DMA_ChannelInitTypeDef sDMA_ADC1;
DMA_ChannelInitTypeDef sDMA_TIM2;
DMA_CtrlDataInitTypeDef sDMA_PriCtrlData_ADC1;				// Основная структура канала для ADC1
DMA_CtrlDataInitTypeDef sDMA_AltCtrlData_ADC1;				// Альтернативная структура канала для ADC1
DMA_CtrlDataInitTypeDef sDMA_PriCtrlData_TIM2;
DMA_CtrlDataInitTypeDef sDMA_AltCtrlData_TIM2;


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
	sDMA_PriCtrlData_ADC1.DMA_SourceBaseAddr =								// Адрес откуда будем брать измерения 
	(uint32_t)(&(MDR_ADC->ADC1_RESULT));									// Соответственно это регистр ADC1_RESULT
	sDMA_PriCtrlData_ADC1.DMA_DestBaseAddr = (uint32_t)(ADC1_array_m);		// Адрес куда будем писать наши измерения
	sDMA_PriCtrlData_ADC1.DMA_CycleSize = NUM_OF_MES;						// Сколько измерений (DMA передач) содержит 1 DMA цикл
	sDMA_PriCtrlData_ADC1.DMA_SourceIncSize = DMA_SourceIncNo;				// Адрес ADC1_RESULT не требует инкремента, он статичен
	sDMA_PriCtrlData_ADC1.DMA_DestIncSize = DMA_DestIncHalfword;			// Адрес места, куда будем писать измерения будет инкрементироваться на 16 бит, т.к. АЦП 12 битный и в 8 бит он не поместится
	sDMA_PriCtrlData_ADC1.DMA_MemoryDataSize =								// Скажем DMA, Что мы работаем с 16 битными данными
	DMA_MemoryDataSize_HalfWord;	
	sDMA_PriCtrlData_ADC1.DMA_NumContinuous = DMA_Transfers_1024;			// Сколько передач может пройти между процедурой арбитража
	sDMA_PriCtrlData_ADC1.DMA_SourceProtCtrl = DMA_SourcePrivileged;		// Память, откуда берем значения кэшируемая (не факт)
	sDMA_PriCtrlData_ADC1.DMA_DestProtCtrl = DMA_DestCacheable;				// Память, куда пишем значения кэшируемая (не факт)
	sDMA_PriCtrlData_ADC1.DMA_Mode = DMA_Mode_PingPong;						// Режим "Пинг-понг" ст. 385 спецификации к К1986ВЕ92QI

	// Заполним структуру sDMA_AltCtrlData_ADC1 для АЦП 1	
	sDMA_AltCtrlData_ADC1.DMA_SourceBaseAddr =								// Адрес откуда будем брать измерения 
	(uint32_t)(&(MDR_ADC->ADC1_RESULT));									// Соответственно это регистр ADC1_RESULT
	sDMA_AltCtrlData_ADC1.DMA_DestBaseAddr = (uint32_t) (ADC1_array_a);		// Адрес куда будем писать наши измерения (+ размер массива / 2 * 2 байта)
	sDMA_AltCtrlData_ADC1.DMA_CycleSize = NUM_OF_MES;						// Сколько измерений (DMA передач) содержит 1 DMA цикл
	sDMA_AltCtrlData_ADC1.DMA_SourceIncSize = DMA_SourceIncNo;				// Адрес ADC1_RESULT не требует инкремента, он статичен
	sDMA_AltCtrlData_ADC1.DMA_DestIncSize = DMA_DestIncHalfword;			// Адрес места, куда будем писать измерения будет инкрементироваться на 16 бит
	sDMA_AltCtrlData_ADC1.DMA_MemoryDataSize =								// Скажем DMA, Что мы работаем с 16 битными данными
	DMA_MemoryDataSize_HalfWord;
	sDMA_AltCtrlData_ADC1.DMA_NumContinuous = DMA_Transfers_1024;			// Сколько передач может пройти между процедурой арбитража
	sDMA_AltCtrlData_ADC1.DMA_SourceProtCtrl = DMA_SourcePrivileged;		// Память, откуда берем значения кэшируемая (не факт)
	sDMA_AltCtrlData_ADC1.DMA_DestProtCtrl = DMA_DestCacheable;				// Память, куда пишем значения кэшируемая (не факт)
	sDMA_AltCtrlData_ADC1.DMA_Mode = DMA_Mode_PingPong;						// Режим "Пинг-понг" ст. 385 спецификации к К1986ВЕ92QI
	
	// Заполним структуру для 1ого канала 
	sDMA_ADC1.DMA_PriCtrlData = &sDMA_PriCtrlData_ADC1;						// Укажем основную структуру
	sDMA_ADC1.DMA_AltCtrlData = &sDMA_AltCtrlData_ADC1;						// Укажем альтернативную структуру
	sDMA_ADC1.DMA_Priority = DMA_Priority_Default;							// Обычный уровень приоритетности (нужен для арбитража)
	sDMA_ADC1.DMA_UseBurst = DMA_BurstClear;
	sDMA_ADC1.DMA_SelectDataStructure =	DMA_CTRL_DATA_PRIMARY;				// в качестве базовой берем основную структуру
	
	// Проинициализируем первый канал
	DMA_Init(DMA_Channel_ADC1, &sDMA_ADC1);
	MDR_DMA->CHNL_REQ_MASK_CLR = 1 << DMA_Channel_ADC1;
	MDR_DMA->CHNL_USEBURST_CLR = 1 << DMA_Channel_ADC1;

	// Будем использовать TIM2 для генерации сигнала DAC
	DMA_StructInit (&sDMA_TIM2);		// Проинициализировать sDMA_ADC1 стандартными значениями
	// Заполняем структуру sDMA_PriCtrlData_ADC1 для Таймера 2
	sDMA_PriCtrlData_TIM2.DMA_SourceBaseAddr =								// Адрес откуда будем брать измерения 
	(uint32_t)(DAC_table);													// Соответственно это таблица DAC_table
	sDMA_PriCtrlData_TIM2.DMA_DestBaseAddr = 
	(uint32_t)(&(MDR_DAC->DAC2_DATA));										// Адрес куда будем писать наши измерения (в DAC 2)
	sDMA_PriCtrlData_TIM2.DMA_CycleSize = (SIN_RES);							// Сколько измерений (DMA передач) содержит 1 DMA цикл
	sDMA_PriCtrlData_TIM2.DMA_SourceIncSize = DMA_SourceIncHalfword;		// DAC_table - 16 битный массив => инкремент = полуслово
	sDMA_PriCtrlData_TIM2.DMA_DestIncSize = DMA_DestIncNo;					// Адрес места, куда будем писать измерения не будет инкрементироваться
	sDMA_PriCtrlData_TIM2.DMA_MemoryDataSize =								// Скажем DMA, Что мы работаем с 16 битными данными
	DMA_MemoryDataSize_HalfWord;	
	sDMA_PriCtrlData_TIM2.DMA_NumContinuous = DMA_Transfers_16;				// Сколько передач может пройти между процедурой арбитража
	sDMA_PriCtrlData_TIM2.DMA_SourceProtCtrl = DMA_SourcePrivileged;		// Память, откуда берем значения кэшируемая (не факт)
	sDMA_PriCtrlData_TIM2.DMA_DestProtCtrl = DMA_DestCacheable;				// Память, куда пишем значения кэшируемая (не факт)
	sDMA_PriCtrlData_TIM2.DMA_Mode = DMA_Mode_PingPong;						// Стандартный режим работы DMA 
	
	// Заполняем структуру sDMA_AltCtrlData_ADC1 для Таймера 2
	sDMA_AltCtrlData_TIM2.DMA_SourceBaseAddr =								// Адрес откуда будем брать измерения 
	(uint32_t)(DAC_table);													// Соответственно это таблица DAC_table
	sDMA_AltCtrlData_TIM2.DMA_DestBaseAddr = 
	(uint32_t)(&(MDR_DAC->DAC2_DATA));										// Адрес куда будем писать наши измерения (в DAC 2)
	sDMA_AltCtrlData_TIM2.DMA_CycleSize = (SIN_RES);							// Сколько измерений (DMA передач) содержит 1 DMA цикл
	sDMA_AltCtrlData_TIM2.DMA_SourceIncSize = DMA_SourceIncHalfword;		// DAC_table - 16 битный массив => инкремент = полуслово
	sDMA_AltCtrlData_TIM2.DMA_DestIncSize = DMA_DestIncNo;					// Адрес места, куда будем писать измерения не будет инкрементироваться
	sDMA_AltCtrlData_TIM2.DMA_MemoryDataSize =								// Скажем DMA, Что мы работаем с 16 битными данными
	DMA_MemoryDataSize_HalfWord;	
	sDMA_AltCtrlData_TIM2.DMA_NumContinuous = DMA_Transfers_16;				// Сколько передач может пройти между процедурой арбитража
	sDMA_AltCtrlData_TIM2.DMA_SourceProtCtrl = DMA_SourcePrivileged;		// Память, откуда берем значения кэшируемая (не факт)
	sDMA_AltCtrlData_TIM2.DMA_DestProtCtrl = DMA_DestCacheable;				// Память, куда пишем значения кэшируемая (не факт)
	sDMA_AltCtrlData_TIM2.DMA_Mode = DMA_Mode_PingPong;						// Стандартный режим работы DMA 
	
	// Заполним структуру для канала TIM2 
	sDMA_TIM2.DMA_PriCtrlData = &sDMA_PriCtrlData_TIM2;						// Укажем основную структуру
	sDMA_TIM2.DMA_Priority = DMA_Priority_Default;							// Обычный уровень приоритетности (нужен для арбитража)
	sDMA_TIM2.DMA_UseBurst = DMA_BurstClear;
	sDMA_TIM2.DMA_SelectDataStructure =	DMA_CTRL_DATA_PRIMARY;				// в качестве базовой берем основную структуру
	
	// Проинициализируем первый канал
	DMA_Init(DMA_Channel_TIM2, &sDMA_TIM2);
	MDR_DMA->CHNL_REQ_MASK_CLR = 1 << DMA_Channel_TIM2;
	MDR_DMA->CHNL_USEBURST_CLR = 1 << DMA_Channel_TIM2;

	// Установим значение приоретета прерывания DMA
	NVIC_EnableIRQ(DMA_IRQn);
	NVIC_SetPriority (DMA_IRQn, 100);
}

void DMA_IRQHandler() {
	if(DMA_GetFlagStatus(DMA_Channel_TIM2, DMA_FLAG_CHNL_ALT) == RESET) {
		DMA_CtrlInit(DMA_Channel_TIM2, DMA_CTRL_DATA_ALTERNATE, &sDMA_AltCtrlData_TIM2);	// реинициализируем альтернативную структуру
	}
	else  {
		DMA_CtrlInit(DMA_Channel_TIM2, DMA_CTRL_DATA_PRIMARY, &sDMA_PriCtrlData_TIM2);		// реинициализируем основную структуру
	}
}
