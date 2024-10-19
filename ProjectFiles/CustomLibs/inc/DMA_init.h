/**
  ******************************************************************************
  * @file    DMA_init.c
  * @author  ICV
  * @version V1.1.0
  * @date    19/10/2024
  * @brief   DMA initialization Header File.
  * ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DMA_init
#define DMA_init
// Структуры для DMA
extern DMA_CtrlDataInitTypeDef ADC1_primary_DMA_structure;				// Основная структура канала для ADC1
extern DMA_CtrlDataInitTypeDef ADC1_alternate_DMA_structure;				// Альтернативная структура канала для ADC1
extern DMA_CtrlDataInitTypeDef TIM2_primary_DMA_structure;
extern DMA_CtrlDataInitTypeDef TIM2_alternate_DMA_structure;
void Setup_DMA();
void reconfig_DMA_dac_mode(void);

#endif /* DMA_init */

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE DMA_init.h */