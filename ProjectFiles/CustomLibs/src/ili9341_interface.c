#include "ili9341.h"
#include "ili9341gfx.h"
#include <stdint.h>
#include "MDR32F9Qx_ssp.h"
#include "MDR32F9Qx_port.h"
#include "MDR32Fx.h"
#include "delay.h"
#include "defines.h"

#define GAP 8
#define BLOCK_H 54
#define BLOCK_W 250

extern uint16_t LCD_W;
extern uint16_t LCD_H;


void display_signal(uint16_t *arr, int size, int signal_number, int skip_every)
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


void print_str(char* str, int x, int y, uint16_t color, uint16_t bg, uint8_t size)
{
	while (*str)
	{
		ili9341_drawchar(x, y, *str, color, bg, size);
		x += 6 * size;				// Подвинуть курсор (шрифт моноширинный, 6 квадратов в ширину, 7 в высоту, сторона одного квадрата задается через size)
		str++;
	}
	
}

int draw_box(int row_num, uint16_t color)
{
	// 1 определим левую нижнюю координату блока (по высоте)
	int coordinate = (row_num - 1) * (GAP + BLOCK_H);
	// 2 нарисуем рамки
	ili9341_drawvline(0, coordinate, BLOCK_H, color);				// ||
	ili9341_drawvline(1, coordinate, BLOCK_H, color);				// ||
	ili9341_drawhline(0, coordinate, BLOCK_W, color);				//   --
	ili9341_drawhline(0, (coordinate+1), BLOCK_W, color);			//   --
	ili9341_drawvline(BLOCK_W, coordinate, BLOCK_H, color);			//     ||
	ili9341_drawvline((BLOCK_W-1), coordinate, BLOCK_H, color);		//     ||
	ili9341_drawhline(0, (coordinate-1 + BLOCK_H), BLOCK_W, color);	//   __
	ili9341_drawhline(0,( coordinate-2 + BLOCK_H), BLOCK_W, color);	//   __
	return coordinate;
}


void draw_func_block(int row_num, char *str, int font_size)
{
	// 1 рисуем рамку блока, получаем координату блока (по высоте)
	int coordinate = draw_box(row_num, BLUE);
	// 3 определим координаты для размещения текста в центре
	int len = 0;
	while (str[len])
		len++;
	int x_center = 2 + ((BLOCK_W - len * 6 * font_size) / 2);
	int y_center = coordinate + (BLOCK_H - 7 * font_size) / 2;
	// 4 поместим текст в центр
	print_str(str, x_center, y_center, WHITE,BLACK, font_size);

}


void display_main_menu(void)
{
	draw_func_block(1, "set freq", 3);
	draw_func_block(2, "channels ctrl", 3);
	draw_func_block(3, "scan property", 3);
	draw_func_block(4, "ampl property", 3);
	// draw_arrow_up();
	// draw_button_ok();
	// draw_button_back();
	// ili9341_drawchar(2, 2, 't', 0xffff, 0x0000, 5);
	// print_str("hello", 2, 2, 0xffff, 0x0000, 5);
	ili9341_filltriangle(0, 0, 100, 100, WHITE);
}
