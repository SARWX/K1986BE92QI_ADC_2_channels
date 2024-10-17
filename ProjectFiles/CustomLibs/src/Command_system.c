/**
  ******************************************************************************
  * @file    Command_system.c
  * @author  ICV
  * @version V1.0.0
  * @date    08/05/2024
  * @brief   This file contains command system for project.
  * ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_usb_CDC.h"
#include "MDR32F9Qx_dma.h"
#include "MDR32F9Qx_timer.h"
#include "MDR32F9Qx_adc.h"
#include <string.h>
#include <stdlib.h>
#include "ADC_init.h"
#include "defines.h"
#include "DAC_init.h"
#include "Command_system.h"

extern uint16_t DAC_table[SIN_RES];                                 // Внешняя таблица значений ЦАП
extern DMA_CtrlDataInitTypeDef TIM2_primary_DMA_structure;          // Внешние структуры DMA
extern DMA_CtrlDataInitTypeDef TIM2_alternate_DMA_structure;        // Внешние структуры DMA

enum mode_setting mode = 3;                                         // Режим работы устройства (по умолчанию режим = 3)

float get_voltage_num(char *command, int *i);                       // функция преобразования числа строкового формата в число с плавающей точкой
int convert_voltage_to_register_val(float voltage);                 // функция переводящая значение в вольтах в значение регистра ЦАП

/**
  * @brief : 
  * function for execution the command.
  * @param  command - command to excute.
  * @retval None
  */

int execute_command(char *command) 
{
// ------------- "set freq " command ------------------------------------------------------------ //
  if (strstr(command, "set freq ") == command) 
  {                    // проверить: команда начинается с "set freq "?
    int freq = atoi((char *)(command + strlen("set freq ")));       // перевести freq из строкового формата в int
      set_sin_DAC_table(freq, 1);                                          // задать синусоиду требуемой частоты в DAC_table (в первый канал)
  }
// ---------------------------------------------------------------------------------------------- //

// ---------------- "set " command -------------------------------------------------------------- //
  else if (strstr(command, "set ") == command)                      // проверить: команда начинается с "set "?
  {
    static int DAC_table_buf[SIN_RES*2];                              // буфер DAC_table_buf
    int i = 4;                                                      // 1ый символ числа num
    int buffer_num = 0;                                             // буферная переменная
    static int j = 0;                                               // индекс таблицы DAC_table_buf
    while ((command[i] != 0) && (command[i] != '\n')                // пока строка не закончена
    && (command[i] != '\r') && (command[i] != '!'))                 // пока строка не закончена
    {
      float voltage_num = get_voltage_num(command, &i);             // получить число в формате X.XX
      if (voltage_num == -1.0)  
      {
        break;                                                      // неверное значение, прекратить выполнение
      }
      int reg_val = convert_voltage_to_register_val(voltage_num);   // конвертировать значение напряжения в значение регистра для ЦАП
      DAC_table_buf[j] = reg_val;                                   // занести значение в таблицу DAC_table_buf
      j += 1;                                                       // инкрементировать индекс DAC_table_buf
      if (command[i] == ' ')                                        // проверить если следующий символ это пробел, 
      {
        i += 1;                                                     // то пропустить его
      }
    }
  
    if(command[i] == '!')                                           // передача завершена
    {
      int iter = (SIN_RES*2) / j;                                       // сколько периодов нашего сигнала уложится в буфер для передачи
      for (int l = 0; l < iter; l++)                                // для каждого из умещающихся периодов
      {
        for (int k = 0; k <= j; k++)                                  
        {
          DAC_table[((l * j) + k)] = DAC_table_buf[k];              // скопировать значения в DAC_table
        }
      }
      TIM2_primary_DMA_structure.DMA_CycleSize = (iter * j);		    // Сколько измерений (DMA передач) содержит 1 DMA цикл
      TIM2_alternate_DMA_structure.DMA_CycleSize = (iter * j);	    // Сколько измерений (DMA передач) содержит 1 DMA цикл
      j = 0;                                                        // сбросим индекс DAC_table_buf в 0
    }
  }
// ---------------------------------------------------------------------------------------------- //

// ------------- "dac_mode " command ------------------------------------------------------------ //
  if (strstr(command, "dac_mode") == command) 
  {                    // проверить: команда начинается с "dac_mode"?
    // Выключить таймер (остановить ЦАП)
    // TIMER_Cmd(MDR_TIMER2, DISABLE);
   	// NVIC_DisableIRQ(DMA_IRQn);
    mode = dac_mode_s;
    return(1);
  }
// ---------------------------------------------------------------------------------------------- //


// ------------- "mode " command ------------------------------------------------------------ //
  if (strstr(command, "mode ") == command) 
  {                     // проверить: команда начинается с "mode "?
    int tmp_mode = atoi((char *)(command + strlen("mode ")));       // перевести режим из строкового формата в int
    mode = (is_valid_mode_setting(tmp_mode) ? tmp_mode : mode);     // обновить mode только если значение валидное
    set_mode_setting(mode);   // задать требуемый режим

  }
// ---------------------------------------------------------------------------------------------- //

// ------------- "clock " command ------------------------------------------------------------ //
  if (strstr(command, "clock ") == command) 
  {                    // проверить: команда начинается с "clock "?
    // Настройка частоты для ADC
    if (strstr(command, "ADC ") == command + strlen("clock ")) {
      int new_clock = atoi((char *)(command + strlen("clock ADC ")));       // перевести new_clock из строкового формата в int
      reconfig_ADC_clock(new_clock, mode);
    }
    // Настройка частоты для DAC
    if (strstr(command, "DAC ") == command + strlen("clock ")) {
      int new_clock = atoi((char *)(command + strlen("clock DAC ")));       // перевести new_clock из строкового формата в int
      reconfig_DAC_clock(new_clock, mode);
    }
 }
// ---------------------------------------------------------------------------------------------- //

  return(0);
}
/** @example Commands 
 *  command can be sent to the MCU through USB or specified in code \n
  * \n List of the commands: \n
  * \n \b "set \b freq \b X"      this command will set sinusoid with specified frequence in DAC table \n
  * \b "set \b freq \b 100" configures DAC to 100 HZ \n
  * \n \b "set \b X.X \b Y.Y \b ... \b Z.Z \b !"      this command will set specified voltage values in DAC table \n
  * \b "set \b 2.0 \b 0.0 \b !" configures DAC repetitively transmit 2.0 V and then 0.0 V \n
  * \n Notice, that if you transmit command through USB MAX command length = 64 bytes, \n
  * So that transmit this command in separate messages, it won't be executed while you \n
  * won't transmit ! at the end of set command 
  */


/**
  * @brief :
  *  
  * function for extraction voltage value from command and converting it from str to float.
  * @param  command - command string from where to extract the voltage value.
  * @param  i - index of the value to be extracted.
  * @retval value of the extracted voltage 
  */
  float get_voltage_num(char *command, int *i)                      // передаем i по ссылке, а не по значению
  {
  float num = 0.0;
    if ((command[*i] >= '0') && (command[*i] <= '9'))               // проверка того, что это цифра
    {
      num = (command[*i] - '0');
      *i += 1;                                                      // инкрементировать индекс
    }
    else  
    {
      return(-1);                                                   // ошибка при вводе
    }
    if (command[*i] == '.')  
    {
      *i += 1;                                                      // пропустить символ '.'
    }
    else  
    {
      return(-1);                                                   // ошибка при вводе
    }
    float d = 10.0;
    while ((command[*i] >= '0') && (command[*i] <= '9'))  
    {
      num += (float)((command[*i] - '0') / d);
      d *= 10.0;
      *i += 1;
    }
    if(num > 3.3)                                                   // проверить не выходит ли напряжение за установленный максимум
    {
      return(-1);
    }
    return(num);
  }

/**
  * @brief : 
  * function for convertion voltage value from float to 
  * K1986BE92QI specific register value.
  * @param  voltage - voltage value.
  * @retval register value - voltage converted to the K1986BE92QI DAC specific type
  */
int convert_voltage_to_register_val(float voltage) 
{
  voltage /= 3.3;           // перевод в проценты от 3.3 вольт (максимума)
  voltage *= 4095;          // перевод в регистровое значение (4095 - максимум)
  return((int)voltage);     // преобразование к типу int
}

void set_mode_setting(enum mode_setting mode)
{
  // Выключение АЦП и таймера
	ADC1_Cmd(DISABLE);
	ADC2_Cmd(DISABLE);
  TIMER_Cmd(MDR_TIMER2, DISABLE);

  // 1 устрановка АЦП
  int num_adc_chan = ((int)mode >> 1) + 1;
  change_adc_chan_num(num_adc_chan);

  // 2 установка каналов ЦАП
  int num_dac_chan = ((int)mode % 2) + 1;
  change_dac_chan_num(num_dac_chan);

  // Включение АЦП и таймера
	ADC1_Cmd(ENABLE);
	ADC2_Cmd(ENABLE);
  TIMER_Cmd(MDR_TIMER2, ENABLE);

		// NVIC_EnableIRQ(USB_IRQn);
		// NVIC_EnableIRQ(ADC_IRQn);
		// NVIC_EnableIRQ(DMA_IRQn);
    // NVIC_DisableIRQ(DMA_IRQn);
    // NVIC_DisableIRQ(ADC_IRQn);
    // NVIC_DisableIRQ(Timer2_IRQn);
}

int is_valid_mode_setting(int x)
{
  return((0 <= x) && (x <= 3));
};

/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE Command_system.c */