/**
  ******************************************************************************
  * @file    command_sys_flex.h
  * @author  ICV
  * @version V1.1.0
  * @date    19/10/2024
  * @brief   contains Header File.
  * ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef Command_system
#define Command_system

/**
  * @brief type for describing current mode
  */
enum mode_setting
{                       //  1 - оба, 0 - один канал     АЦП|ЦАП
  adc1_dac1   = 0,      // 1ый канал АЦП, 1ый канал ЦАП   0 0
  adc1_dac12  = 1,      // 1ый канал АЦП, 2 канала ЦАП    0 1
  adc12_dac1  = 2,      // 2 канала АЦП, 1ый канала ЦАП   1 0
  adc12_dac12 = 3,      // 2 канала АЦП, 2 канала ЦАП     1 1
  dac_mode_s = 1000,    // Режим потоковой передачи в DAC, АЦП отключен
};

/** @defgroup __Specific_commands Specific command system
  * @{
  */

int is_valid_mode_setting(int x);

int get_adc_chan_num(enum mode_setting mode);

int get_dac_chan_num(enum mode_setting mode);

int execute_command(char *command);
void set_mode_setting(enum mode_setting mode);

/** @} */ /* End of group __Specific_commands */

#endif /* Command_system */

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE command_sys_flex.h */