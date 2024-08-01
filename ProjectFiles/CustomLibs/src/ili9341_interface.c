#include "ili9341.h"
#include "ili9341_interface.h"
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
#define ARROW_SIDE 38

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
		uint16_t point = LCD_H - ((arr[i]) * LCD_H) / MAX_ADC_VAL;
		// int j = i/2;
		ili9341_drawpixel(cur_x, clear_arr[cur_x], BLACK);
		clear_arr[cur_x] = point;
		ili9341_drawpixel(cur_x, point, GREEN);
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
// Передаем левый верхний угол
void draw_arrow(int x, int y, enum direction j, uint16_t color)		// x1 = 320 - 48;  y1 = 13  сторона = 38
{
	// 1 Рисуем рамку
	ili9341_drawvline(x, y, ARROW_SIDE, WHITE);					// | 	 |=>    =====
	ili9341_drawhline(x, y, ARROW_SIDE, WHITE);					// --	 |=>   ||   ||
	ili9341_drawhline(x, (y + ARROW_SIDE), ARROW_SIDE, WHITE);	// __	 |=>   ||   ||
	ili9341_drawvline((x + ARROW_SIDE), y, ARROW_SIDE, WHITE);	//   |	 |=>    =====
	// 2 Рисуем background
	ili9341_fillrect(x+1, y+1, ARROW_SIDE-1, ARROW_SIDE-1, color);
	// 3 Рисуем стрелку
	ili9341_filltriangle(x + (ARROW_SIDE/2), y + (ARROW_SIDE/2), 1, j * ((ARROW_SIDE/2) - 3), WHITE);		
	ili9341_filltriangle(x + (ARROW_SIDE/2), y + (ARROW_SIDE/2), 1, j * ((ARROW_SIDE/4) - 2), color);		
	ili9341_filltriangle(x + (ARROW_SIDE/2), y + (ARROW_SIDE/2), -1, j * ((ARROW_SIDE/2) - 3), WHITE);	
	ili9341_filltriangle(x + (ARROW_SIDE/2), y + (ARROW_SIDE/2), -1, j * ((ARROW_SIDE/4) - 2), color);
	if (j == up)	
		ili9341_fillrect(x + ((ARROW_SIDE/2) - (ARROW_SIDE/6)/2), y + (ARROW_SIDE/3), (ARROW_SIDE/6), 2*(ARROW_SIDE/3) - 4, WHITE);	
	else
		ili9341_fillrect(x + ((ARROW_SIDE/2) - (ARROW_SIDE/6)/2), y + 4, (ARROW_SIDE/6), 2*(ARROW_SIDE/3), WHITE);	
	ili9341_fillrect(x+1, y+1, ARROW_SIDE/5, ARROW_SIDE-1, color);
	ili9341_fillrect(x + ARROW_SIDE - ARROW_SIDE/5, y + 1, ARROW_SIDE/5, ARROW_SIDE-1, color);
}


void display_main_menu(void)
{
	draw_func_block(1, "set freq", 3);
	draw_func_block(2, "channels ctrl", 3);
	draw_func_block(3, "scan property", 3);
	draw_func_block(4, "ampl property", 3);
	draw_arrow(320 - 48, 13, up, BLUE);
	draw_arrow(320 - 48, 240 - 13 - ARROW_SIDE, down, BLUE);
	// draw_button_ok();
	// draw_button_back();
	// ili9341_drawchar(2, 2, 't', 0xffff, 0x0000, 5);
	// print_str("hello", 2, 2, 0xffff, 0x0000, 5);
	// ili9341_filltriangle(0, 0, 100, 100, WHITE);
}


// TOUCH Features
/**
  * @brief  this function draws cursor on the screen 
  * @param  x - x coordinate
  * @param  y - y coordinate
  * @retval None
  */
void draw_touch_cursor(uint16_t x, uint16_t y)
{
	static uint16_t prev_x = 0, prev_y = 0;
	static uint16_t color_under_cursor = YELLOW;
	// 1 - возвращаем предыдущий цвет
	ili9341_drawpixel(prev_x, prev_y, color_under_cursor);
	// 2 - запоминаем новые координаты курсора
	prev_x = x;
	prev_y = y;
	// 3 -  запоминаем цвет под курсором 
	color_under_cursor = YELLOW;		// рисовалка
	// 4 - рисуем курсор
	ili9341_drawpixel(x, y, color_under_cursor);
}