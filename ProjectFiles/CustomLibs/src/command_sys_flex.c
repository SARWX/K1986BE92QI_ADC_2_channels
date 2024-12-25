/**
  ******************************************************************************
  * @file    command_sys_flex.c
  * @author  ICV
  * @version V1.1.0
  * @date    19/10/2024
  * @brief   This file contains command system for project.
  * ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_usb_CDC.h"
#include "MDR32F9Qx_dma.h"
#include "MDR32F9Qx_timer.h"
#include "MDR32F9Qx_adc.h"
#include "MDR32F9Qx_ssp.h"
#include "MDR32F9Qx_port.h"
#include <string.h>
#include <stdlib.h>
#include "adc.h"
#include "defines.h"
#include "pins.h"
#include "dac.h"
#include "spi.h"
#include "command_sys_flex.h"

// внешние переменные
extern uint16_t DAC_table[SIN_RES];
extern DMA_CtrlDataInitTypeDef TIM2_primary_DMA_structure;    
extern DMA_CtrlDataInitTypeDef TIM2_alternate_DMA_structure;  

enum mode_setting mode = 3;   /* режим работы устройства */

float get_voltage_num(const char *command, int *i); 
int convert_voltage_to_register_val(float voltage);

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
      set_sin_DAC_table(freq, 1, get_dac_chan_num(mode));           // задать синусоиду требуемой частоты в DAC_table (в первый канал)
  }
// ---------------------------------------------------------------------------------------------- //

// ---------------- "set " command -------------------------------------------------------------- //
  else if (strstr(command, "set ") == command)                      // проверить: команда начинается с "set "?
  {
    static int DAC_table_buf[SIN_RES*2];                            // буфер DAC_table_buf
    int i = (int)strlen("set ");                                    // 1ый символ числа num
    int buffer_num = 0;                                             // буферная переменная
    static int j = 0;                                               // индекс таблицы DAC_table_buf
    while ((command[i] != 0) && (command[i] != '\n')                // пока строка не закончена
    && (command[i] != '\r') && (command[i] != '!'))                 // пока строка не закончена
    {
      float voltage_num = get_voltage_num(command, &i);              // получить число в формате X.XX
      if (voltage_num == -1)  
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
      int iter = (SIN_RES*2) / j;                                   // сколько периодов нашего сигнала уложится в буфер для передачи
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
    mode = dac_mode_s;
    return(1);
  }
// ---------------------------------------------------------------------------------------------- //

// ------------- "mode " command ---------------------------------------------------------------- //
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
    if (strstr(command, "ADC ") == command + strlen("clock ")) 
    {
      int new_clock = atoi((char *)(command + strlen("clock ADC ")));       // перевести new_clock из строкового формата в int
      reconfig_ADC_clock(new_clock, get_adc_chan_num(mode));
    }
    // Настройка частоты для DAC
    if (strstr(command, "DAC ") == command + strlen("clock ")) 
    {
      int new_clock = atoi((char *)(command + strlen("clock DAC ")));       // перевести new_clock из строкового формата в int
      reconfig_DAC_clock(new_clock, get_dac_chan_num(mode));
    }
 }
// ---------------------------------------------------------------------------------------------- //

// ------------- "spi1_send " command ------------------------------------------------------------ //
  if (strstr(command, "spi1_send ") == command) 
  {                    // проверить: команда начинается с "spi1_send "?
    uint8_t *data_to_send = (uint8_t *)(command + strlen("spi1_send "));
    uint8_t len_of_message = *data_to_send;       // прочитать длину транзакции в байтах
    data_to_send += strlen("X ");     // 1ый байт 'X' - размер транзакции в байтах
                                      // 2ой байт ' ' - пробел

    PORT_ResetBits(Port_SPI_CS_Display, Pin_SPI_CS_Display); 	// cs = 0
    // Port_SPI_CS_Display->RXTX &= ~(Pin_SPI_CS_Display);			// cs = 0
    for(int i = 0; i < len_of_message; i++)
    {
      SSP_SendData(MDR_SSP1, (uint16_t)(data_to_send[i]));    // SSP настроен на работу с 8 битными данными, 
                                                              // но функция принимает uint16_t, поэтому надо привести тип
    }
    while (SSP_GetFlagStatus(MDR_SSP1, SSP_FLAG_BSY))
      ;
    PORT_SetBits(Port_SPI_CS_Display, Pin_SPI_CS_Display); 	// cs = 1
    // Port_SPI_CS_Display->RXTX |= Pin_SPI_CS_Display;			  // cs = 1
  }
// ---------------------------------------------------------------------------------------------- //

  return(0);
}
/**
 * @example Commands 
 * Commands can be sent to the MCU through USB or specified in code.
 * 
 * ### List of the commands:
 * 
 * - **set freq X1**
 *   This command sets a sinusoidal signal with the specified frequency in the DAC table.  
 *   Example:  
 *   ``` set freq 100 ``` configures DAC to 100 Hz.
 * 
 * - **set X.X Y.Y ... Z.Z**  
 *   This command sets the specified voltage values in the DAC table.  
 *   Example:  
 *   ``` set 2.0 0.0 ! ``` configures DAC to repetitively transmit 2.0 V and then 0.0 V.
 * 
 * > [!note] \n
 * > When transmitting a command through USB, the maximum command length is 64 bytes.  
 * > Therefore, transmit this command in separate messages. The command will not be executed until you transmit **!** at the end of the **set** command.
 * \n
 */

/**
  * @brief :
  *  
  * function for extraction voltage value from command and converting it from str to float.
  * @param  command - command string from where to extract the voltage value.
  * @param  i - index of the value to be extracted.
  * @retval value of the extracted voltage 
  */
  float get_voltage_num(const char *command, int *i)   // передаем i по ссылке, а не по значению
  {
  float num = 0.0;
    if ((command[*i] >= '0') && (command[*i] <= '9'))   // проверка того, что это цифра
    {
      num = (command[*i] - '0');
      *i += 1;   // инкрементировать индекс
    }
    else  
    {
      return(-1);   // ошибка при вводе
    }
    if (command[*i] == '.')  
    {
      *i += 1;   // пропустить символ '.'
    }
    else  
    {
      return(-1);   // ошибка при вводе
    }
    float d = 10.0;
    while ((command[*i] >= '0') && (command[*i] <= '9'))  
    {
      num += (float)((command[*i] - '0') / d);
      d *= 10.0;
      *i += 1;
    }
    if(num > 3.3)   // проверить не выходит ли напряжение за установленный максимум
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
  voltage /= 3.3;         // перевод в проценты от 3.3 вольт (максимума)
  voltage *= 4095;        // перевод в регистровое значение (4095 - максимум)
  return((int)voltage);   // преобразование к типу int
}

/**
  * @brief : 
  * function to set desired mode.
  * @param  mode - mode to set.
  * @retval None
  */
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
}

/**
  * @brief : 
  * function to check if x - correct mode_setting.
  * @param  x - value to test.
  * @retval 1 - valid, 0 - not valid
  */
int is_valid_mode_setting(int x)
{
  return((0 <= x) && (x <= 3));
};


/**
  * @brief returns number of current adc channels 
  * @param  mode - current operating mode
  * @retval number of channels (1 = 1)
  */
int get_adc_chan_num(enum mode_setting mode)
{
  int adc_chan = ((mode & 0x2) >> 1);
  return(adc_chan + 1);
}


/**
  * @brief returns number of current dac channels 
  * @param  mode - current operating mode
  * @retval number of channels (1 = 1)
  */
int get_dac_chan_num(enum mode_setting mode)
{
  int dac_chan = (mode & 0x1);
  return(dac_chan + 1);
}
/*********************** (C) COPYRIGHT 2024 ICV ****************************
*
* END OF FILE command_sys_flex.c */