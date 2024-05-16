#include "ili9341.h"
#include "SPI_init.h"
#include <stdint.h>
#include "MDR32F9Qx_ssp.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_usb_handlers.h"
#include "MDR32Fx.h"
#include "delay.h"
#include "defines.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

// Для touch screen команды на чтение координат
#define READ_Y 0xD0
#define READ_X 0x90
// Для touch screen максимальные и минимальные значения
#define XPT2046_MIN_RAW_X 1500		//		//
#define XPT2046_MAX_RAW_X 30000		// 		//
#define XPT2046_MIN_RAW_Y 2000		//		//
#define XPT2046_MAX_RAW_Y 32000		//		//
#define AVG_NUM 16

// Для USB отладки
char debugString[100];


volatile uint16_t LCD_W=ILI9341_TFTWIDTH;
volatile uint16_t LCD_H=ILI9341_TFTHEIGHT;

// SSP control structure
extern SSP_InitTypeDef SSP1_struct;

void test(void)
{
	// TEST
	for (int x = 0; x < 320; x+=10)
	{
		for (int y = 0; y < LCD_W; y++)
		{
			ili9341_drawpixel(y, x, YELLOW);
		}
	}
	//
}

void ili9341_writecommand8(uint8_t com)			// Передать команду
{
	MDR_PORTB->RXTX &= ~(PORT_Pin_6);			// dc = 0
	MDR_PORTF->RXTX &= ~(PORT_Pin_2);			// cs = 0
	MDR_SSP1->DR = com;
	while (MDR_SSP1->SR & SSP_SR_BSY)			// 1 – модуль SSP в настоящее время передает и/или принимает данные, либо буфер FIFO передатчика не пуст
	{
		;										// wait
	}
	MDR_PORTF->RXTX |= PORT_Pin_2;			// cs = 1
}

void ili9341_writedata8(uint8_t data)			// Передать данные
{
	// PORT_SetBits(MDR_PORTB, PORT_Pin_6);		// dc = 1
	MDR_PORTB->RXTX |= PORT_Pin_6;				// dc = 1
	// PORT_ResetBits(MDR_PORTF, PORT_Pin_2);		// cs = 0
	MDR_PORTF->RXTX &= ~(PORT_Pin_2);			// cs = 0
	// SSP_SendData(MDR_SSP1, data);
	MDR_SSP1->DR = data;
	while (MDR_SSP1->SR & SSP_SR_BSY)			// 1 – модуль SSP в настоящее время передает и/или принимает данные, либо буфер FIFO передатчика не пуст
	{
		;										// wait
	}
	// PORT_SetBits(MDR_PORTF, PORT_Pin_2); 		// cs = 1
	MDR_PORTF->RXTX |= PORT_Pin_2;			// cs = 1
}

void custom_ili9341_setaddress(uint16_t x,uint16_t y)	// set coordinate for print or other function
{
	ili9341_writecommand8(0x2A);
	ili9341_writedata8(x>>8);
	ili9341_writedata8(x);

	ili9341_writecommand8(0x2B);
	// ili9341_writedata8(y1>>8);
	ili9341_writedata8(y);

	ili9341_writecommand8(0x2C);	//meory write
}

void ili9341_setaddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)	// set coordinate for print or other function
{
	ili9341_writecommand8(0x2A);
	ili9341_writedata8(x1>>8);
	ili9341_writedata8(x1);
	ili9341_writedata8(x2>>8);
	ili9341_writedata8(x2);

	ili9341_writecommand8(0x2B);
	ili9341_writedata8(y1>>8);
	ili9341_writedata8(y1);
	ili9341_writedata8(y2);
	ili9341_writedata8(y2);

	ili9341_writecommand8(0x2C);	//meory write
}

void ili9341_hard_reset(void)	// hard reset display (переключить вывод RESET 1 -> 0 -> 1)
{
	PORT_SetBits(MDR_PORTB, PORT_Pin_7); 		// RESET = 1
	delay_ms(200);
	PORT_ResetBits(MDR_PORTB, PORT_Pin_7);		// RESET = 0
	delay_ms(200);
	PORT_SetBits(MDR_PORTB, PORT_Pin_7); 		// RESET = 1
	delay_ms(200);
}

void ili9341_init(void) 	// set up display using predefined command sequence
{
	ili9341_hard_reset();			// Выполнить сброс экрана
	ili9341_writecommand8(0x01);	// Послать команду сброса
	delay_ms(1000);

	// power control A
	ili9341_writecommand8(0xCB);
	ili9341_writedata8(0x39);
	ili9341_writedata8(0x2C);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0x34);
	ili9341_writedata8(0x02);

	// power control B
	ili9341_writecommand8(0xCF);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0xC1);
	ili9341_writedata8(0x30);

	// driver timing control A
	ili9341_writecommand8(0xE8);
	ili9341_writedata8(0x85);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0x78);

	// driver timing control B
	ili9341_writecommand8(0xEA);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0x00);

	// power on sequence control
	ili9341_writecommand8(0xED);
	ili9341_writedata8(0x64);
	ili9341_writedata8(0x03);
	ili9341_writedata8(0x12);
	ili9341_writedata8(0x81);

	// pump ratio control
	ili9341_writecommand8(0xF7);
	ili9341_writedata8(0x20);

	// power control,VRH[5:0]
	ili9341_writecommand8(0xC0);
	ili9341_writedata8(0x23);

	// Power control,SAP[2:0];BT[3:0]
	ili9341_writecommand8(0xC1);
	ili9341_writedata8(0x10);

	// vcm control
	ili9341_writecommand8(0xC5);
	ili9341_writedata8(0x3E);
	ili9341_writedata8(0x28);

	// vcm control 2
	ili9341_writecommand8(0xC7);
	ili9341_writedata8(0x86);

	// memory access control
	ili9341_writecommand8(0x36);
	ili9341_writedata8(0x48);

	// pixel format
	ili9341_writecommand8(0x3A);
	ili9341_writedata8(0x55);

	// frameration control,normal mode full colours
	ili9341_writecommand8(0xB1);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0x18);

	// display function control
	ili9341_writecommand8(0xB6);
	ili9341_writedata8(0x08);
	ili9341_writedata8(0x82);
	ili9341_writedata8(0x27);

	// 3gamma function disable
	ili9341_writecommand8(0xF2);
	ili9341_writedata8(0x00);

	// gamma curve selected
	ili9341_writecommand8(0x26);
	ili9341_writedata8(0x01);

	// set positive gamma correction
	ili9341_writecommand8(0xE0);
	ili9341_writedata8(0x0F);
	ili9341_writedata8(0x31);
	ili9341_writedata8(0x2B);
	ili9341_writedata8(0x0C);
	ili9341_writedata8(0x0E);
	ili9341_writedata8(0x08);
	ili9341_writedata8(0x4E);
	ili9341_writedata8(0xF1);
	ili9341_writedata8(0x37);
	ili9341_writedata8(0x07);
	ili9341_writedata8(0x10);
	ili9341_writedata8(0x03);
	ili9341_writedata8(0x0E);
	ili9341_writedata8(0x09);
	ili9341_writedata8(0x00);

	// set negative gamma correction
	ili9341_writecommand8(0xE1);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0x0E);
	ili9341_writedata8(0x14);
	ili9341_writedata8(0x03);
	ili9341_writedata8(0x11);
	ili9341_writedata8(0x07);
	ili9341_writedata8(0x31);
	ili9341_writedata8(0xC1);
	ili9341_writedata8(0x48);
	ili9341_writedata8(0x08);
	ili9341_writedata8(0x0F);
	ili9341_writedata8(0x0C);
	ili9341_writedata8(0x31);
	ili9341_writedata8(0x36);
	ili9341_writedata8(0x0F);

	// exit sleep
	ili9341_writecommand8(0x11);
	delay_ms(120);
	// display on
	ili9341_writecommand8(0x29);
}

// set colour for drawing
void ili9341_pushcolour(uint16_t colour)
{
	ili9341_writedata8(colour>>8);
	ili9341_writedata8(colour);
}

// clear lcd and fill with colour
void ili9341_clear(uint16_t colour)
{
	uint16_t i,j;
	ili9341_setaddress(0,0,LCD_W-1,LCD_H-1);

	for(i=0;i<LCD_W;i++)
	{
		for(j=0;j<LCD_H;j++)
		{
			ili9341_pushcolour(colour);
		}
	}
}

// draw pixel
void ili9341_drawpixel(uint16_t x3,uint16_t y3,uint16_t colour1) //pixels will always be counted from right side.x is representing LCD width which will always be less tha 240.Y is representing LCD height which will always be less than 320
{
	// if ((x3 < 0) ||(x3 >= LCD_W) || (y3 < 0) || (y3 >= LCD_H))
	// {
	// 	return;
	// }

	ili9341_setaddress(x3,y3,x3+1,y3+1);
	// custom_ili9341_setaddress(x3,y3);
	ili9341_pushcolour(colour1);
	ili9341_pushcolour(colour1);
	ili9341_pushcolour(colour1);
}

// draw vertical line
void ili9341_drawvline(uint16_t x,uint16_t y,uint16_t h,uint16_t colour)//basically we will see this line horizental if we see the display 320*240
{
	if ((x >= LCD_W) || (y >= LCD_H))
	{
		return;
	}

	if((y+h-1) >= LCD_H)
	{
		h=LCD_H-y;
	}

	ili9341_setaddress(x,y,x,y+h-1);

	while (h--)
	{
		ili9341_pushcolour(colour);
	}
}


// draw horizental line

void ili9341_drawhline(uint16_t x,uint16_t y,uint16_t w,uint16_t colour)
{
	if((x >=LCD_W) || (y >=LCD_H))
	{
		return;
	}

	if((x+w-1) >= LCD_W)
	{
		w=LCD_W-x;
	}

	ili9341_setaddress(x,y,x+w-1,y);

	while(w--)
	{
		ili9341_pushcolour(colour);
	}
}

// Нарисовать прямоугольный треугольник
void ili9341_filltriangle(uint16_t x, uint16_t y, int base, int height, uint16_t colour)
{
	while (height != 0)
	{
		if (height > 0)
		{
			ili9341_drawvline(x, y, height, colour);
			height--;
		}
		else 
		{
			ili9341_drawvline(x, (y + height), -height, colour);
			height++;
		}
		// height = (height < 0) ? height + 1: height - 1; 
		x = (base < 0) ? x - 1: x + 1; 
	}
	
}

// draw colour filled rectangle
void ili9341_fillrect(uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t colour)
{
	if ((x >= LCD_W) || (y >= LCD_H))
	{
		return;
	}

	if ((x+w-1) >= LCD_W)
	{
		w = LCD_W-x;
	}

	if ((y+h-1) >= LCD_H)
	{
		h = LCD_H-y;
	}

	ili9341_setaddress(x, y, x+w-1, y+h-1);

	for(y=h; y>0; y--) 
	{
		for(x=w; x>0; x--)
		{
			ili9341_pushcolour(colour);
		}
	}
}
// rotate screen at desired orientation
void ili9341_setRotation(uint8_t m) 
{
	uint8_t rotation;

	ili9341_writecommand8(0x36);
	rotation=m%4;

	switch (rotation) 
	{
		case 0:
			ili9341_writedata8(0x40|0x08);
			// LCD_W = 240;
			// LCD_H = 320;
			LCD_W = 320;
			LCD_H = 240;
			break;
		case 1:
			ili9341_writedata8(0x20|0x08);
			LCD_W  = 320;
			LCD_H = 240;
			break;
		case 2:
			ili9341_writedata8(0x80|0x08);
			LCD_W  = 240;
			LCD_H = 320;
			break;
		case 3:
			ili9341_writedata8(0x40|0x80|0x20|0x08);
			LCD_W  = 320;
			LCD_H = 240;
			break;
	}
}

void Setup_ili9341(void)
{
	ili9341_init();         	// Проинициализировать ili9341
	ili9341_clear(BLACK);   		// Заполнить экран одним цветом
	delay_ms(1000);
	ili9341_setRotation(1); 	// Задать ориентацию БЫЛА 3
}

////// TOUCH ///////
// Передача команды на получение координаты и ее получение
uint16_t ili9341_touch_writecommand8(uint8_t com)			// Передать команду
{
	// Занижаем скорость работы для тача
	SSP_Cmd(MDR_SSP1, DISABLE);
	SSP1_struct.SSP_CPSDVSR = 128;
    SSP1_struct.SSP_SCR = 32;
	SSP_Init(MDR_SSP1, &SSP1_struct);
	SSP_Cmd(MDR_SSP1, ENABLE);

	// MDR_PORTB->RXTX &= ~(PORT_Pin_6);			// dc = 0
	MDR_PORTB->RXTX &= ~(PORT_Pin_10);			// cs = 0 PB10 для touch
	// uint16_t null_fifo_read [16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	MDR_SSP1->DR = com;
	while (MDR_SSP1->SR & SSP_SR_BSY)			// 1 – модуль SSP в настоящее время передает и/или принимает данные, либо буфер FIFO передатчика не пуст
	{
		;										// wait
	}
	// Почистить
	for (int i = 0; i < 8; i++) 
	{
		uint16_t foo = MDR_SSP1->DR; 
	}

	MDR_SSP1->DR = 0;
	while (MDR_SSP1->SR & SSP_SR_BSY)			// 1 – модуль SSP в настоящее время передает и/или принимает данные, либо буфер FIFO передатчика не пуст
	{
		;										// wait
	}
	// Прочитать
	uint16_t temp = 0;
	temp = (uint16_t)(MDR_SSP1->DR);
	temp = temp << 8;
	
	MDR_SSP1->DR = 0;
	while (MDR_SSP1->SR & SSP_SR_BSY)			// 1 – модуль SSP в настоящее время передает и/или принимает данные, либо буфер FIFO передатчика не пуст
	{
		;										// wait
	}
	temp |= (uint16_t)(MDR_SSP1->DR);
	MDR_PORTB->RXTX |= PORT_Pin_10;				// cs = 1
	// MDR_SSP1->DR = (uint16_t) 0;
	// while (MDR_SSP1->SR & SSP_SR_BSY)			// 1 – модуль SSP в настоящее время передает и/или принимает данные, либо буфер FIFO передатчика не пуст
	// {
	// 	;										// wait
	// }
	// uint16_t coordinate = SSP_ReceiveData(MDR_SSP1);
	MDR_PORTB->RXTX |= PORT_Pin_10;				// cs = 1
	// return coordinate;
	
	// Повышаем скорость работы для дисплея
	SSP_Cmd(MDR_SSP1, DISABLE);
	SSP1_struct.SSP_CPSDVSR = 2;
    SSP1_struct.SSP_SCR = 0;
	SSP_Init(MDR_SSP1, &SSP1_struct);
	SSP_Cmd(MDR_SSP1, ENABLE);
	return(temp);
}

// void ili9341_touch_read(uint16_t* z)
// {
// 	// Занижаем скорость работы для тача
// 	SSP_Cmd(MDR_SSP1, DISABLE);
// 	SSP1_struct.SSP_CPSDVSR = 128;
//     SSP1_struct.SSP_SCR = 32;
// 	SSP_Init(MDR_SSP1, &SSP1_struct);
// 	SSP_Cmd(MDR_SSP1, ENABLE);

// 	// MDR_PORTB->RXTX &= ~(PORT_Pin_6);			// dc = 0
// 	MDR_PORTB->RXTX &= ~(PORT_Pin_10);			// cs = 0 PB10 для touch
// 	MDR_SSP1->DR = 0;
// 	while (MDR_SSP1->SR & SSP_SR_BSY)			// 1 – модуль SSP в настоящее время передает и/или принимает данные, либо буфер FIFO передатчика не пуст
// 	{
// 		;										// wait
// 	}
// 	uint16_t temp = 0;
// 	temp = (uint16_t)(MDR_SSP1->DR);
// 	temp = temp << 8;
// 	MDR_SSP1->DR = 0;
// 	while (MDR_SSP1->SR & SSP_SR_BSY)			// 1 – модуль SSP в настоящее время передает и/или принимает данные, либо буфер FIFO передатчика не пуст
// 	{
// 		;										// wait
// 	}
// 	temp |= (uint16_t)(MDR_SSP1->DR);
// 	*z = temp;
// 	MDR_PORTB->RXTX |= PORT_Pin_10;				// cs = 1

// 	// Повышаем скорость работы для дисплея
// 	SSP_Cmd(MDR_SSP1, DISABLE);
// 	SSP1_struct.SSP_CPSDVSR = 2;
//     SSP1_struct.SSP_SCR = 0;
// 	SSP_Init(MDR_SSP1, &SSP1_struct);
// 	SSP_Cmd(MDR_SSP1, ENABLE);
// }

// 1 если на тач нажимают, 0 - если нет
uint8_t ILI9341_TouchPressed()
{
	if ( (uint8_t)PORT_ReadInputDataBit(MDR_PORTB, PORT_Pin_9))
		return (0);
	else
		return (1);
}

// Отладка
void USB_Print(char *format, ...)
{
	va_list argptr;
	va_start(argptr, format);

	vsprintf(debugString, format, argptr);
	va_end(argptr);
	USB_CDC_SendData((uint8_t *)debugString, strlen(debugString));
	
	//delayTick(timeout);
}

uint8_t ILI9341_TouchGetCoordinates(uint16_t* x, uint16_t* y) {
    // ILI9341_TouchSelect();		// Это CS = 0, а я сделал это в самой функции

    uint32_t avg_x = 0;
    uint32_t avg_y = 0;
	uint16_t num_good_x = 0;
	uint16_t num_good_y = 0;
    // uint8_t nsamples = 0;
    // for(uint8_t i = 0; i < 16; i++) {
		// USB_Print("TEST\n");
        if(!ILI9341_TouchPressed())		// Проверяем пин с прерыванием
            // break;
			return 0;

		for(int i = 0; i < AVG_NUM; i++)
		{
			uint16_t raw_y = ili9341_touch_writecommand8(READ_Y); 
			uint8_t good_y = ((raw_y >  XPT2046_MIN_RAW_Y) && (raw_y < XPT2046_MAX_RAW_Y)) ? 1 : 0;
			avg_y += raw_y * good_y;
			num_good_y += good_y;

			uint16_t raw_x = ili9341_touch_writecommand8(READ_X); 
			uint8_t good_x = ((raw_x >  XPT2046_MIN_RAW_X) && (raw_x < XPT2046_MAX_RAW_X)) ? 1 : 0;
			avg_x += raw_x * good_x;
			num_good_x += good_x;
		}
		// Найдем среднее
		avg_y = avg_y / num_good_y;
		avg_x = avg_x / num_good_y;
		// Переведем в адекватное значение
		avg_y = (((avg_y - XPT2046_MIN_RAW_Y) * 100) / (XPT2046_MAX_RAW_Y - XPT2046_MIN_RAW_Y)) * ILI9341_TFTHEIGHT / 100;
		avg_x = (((avg_x - XPT2046_MIN_RAW_Y) * 100) / (XPT2046_MAX_RAW_Y - XPT2046_MIN_RAW_Y)) * ILI9341_TFTWIDTH / 100;

		USB_Print("raw_x = %d, raw_y = %d\r\n", avg_x, avg_y);
    // }
	
}


#define XPT2046_MIN_RAW_X 1500		//		//
#define XPT2046_MAX_RAW_X 30000		// 		//
#define XPT2046_MIN_RAW_Y 2000		//		//
#define XPT2046_MAX_RAW_Y 32000		//		//