/**
  ******************************************************************************
  * @file    adc.h
  * @author  ICV
  * @version V1.1.0
  * @date    19/10/2024
  * @brief   ADC initialization Header File.
  * ******************************************************************************
  */

#include "command_sys_flex.h"
#include "MDR32Fx.h"

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ADC_init
#define ADC_init

/** @defgroup __Specific_ADC Specific ADC functions
  * @{
  */

void Setup_ADC();
void change_adc_chan_num(int num_adc_chan);
ErrorStatus reconfig_ADC_clock(uint32_t input_freq, int num_of_adc_channels /* enum mode_setting mode */);

/** @} */ /* End of group __Specific_ADC */

#endif /* ADC_init */

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE adc.h */