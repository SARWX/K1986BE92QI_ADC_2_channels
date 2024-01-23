#include "MDR32F9Qx_usb_CDC.h"
#include <string.h>
#include <stdlib.h>
#include "ADC_init.h"
#include "defines.h"
#include "DAC_init.h"

void execute_command(char *command) 
{
  if (strstr(command, "set freq ") == command) 
  {
    int freq = atoi((char *)(command + strlen("set freq ")));

    if (freq >= 100) // MIN freq = 100
    {                                          
      set_DAC_table(freq);
    }
  }
}
