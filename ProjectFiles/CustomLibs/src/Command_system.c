#include "MDR32F9Qx_usb_CDC.h"
#include "MDR32F9Qx_dma.h"
#include <string.h>
#include <stdlib.h>
#include "ADC_init.h"
#include "defines.h"
#include "DAC_init.h"

// Внешняя таблица значений ЦАП
extern uint16_t DAC_table[SIN_RES];
// Внешние структуры DMA
extern DMA_CtrlDataInitTypeDef TIM2_primary_DMA_structure;
extern DMA_CtrlDataInitTypeDef TIM2_alternate_DMA_structure;

float get_voltage_num(char *command, int *i);
int convert_voltage_to_register_val(float voltage);


void execute_command(char *command) {
// ------------- "set freq " command ------------------------------------------------------------ //
  if (strstr(command, "set freq ") == command) {
    int freq = atoi((char *)(command + strlen("set freq ")));
      set_DAC_table(freq);
  }
// ---------------------------------------------------------------------------------------------- //

// ---------------- "set " command -------------------------------------------------------------- //
  else if (strstr(command, "bet ") == command) {
    int DAC_table_buf[SIN_RES];                                                    // буфер DAC_table_buf
    int i = 4;                                                                    // 1ый символ числа num
    int buffer_num = 0;                                                           // буферная переменная
    int j = 0;                                                                    // индекс таблицы DAC_table_buf
    while ((command[i] != 0) && (command[i] != '\n') && (command[i] != '\r')) {   // пока строка не закончена
      float voltage_num = get_voltage_num(command, &i);                           // получить число в формате X.XX
      if (voltage_num == -1.0) {
        break;                                                                    // неверное значение, прекратить выполнение
      }
      int reg_val = convert_voltage_to_register_val(voltage_num);                 // конвертировать значение напряжения в значение регистра для ЦАП
      DAC_table_buf[j] = reg_val;                                                     // занести значение в таблицу DAC_table_buf
      j += 1;
      if (command[i] == ' ') {                                                    // проверить если следующий символ это пробел, 
        i += 1;                                                                   // то пропустить его
      }
    }

    // ЗАПОЛНИМ ВСЮ ТАБЛИЦУ
    int iter = SIN_RES / j;                                                       // сколько периодов нашего сигнала уложится в буфер для передачи
    for (int l = 0; l < iter; l++) {
      for (int k = 0; k <= j; k++) {
        DAC_table[((l * j) + k)] = DAC_table_buf[k];                                            // скопировать значения в DAC_table
      }
    }
    TIM2_primary_DMA_structure.DMA_CycleSize = (iter * j);								                // Сколько измерений (DMA передач) содержит 1 DMA цикл
    TIM2_alternate_DMA_structure.DMA_CycleSize = (iter * j);							                // Сколько измерений (DMA передач) содержит 1 DMA цикл
  }
// ---------------------------------------------------------------------------------------------- //
}

  float get_voltage_num(char *command, int *i) {                                        // передаем i по ссылке, а не по значению
  float num = 0.0;
    if ((command[*i] >= '0') && (command[*i] <= '9')) {                           // проверка того, что это цифра
      num = (command[*i] - '0');
      *i += 1;                                                                    // инкрементировать индекс
    }
    else {
      return(-1);                                                                 // ошибка при вводе
    }
    if (command[*i] == '.') {
      *i += 1;                                                                    // пропустить символ '.'
    }
    else {
      return(-1);                                                                 // ошибка при вводе
    }
    float d = 10.0;
    while ((command[*i] >= '0') && (command[*i] <= '9')) {
      num += (float)((command[*i] - '0') / d);
      d *= 10.0;
      *i += 1;
    }
    if(num > 3.3) {                                                               // проверить не выходит ли напряжение за установленный максимум
      return(-1);
    }
    return(num);
  }

int convert_voltage_to_register_val(float voltage) {
  voltage /= 3.3;                                       // перевод в проценты от 3.3 вольт (максимума)
  voltage *= 4095;                                      // перевод в регистровое значение (4095 - максимум)
  return((int)voltage);                                  // преобразование к типу int
}

//     while ((command[i] != 0) && (command[i] != '\n') && (command[i] != '\r')) {   // пока строка не закончена
//       if ((command[i] >= '0') && (command[i] <= '9')) {                           // проверка того, что это цифра
//         buffer_num *= 10;                                                         // новый разряд числа
//         buffer_num += (command[i] - '0');                                         // прибавить разряд
//         i += 1;                                                                   // инкрементировать 
//       }
//       else if (command[i] == '.') {
//         i += 2;                                                                   // пропустить сивол '.'
//         DAC_table[j] = buffer_num;                                                // занести новое значение
//         j++;                                                                      // инкрементировать индекс таблицы DAC_table
//       }
//       else {
//         break;                                                                    // допущенна ошибка при вводе
//       }
//     }
    
//   }
  
// }
