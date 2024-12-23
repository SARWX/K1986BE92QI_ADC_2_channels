/**
  ******************************************************************************
  * @file    dac.h
  * @author  ICV
  * @version V1.1.0
  * @date    19/10/2024
  * @brief   DAC initialization Header File.
  * ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DAC_init
#define DAC_init

#include "command_sys_flex.h"

/**
 * @brief Type for dac_mode,
 * this type signalize current DMA state
 */
enum dac_mode_state 
{
  main_state,
  alt_state,
  not_init,
  stopped,
};

/** @defgroup __Specific_DAC Specific DAC functions
  * @{
  */

void Setup_DAC();
void Setup_TIM2();
void Setup_DEMUX_for_DAC(void);
void set_sin_DAC_table(int freq, int chan);
void change_dac_chan_num(int num_dac_chan);
void reconfig_TIM_dac_mode(void);
ErrorStatus reconfig_DAC_clock(uint32_t input_freq, enum mode_setting mode);

/** @} */ /* End of group __Specific_DAC */

#endif /* DAC_init */

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE dac.h */