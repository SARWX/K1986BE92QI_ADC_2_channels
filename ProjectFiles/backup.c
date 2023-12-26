
/* Includes ------------------------------------------------------------------*/
// #include "main.h" 
// Основано на другом проекте от Гарановича Д.И.
// Используется только аппаратный USB, АЦП, должен определяться в системе, как устройство
// с последовательным интерфейсом
// Это программа должна читать данные с АЦП (на данный момент, с одного, в перспективе - с двух)
// считанные данные должны передаваться в Serial port 
// требуется достичь максимальной скорости оцифровки для АЦП

#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_usb_handlers.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_ssp.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_adc.h"
#include "MDR32F9Qx_dma.h"

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

/* Макроподстановки --------------------------------------------------------------*/
#define BUFFER_LENGTH 128
#define timeout 10
//#define DEBUG
#define LED_Pin PORT_Pin_2
#define LED_Port MDR_PORTC
#define NUM_OF_MES 128			// 64 * 2 - 2

/* Глобальные переменные ---------------------------------------------------------*/
static USB_Clock_TypeDef USB_Clock_InitStruct;
static USB_DeviceBUSParam_TypeDef USB_DeviceBUSParam;
static MDR_SSP_TypeDef SSP_InitStruct;
SSP_InitTypeDef sSSP;
PORT_InitTypeDef PORT_InitStructure;

static uint8_t Buffer[BUFFER_LENGTH];
static uint8_t RecBuf[BUFFER_LENGTH];
static uint8_t DoubleBuf[BUFFER_LENGTH * 2];

char *start;
char *end;
char tokens[5][BUFFER_LENGTH * 2]; //usb parsing tokens pointers array
char tempString[100];			   //debug

// массивы для АЦП
uint16_t ADC1_array_m[200];
uint16_t ADC1_array_a[200];

// Структуры для АЦП
ADC_InitTypeDef sADC;
ADCx_InitTypeDef sADCx;
// Структуры для DMA
DMA_ChannelInitTypeDef sDMA_ADC1;
DMA_ChannelInitTypeDef sDMA_ADC2;
DMA_CtrlDataInitTypeDef sDMA_PriCtrlData_ADC1;				// Основная структура канала для ADC1
DMA_CtrlDataInitTypeDef sDMA_AltCtrlData_ADC1;				// Альтернативная структура канала для ADC1
DMA_CtrlDataInitTypeDef sDMA_PriCtrlData_ADC2;				// Основная структура канала для ADC2
DMA_CtrlDataInitTypeDef sDMA_AltCtrlData_ADC2;				// Альтернативная структура канала для ADC2
/* ---------------------------------------------------------------------------*/

#ifdef USB_CDC_LINE_CODING_SUPPORTED
static USB_CDC_LineCoding_TypeDef LineCoding;
#endif /* USB_CDC_LINE_CODING_SUPPORTED */

/* Объявления функций --------------------------------------------------------*/
static void Setup_CPU_Clock(void); 							// настройка тактирования ядра
static void Setup_USB(void);
static void VCom_Configuration(void); 						// конфигурация виртуального COM-порта
static void USB_PrintDebug(char *format, ...);				// вывод отладочных сообщений
static void SetupDMA();
static void SetupADC(); 									// настройка АЦП

/* Определение функций ---------------------------------------------------------*/
// задержка на count тактов 
void delayTick(uint32_t count)		// Ждать count тактов процессора
{	
	while (count--) {				// декремент счетчика	
		__NOP();					// Не делать ничего
	}
}

// вывод символов в USB 
void USB_Print(char *format, ...) 
{
	va_list argptr;
	va_start(argptr, format);
	vsprintf(tempString, format, argptr);
	va_end(argptr);
	USB_CDC_SendData((uint8_t *)tempString, strlen(tempString));
}

void USB_PrintDebug(char *format, ...) 
{
#ifdef DEBUG
	va_list argptr;
	va_start(argptr, format);

	vsprintf(tempString, format, argptr);
	va_end(argptr);
	//CDC_Transmit_FS((uint8_t *)tempString,strlen(tempString) );
	USB_CDC_SendData((uint8_t *)tempString, strlen(tempString));
	delayTick(timeout);
#endif
}

int main(void) 
{
	/*
	ADC1_array_m[0] = 5001;
	ADC1_array_m[(NUM_OF_MES + 1)] = 6000;

	ADC1_array_a[0] = 5002;
	ADC1_array_a[(2 * NUM_OF_MES + 1)] = 8002;
	*/
	VCom_Configuration();

	/* CDC layer initialization */
	SetupADC();
	SetupDMA();
	USB_CDC_Init(Buffer, 1, SET);
	Setup_CPU_Clock();
	Setup_USB();
  
	// Инициализация пина для светодиода
	RST_CLK_PCLKcmd (RST_CLK_PCLK_PORTC, ENABLE);
	PORT_InitStructure.PORT_Pin = (LED_Pin);
	PORT_InitStructure.PORT_OE = PORT_OE_OUT;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_Init(LED_Port, &PORT_InitStructure);

	int num_of_transfers = 0;
reinit_DMA:

num_of_transfers = 0;

	// Выключение DMA для АЦП
	ADC1_Cmd (DISABLE);
	ADC2_Cmd (DISABLE);
	DMA_Cmd(DMA_Channel_ADC1, DISABLE);
	DMA_Cmd(DMA_Channel_ADC2, DISABLE);

//		ADC1_Cmd (ENABLE);
		MDR_ADC->ADC1_CFG |= ADC1_CFG_REG_ADON;
//		ADC2_Cmd (ENABLE);

		
		ADC2_SetChannel(ADC_CH_ADC1);
//		DMA_Cmd(DMA_Channel_ADC1, ENABLE);		// разрешаем работу (периодически разрешение может сбиваться, поэтому стоит периодически делать это)
//		DMA_Cmd(DMA_Channel_ADC2, ENABLE);		// соответсвенно для 1ого и 2ого канала
		MDR_DMA->CHNL_ENABLE_SET = (1 << DMA_Channel_ADC1);
//		MDR_DMA->CHNL_ENABLE_SET = (1 << DMA_Channel_ADC1);


	/* Main loop */
	while (1) {
//		num_of_transfers++;
		// 1 стадия
		while ((DMA_GetFlagStatus(DMA_Channel_ADC1, DMA_FLAG_CHNL_ALT) == 0))
			;
		DMA_CtrlInit(DMA_Channel_ADC1, DMA_CTRL_DATA_PRIMARY, &sDMA_PriCtrlData_ADC1);	

		USB_CDC_SendData((uint8_t *)(ADC1_array_m), ((NUM_OF_MES) * 2 ));
		
		// 2 стадия
		while ((DMA_GetFlagStatus(DMA_Channel_ADC1, DMA_FLAG_CHNL_ALT) != 0))
			;					// ждем, когда ADC1 перейдет на основную структуру
		DMA_CtrlInit(DMA_Channel_ADC1, DMA_CTRL_DATA_ALTERNATE, &sDMA_AltCtrlData_ADC1);	// для DMA_Channel_ADC1
		DMA_CtrlInit(DMA_Channel_ADC2, DMA_CTRL_DATA_ALTERNATE, &sDMA_AltCtrlData_ADC2);
//		DMA_Cmd(DMA_Channel_ADC1, ENABLE);		// разрешаем работу 1ого канала
//		DMA_Cmd(DMA_Channel_ADC2, ENABLE);		// разрешаем работу 2ого канала
		USB_CDC_SendData((uint8_t *)(ADC1_array_a), ((NUM_OF_MES) * 2));

	}	
}

void SetupADC() 
{
	// Подключаем тактирование к блоку АЦП, портам A и C 
    RST_CLK_PCLKcmd((RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_ADC), ENABLE);
    RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD), ENABLE);

	// Инициализируем контроллер прерывний (NVIC)
    SCB->AIRCR = 0x05FA0000 | ((uint32_t)0x500);
    SCB->VTOR = 0x08000000;
	
    // Запрещаем все прерывания
    NVIC->ICPR[0] = 0xFFFFFFFF;
    NVIC->ICER[0] = 0xFFFFFFFF;

	NVIC->ISER[0] = (1<<ADC_IRQn);

	// Сбрасываем настройки порта D
    PORT_DeInit(MDR_PORTD);

	// Конфигурируем выводы для АЦП 1 и 2
    PORT_InitStructure.PORT_Pin   = PORT_Pin_0 | PORT_Pin_1;			// АЦП 1 и 2 расположены на PD0 и PD1 (см. распиновку)
    PORT_InitStructure.PORT_OE    = PORT_OE_IN;							// Режим на вход
    PORT_InitStructure.PORT_MODE  = PORT_MODE_ANALOG;					// Аналоговый вход
    PORT_Init(MDR_PORTD, &PORT_InitStructure);							// Инициализация выводов заданной структурой

	// Настройка АЦП
    ADC_DeInit();														// Сбросить все прежние настройки АЦП
    ADC_StructInit(&sADC);												// Проинициализировать структуру стандартными значениями
//		sADC.ADC_SynchronousMode  = ADC_SyncMode_Synchronous;		// Запустить 2 АЦП в сихронном режиме
//		sADC.ADC_StartDelay = 0xF;								// Задержка 4 такта
		ADC_Init (&sADC);													// Применить конфигурацию, занесенную в sADC

    ADCx_StructInit (&sADCx);											// Проинициализировать структуру для отдельного канала стандартными значениями
    sADCx.ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;					// Источник тактирования - ЦПУ (т.е. от HSE)
    sADCx.ADC_SamplingMode     = ADC_SAMPLING_MODE_CYCLIC_CONV;			// Режим работы (циклические преобразования, а не одиночное)
    sADCx.ADC_ChannelSwitching = ADC_CH_SWITCHING_Enable;				// Переключение каналов разрешено, АЦП 1 будет вссегда работать на PD0,// PD1
    sADCx.ADC_ChannelNumber    = ADC_CH_ADC0;							// Указываем канал АЦП 1 (ADC0 = АЦП 1, т.к. у Миландр он то первый, то нулевой)
    sADCx.ADC_Channels         = (ADC_CH_ADC0_MSK | ADC_CH_ADC1_MSK);						// Маска для каналов 0 и 1
    sADCx.ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;				// Опорное напряжение от внутреннего источника
    sADCx.ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;			// Выбираем неточный источник опорного напряжения
    sADCx.ADC_Prescaler        = ADC_CLK_div_16;						// Задаем скорость работы АЦП, ИМЕННО ЭТОЙ НАСТРОЙКОЙ ЗАДАЕТСЯ СКОРОСТЬ РАБОТЫ УСТРОЙСТВА
 //   sADCx.ADC_DelayGo          = 0x7;									// Отложенный запуск, необходиим для нормальной работы
		sADCx.ADC_DelayGo          = 0x2;
		
    ADC1_Init (&sADCx);													// Применяем настройки к АЦП 1

    // Разрешаем прерывания от АЦП
    ADC1_ITConfig((ADCx_IT_END_OF_CONVERSION), ENABLE);
}

void Setup_CPU_Clock(void) 
{
	/* Подлючаем HSE */
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);

	if (RST_CLK_HSEstatus() != SUCCESS)
	{
	/* Trap */ // если не установилась частота, то выпадает в бесконечный цикл
			   // нужно исправить, чтобы было понятно без подключения отладки
		while (1) 
		{
			;
		}
	}

	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul8); //  16 MHz
	
	RST_CLK_CPU_PLLcmd(ENABLE);

	if (RST_CLK_CPU_PLLstatus() != SUCCESS)
	{
		/* Trap */ // та же ситуация, что и в предыдущем случае
		while (1) 
		{
			;
		}
	}

	// CPU_C3_SEL = CPU_C2_SEL
	RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);
	// CPU_C2_SEL = PLL 
	RST_CLK_CPU_PLLuse(ENABLE);
	// HCLK_SEL = CPU_C3_SEL
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
}

/**
	* @brief	USB Device layer setup and powering on
	* @param	None
	* @retval None
	*/
void Setup_USB(void) {
	/* Enables the CPU_CLK clock on USB */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_USB, ENABLE);

	/* Device layer initialization */
	//USB_Clock_InitStruct.USB_USBC1_Source = USB_C1HSIdiv1; 
	USB_Clock_InitStruct.USB_USBC1_Source = USB_C1HSEdiv2; //HSE 
	USB_Clock_InitStruct.USB_PLLUSBMUL = USB_PLLUSBMUL6;   //was 12

	USB_DeviceBUSParam.MODE = USB_SC_SCFSP_Full;
	USB_DeviceBUSParam.SPEED = USB_SC_SCFSR_12Mb;
	USB_DeviceBUSParam.PULL = USB_HSCR_DP_PULLUP_Set;

	USB_DeviceInit(&USB_Clock_InitStruct, &USB_DeviceBUSParam);
	/* Enable all USB interrupts */
	USB_SetSIM(USB_SIS_Msk);
	USB_DevicePowerOn();

	/* Enable interrupt on USB */
#ifdef USB_INT_HANDLE_REQUIRED
	NVIC_EnableIRQ(USB_IRQn);
#endif /* USB_INT_HANDLE_REQUIRED */

	USB_DEVICE_HANDLE_RESET;
}

/**
	* @brief	Example-relating data initialization
	* @param	None
	* @retval None
	*/
static void VCom_Configuration(void) 
{
	#ifdef USB_CDC_LINE_CODING_SUPPORTED
		//LineCoding.dwDTERate = 9600;
		LineCoding.dwDTERate = 1000000;
		LineCoding.bCharFormat = 0;
		LineCoding.bParityType = 0;
		LineCoding.bDataBits = 8;
	#endif /* USB_CDC_LINE_CODING_SUPPORTED */
}

USB_Result USB_CDC_RecieveData(uint8_t *Buffer, uint32_t Length) 
{
	memcpy(RecBuf, Buffer, BUFFER_LENGTH);
	RecBuf[Length] = 0; //why last byte on odd wrong.
	return USB_SUCCESS;
}

#ifdef USB_CDC_LINE_CODING_SUPPORTED

USB_Result USB_CDC_GetLineCoding(uint16_t wINDEX, USB_CDC_LineCoding_TypeDef *DATA) 
{
	assert_param(DATA);
	if (wINDEX != 0)
	{
		/* Invalid interface */
		return USB_ERR_INV_REQ;
	}

	/* Just store received settings */
	*DATA = LineCoding;
	return USB_SUCCESS;
}

USB_Result USB_CDC_SetLineCoding(uint16_t wINDEX, const USB_CDC_LineCoding_TypeDef *DATA) {
	assert_param(DATA);
	if (wINDEX != 0)
	{
		/* Invalid interface */
		return USB_ERR_INV_REQ;
	}

	/* Just send back settings stored earlier */
	LineCoding = *DATA;
	return USB_SUCCESS;
}

#endif /* USB_CDC_LINE_CODING_SUPPORTED */

// Настройка DMA
void SetupDMA() 
{
	// Разрешить тактирование DMA
	RST_CLK_PCLKcmd (RST_CLK_PCLK_DMA | RST_CLK_PCLK_SSP1 |
	RST_CLK_PCLK_SSP2, ENABLE);

	// Запретить все прерывания, в том числе от SSP1 и SSP2
	NVIC->ICPR[0] = 0xFFFFFFFF;
	NVIC->ICER[0] = 0xFFFFFFFF;

	// Сбросить все настройки DMA
	DMA_DeInit();
	DMA_StructInit (&sDMA_ADC1);		// Проинициализировать sDMA_ADC1 стандартными значениями
	DMA_StructInit (&sDMA_ADC2);		// Проинициализировать sDMA_ADC2 стандартными значениями
	
	// Заполняем структуру sDMA_PriCtrlData_ADC1 для АЦП 1
	sDMA_PriCtrlData_ADC1.DMA_SourceBaseAddr =								// Адрес откуда будем брать измерения 
	(uint32_t)(&(MDR_ADC->ADC1_RESULT));									// Соответственно это регистр ADC1_RESULT
	sDMA_PriCtrlData_ADC1.DMA_DestBaseAddr = (uint32_t)(ADC1_array_m);			// Адрес куда будем писать наши измерения
	sDMA_PriCtrlData_ADC1.DMA_CycleSize = NUM_OF_MES;								// Сколько измерений (DMA передач) содержит 1 DMA цикл
	sDMA_PriCtrlData_ADC1.DMA_SourceIncSize = DMA_SourceIncNo;				// Адрес ADC1_RESULT не требует инкремента, он статичен
	sDMA_PriCtrlData_ADC1.DMA_DestIncSize = DMA_DestIncHalfword;			// Адрес места, куда будем писать измерения будет инкрементироваться на 16 бит, т.к. АЦП 12 битный и в 8 бит он не поместится
	sDMA_PriCtrlData_ADC1.DMA_MemoryDataSize =								// Скажем DMA, Что мы работаем с 16 битными данными
	DMA_MemoryDataSize_HalfWord;	
	sDMA_PriCtrlData_ADC1.DMA_NumContinuous = DMA_Transfers_1024;			// Сколько передач может пройти между процедурой арбитража
	sDMA_PriCtrlData_ADC1.DMA_SourceProtCtrl = DMA_SourcePrivileged;			// Память, откуда берем значения кэшируемая (не факт)
	sDMA_PriCtrlData_ADC1.DMA_DestProtCtrl = DMA_DestCacheable;				// Память, куда пишем значения кэшируемая (не факт)
	sDMA_PriCtrlData_ADC1.DMA_Mode = DMA_Mode_PingPong;						// Режим "Пинг-понг" ст. 385 спецификации к К1986ВЕ92QI

	// Заполним структуру sDMA_AltCtrlData_ADC1 для АЦП 1	
	sDMA_AltCtrlData_ADC1.DMA_SourceBaseAddr =								// Адрес откуда будем брать измерения 
	(uint32_t)(&(MDR_ADC->ADC1_RESULT));									// Соответственно это регистр ADC1_RESULT
	sDMA_AltCtrlData_ADC1.DMA_DestBaseAddr = (uint32_t) (ADC1_array_a);	// Адрес куда будем писать наши измерения (+ размер массива / 2 * 2 байта)
	sDMA_AltCtrlData_ADC1.DMA_CycleSize = NUM_OF_MES;								// Сколько измерений (DMA передач) содержит 1 DMA цикл
	sDMA_AltCtrlData_ADC1.DMA_SourceIncSize = DMA_SourceIncNo;				// Адрес ADC1_RESULT не требует инкремента, он статичен
	sDMA_AltCtrlData_ADC1.DMA_DestIncSize = DMA_DestIncHalfword;			// Адрес места, куда будем писать измерения будет инкрементироваться на 16 бит
	sDMA_AltCtrlData_ADC1.DMA_MemoryDataSize =								// Скажем DMA, Что мы работаем с 16 битными данными
	DMA_MemoryDataSize_HalfWord;
	sDMA_AltCtrlData_ADC1.DMA_NumContinuous = DMA_Transfers_1024;			// Сколько передач может пройти между процедурой арбитража
	sDMA_AltCtrlData_ADC1.DMA_SourceProtCtrl = DMA_SourcePrivileged;			// Память, откуда берем значения кэшируемая (не факт)
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

	
	// Разрешим DMA работать с каналом DMA_Channel_ADC1
//	DMA_Cmd (DMA_Channel_ADC1, ENABLE);
	
	// Разрешим DMA работать с каналом DMA_Channel_ADC2 
//	DMA_Cmd (DMA_Channel_ADC2, ENABLE);

	// Установим значение приоретета прерывания DMA
	NVIC_SetPriority (DMA_IRQn, 100);
}
