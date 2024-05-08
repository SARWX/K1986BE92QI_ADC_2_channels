/**
  ******************************************************************************
  * @file    DAC_init.c
  * @author  ICV
  * @version V1.0.0
  * @date    08/05/2024
  * @brief   DAC ADC initialization Header File.
  * ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DAC_init
#define DAC_init

void Setup_DAC();
void Setup_TIM2();
void set_DAC_table(int freq);

#endif /* DAC_init */