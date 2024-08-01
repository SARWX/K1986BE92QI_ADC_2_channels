/**
  ******************************************************************************
  * @file    sys_CLK_init.c
  * @author  ICV
  * @version V1.0.0
  * @date    08/05/2024
  * @brief   sys_CLK initialization Header File.
  * ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SysCLK_init
#define SysCLK_init
#include <stdint.h>

void Setup_CPU_Clock(void);
void delay_tick(uint32_t count);
#endif /* SysCLK_init */
