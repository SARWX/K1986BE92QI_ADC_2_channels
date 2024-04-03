#include "ili9341.h"
#include <stdint.h>
#include "MDR32F9Qx_ssp.h"
#include "MDR32F9Qx_port.h"
#include "MDR32Fx.h"
#include "delay.h"
#include "defines.h"

extern uint16_t LCD_W;
extern uint16_t LCD_H;


void dysplay_signal(uint16_t *arr, int size, int signal_number, int skip_every)
{
	static int cur_x = 0;
	static int skip_flag = 0;
	// signal_number--;	// 0 = 1ый канал, 1 = 2ой канал
	static uint16_t clear_arr[ILI9341_TFTWIDTH];
	for (int i = (signal_number - 1); i < size; i+=2) 
	{
		if (((cur_x % skip_every) == 0) && (skip_flag == 0))
		{
			skip_flag = 1;
			continue;
		}
		uint16_t point = ((arr[i]) * 240) / MAX_ADC_VAL;
		// int j = i/2;
		ili9341_drawpixel(clear_arr[cur_x], cur_x, BLACK);
		clear_arr[cur_x] = point;
		ili9341_drawpixel(point, cur_x, GREEN);
		if (++cur_x >= LCD_W)
		{
			cur_x = 0;
		}
		skip_flag = 0;
	}
	// Очистим экран
	// for (int i = start_point; i < (start_point + size); i++) 
	// {
	// 	ili9341_drawpixel((((arr[i - start_point]) * 240) / MAX_ADC_VAL), i, BLACK);
	// }
}