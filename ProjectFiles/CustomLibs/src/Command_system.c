#include "MDR32F9Qx_usb_CDC.h"
#include <string.h>
#include <stdlib.h>
#include "ADC_init.h"
#include "defines.h"
#include "DAC_init.h"

void execute_command(char *command) {
  if (strstr(command, "set freq ") == command) {
    int freq = atoi((char *)(command + strlen("set freq ")));
      set_DAC_table(freq);
  }
  else if (strstr(command, "set ") == command) {
    int i = 4;                                                                    // 1ый символ числа num
    int buffer_num = 0;                                                           // буферная переменная
    int j = 0;                                                                    // индекс таблицы DAC_table 
    while ((command[i] != 0) && (command[i] != '\n') && (command[i] != '\r')) {   // пока строка не закончена
      if ((command[i] >= '0') && (command[i] <= '9')) {                           // проверка того, что это цифра
        buffer_num *= 10;                                                         // новый разряд числа
        buffer_num += (command[i] - '0');                                         // прибавить разряд
        i += 1;                                                                   // инкрементировать 
      }
      else if (command[i] == ',') {
        i += 2;                                                                   // пропустить сиволы ',' и ' '
        DAC_table[j] = buffer_num;                                                // занести новое значение
        j++;                                                                      // инкрементировать индекс таблицы DAC_table
      }
      else {
        break;                                                                    // допущенна ошибка при вводе
      }
    }
    
  }
  
}
