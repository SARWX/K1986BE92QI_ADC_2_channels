/**
  ******************************************************************************
  * @file    DMA_init.c
  * @author  ICV
  * @version V1.0.0
  * @date    08/05/2024
  * @brief   DMA initialization Header File.
  * ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DMA_init
#define DMA_init
// Структуры для DMA
extern DMA_CtrlDataInitTypeDef ADC1_primary_DMA_structure;				// Основная структура канала для ADC1
extern DMA_CtrlDataInitTypeDef ADC1_alternate_DMA_structure;				// Альтернативная структура канала для ADC1
void Setup_DMA();

#endif /* DMA_init */