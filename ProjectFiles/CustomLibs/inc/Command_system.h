/**
  ******************************************************************************
  * @file    command_system.h
  * @author  ICV
  * @version V1.0.0
  * @date    08/05/2024
  * @brief   contains Header File.
  * ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef Command_system
#define Command_system

enum mode_setting
{                     //  1 - оба, 0 - один канал     АЦП|ЦАП
  adc1_dac1   = 0,    // 1ый канал АЦП, 1ый канал ЦАП   0 0
  adc1_dac12  = 1,    // 1ый канал АЦП, 2 канала ЦАП    0 1
  adc12_dac1  = 2,    // 2 канала АЦП, 1ый канала ЦАП   1 0
  adc12_dac12 = 3,    // 2 канала АЦП, 2 канала ЦАП     1 1
  dac_mode = 1000,    // Режим потоковой передачи в DAC, АЦП отключен
};
int is_valid_mode_setting(int x)
{
  return((0 <= x) && (x <= 3));
};

int execute_command(char *command);
void set_mode_setting(enum mode_setting mode);

#endif /* Command_system */