#include "ADC_for_proj.h"
#include "defines_for_proj.h"
#include "MDR32F9Qx_usb_CDC.h"
#include "DAC_for_proj.h"
#include <string.h>
#include <stdlib.h>

void execute_command(char *command) {
  if (strstr(command, "set freq ") == command) {
    int freq = atoi((char *)(command + strlen("set freq ")));
    if (freq >= 100) {                                          // MIN freq = 100
      Set_DAC_Table(freq);
    }
  }
}
