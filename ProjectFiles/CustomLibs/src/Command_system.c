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
}
