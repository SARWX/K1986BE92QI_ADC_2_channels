/**
  ******************************************************************************
  * @file    defines.h
  * @author  ICV
  * @version V1.1.0
  * @date    19/10/2024
  * @brief   This file contains diferent defines for programm (you can change them, but be carefull)
  * ******************************************************************************
  */

 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef Defines
#define Defines

/** @defgroup __Specific_declaration Specific declaration
  * @{
  */
/* Макроподстановки --------------------------------------------------------------*/
#define BUFFER_LENGTH 128               /* размер буфера для команд USB */

#define SIN_RES 250 					/* разрешение синусоиды (точек на период) */
#define SIN_AMPLITUDE 2000				/* должно быть меньше < 4096 / 2 */
#define SIN_MEDIUM_LINE 2000			/* средняя линия для синусоиды на ЦАП */
#define MAX_ADC_VAL 4095				/* максимальное значение 12 битного АЦП */
#define CORRECTION_FACTOR 1.1			/* поправочный коэфициент для задания точной частоты */

#define AIRCR_SETTING 0x5FA0500			/* настройка для регистра AIRCR */
#define VECTOR_TABLE_OFFSET 0x08000000	/* смещение таблицы векторов */
#define WHOLE_WORD 0xFFFFFFFF           /* константа отображающая 32 битное слово */

#define HSE_FREQ 16000000               /* частота HSE */
#define CPU_PLL 8                       /* коэффициент PLL */
#define CPU_DIV 1                       /* делитель частоты лдя CPU_CLK */

#define PRESCALER_T2 8					/* предделитель для TIM2 */
#define PRESCALER_T2_DAC_MODE 64		/* предделитель для TIM2 в dac_mode */
#define PERIOD_T2 16				    /* определяет период для TIM2 */
#define DISCRET_FREQ                    \
    ((HSE_FREQ * CPU_PLL / CPU_DIV) /   \
     (PRESCALER_T2 * PERIOD_T2))	    /* частота дискретизации ЦАП */ 

#define DAC_MODE_BUF_SIZE 128           /* размер буфера для dac_mode (адается в 16 битных числах) */
#define NUM_OF_MES 128	                /* количество измерений в одном пакете */
    // Этот параметр задает количество измерений АЦП, которые будут составлять 1 пакет.
    // контроллером USB они будут поделены на пакеты по 64 байта, поскольку 1 измерение АЦП кодируется 2 байтами,
    // количество измерений целесообразно выбирать кратным 32 (для достижения максимальной скорости)

#define PERIPH_BASE		0x40000000 		/* начало секции памяти периферии*/
#define PERIPH_BB_BASE	0x42000000 		/* начало bit banding секции памяти периферии*/
/**
 * @def BITBAND_PERIPH(address, bit)
 * @brief Macro for accessing bits of peripheral registers through Bit-Banding.
 * 
 * This macro allows you to obtain a pointer to a specific bit in a peripheral register
 * using the Bit-Banding mechanism. Bit-Banding enables addressing individual bits in memory
 * as regular variables, which can speed up access and improve performance when working
 * with specific bits in a register.
 * 
 * @param address Address of the peripheral register.
 * @param bit Bit number in the register to be accessed.
 * @retval Bit banding pointer to the corresponding bit in the peripheral register.
 * 
 * @example Example usage:
 * volatile uint32_t * const bb_port_c_2 = BITBAND_PERIPH(&(MDR_PORTC->RXTX), 2);
 * *bb_port_c_2 = 1;  // Set bit 2 through bit banding
 */
#define BITBAND_PERIPH(address, bit) \	
    ((__IO uint32_t *)( \
        PERIPH_BB_BASE + \
        (((uint32_t)(address)) - PERIPH_BASE) * 32 + \
        (bit) * 4 \
    ))			/* Макро для bit banding */

#define SSP1_CS PORT_Pin_2

/** @} */ /* End of group __Specific_declaration */

#endif /* Defines */

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE defines.h */
