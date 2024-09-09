/**
  ******************************************************************************
  * @file    DAC_init.h
  * @author  ICV
  * @version V1.0.0
  * @date    08/05/2024
  * @brief   DAC initialization Header File.
  * ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DAC_init
#define DAC_init

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

void Setup_DAC();
void Setup_TIM2();
void set_sin_DAC_table(int freq, int chan);
void change_dac_chan_num(int num_dac_chan);

#endif /* DAC_init */