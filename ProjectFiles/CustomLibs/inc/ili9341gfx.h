/**
  ******************************************************************************
  * @file    _
  * @author  ICV
  * @version V1.0.0
  * @date    08/05/2024
  * @brief   This file contains _
  * ******************************************************************************
  */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ILI9341GFX_H_
#define _ILI9341GFX_H_

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

void ili9341_drawchar(int16_t x, int16_t y, unsigned char c,uint16_t color, uint16_t bg, uint8_t size);
void ili9341_setcursor(uint16_t x,uint16_t y);
void ili9341_settextcolour(uint16_t x,uint16_t y);
void ili9341_settextsize(uint8_t s);
void ili9341_write(uint8_t c);
void backuplocationvset(void);
void backuplocationvactual(void);
void backuplocationiset(void);
void backuplocationiactual(void);
void display_init(void);

#endif
