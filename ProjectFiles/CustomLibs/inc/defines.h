/**
  ******************************************************************************
  * @file    defines.h
  * @author  ICV
  * @version V1.0.0
  * @date    08/05/2024
  * @brief   This file contains diferent defines for programm (you can change them, but be carefull)
  * ******************************************************************************
  */

/** @defgroup __Specific_declaration Specific declaration
  * @{
  */

/* Макроподстановки --------------------------------------------------------------*/
#define BUFFER_LENGTH 128
#define timeout 10
#define LED_Pin PORT_Pin_2
#define LED_Port MDR_PORTC
#define SIN_RES 250 					// Разрешение синусоиды (точек на период)
#define SIN_AMPLITUDE 2000				// должно быть меньше < 4096 / 2
#define SIN_MEDIUM_LINE 2000			// Средняя линия для синусоиды на ЦАП
#define MAX_ADC_VAL 4095				// Максимальное значение 12 битного АЦП
#define AIRCR_SETTING 0x5FA0500			// Настройка для регистра AIRCR
#define VECTOR_TABLE_OFFSET 0x08000000	// Смещение таблицы векторов (см. спецификацию)
#define WHOLE_WORD 0xFFFFFFFF			// Константа отображающая 32 битное слово
#define PRESCALER_T2 8//10					// Определяет воо сколько раз будет делиться системная частота для ЦАП
#define PRESCALER_T2_DAC_MODE 56//10					// Для режима потоковой передачи через USB в DAC
#define PERIOD_T2 16//12					// Определяет период работы ЦАП
#define HSE_FREQ 16000000
#define CPU_PLL 8
#define CPU_DIV 1
#define DISCRET_FREQ ((HSE_FREQ * CPU_PLL / CPU_DIV) / (PRESCALER_T2 * PERIOD_T2))	// определяет частоту дискретизации ЦАП 
// #define CORRECTION_FACTOR 1.065			// поправочный коэфициент для задания точной частоты
#define CORRECTION_FACTOR 1.1			// поправочный коэфициент для задания точной частоты

#define DAC_MODE_BUF_SIZE 128     // Задается в 16 битных числах
#define NUM_OF_MES 128	 
// Этот параметр задает количество измерений АЦП, которые будут составлять 1 пакет.
								// Но контроллером USB они будут поделены на пакеты по 64 байта, поскольку 1 измерение АЦП кодируется 2 байтами,
								// то количество измерений целесообразно выбирать кратным 32 (для достижения максимальной скорости)

/** @} */ /* End of group __Peripheral_declaration */

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE defines.h */