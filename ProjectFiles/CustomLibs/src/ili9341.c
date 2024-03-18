#include "ili9341.h"
#include <stdint.h>
#include "MDR32F9Qx_ssp.h"
#include "MDR32F9Qx_port.h"
#include "MDR32Fx.h"
#include "delay.h"

volatile uint16_t LCD_W=ILI9341_TFTWIDTH;
volatile uint16_t LCD_H=ILI9341_TFTHEIGHT;

// void ili9341_hard_init(void)	// init hardware
// {
// 	rstddr = 0xFF;			// output for reset (конфигурация портов, все на выход) - это для ATMEGA, надо просто конфигурацию портов написать
// 							// просто пояснения: DDRD – The Port D Data Direction Register (регистр направления передачи данных порта D)
// 	rstport |=(1<<rst);		// pull high for normal operation (подтяжка RST к 1)
// 	controlddr |= (1<<dc);	// D/C as output (Тоже направление передачи)
// }

// void ili9341_spi_init(void)//set spi speed and settings 
// {
// 	DDRB |=(1<<1)|(1<<2)|(1<<3)|(1<<5);	// CS,SS,MOSI,SCK as output(although SS will be unused throughout the program)
// 	SPCR=(1<<SPE)|(1<<MSTR);			// mode 0,fosc/4
// 	SPSR |=(1<<SPI2X);					// doubling spi speed.i.e final spi speed-fosc/2
// 	PORTB |=(1<<1);						// cs off during startup
// }

// void ili9341_spi_send(unsigned char spi_data)//send spi data to display
// {
// 	SPDR=spi_data;//move data into spdr
// 	while(!(SPSR & (1<<SPIF)));//wait till the transmission is finished
// }

void ili9341_writecommand8(uint8_t com)//command write
{
//	controlport &=~((1<<dc)|(1<<cs));//dc and cs both low to send command
	PORT_ResetBits(MDR_PORTB, PORT_Pin_6);		// dc = 0
	PORT_ResetBits(MDR_PORTF, PORT_Pin_2);		// cs = 0
	delay_us(5);//little delay
	// ili9341_spi_send(com);
	SSP_SendData(MDR_SSP1, com);
//	controlport |=(1<<cs);//pull high cs
	PORT_SetBits(MDR_PORTB, PORT_Pin_6); 		// cs = 1
}

void ili9341_writedata8(uint8_t data)//data write
{
//	controlport |=(1<<dc);//set dc high for data
	PORT_SetBits(MDR_PORTB, PORT_Pin_6);			// dc = 1
//	delay_us(1);//delay
//	controlport &=~(1<<cs);//set cs low for operation
	PORT_ResetBits(MDR_PORTF, PORT_Pin_2);		// cs = 0
//	ili9341_spi_send(data);
	SSP_SendData(MDR_SSP1, data);
//	controlport |=(1<<cs);
	PORT_SetBits(MDR_PORTF, PORT_Pin_2); 		// cs = 1
}

void ili9341_setaddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)//set coordinate for print or other function
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

	ili9341_writecommand8(0x2C);//meory write
}

void ili9341_hard_reset(void)	// hard reset display (просто ножку RESET дернуть 1 -> 0 -> 1 для перезагрузки)
{
//	rstport |=(1<<rst);//pull high if low previously
	PORT_SetBits(MDR_PORTB, PORT_Pin_7); 		// RESET = 1
	delay_ms(200);
//	rstport &=~(1<<rst);//low for reset
	PORT_ResetBits(MDR_PORTB, PORT_Pin_7);		// RESET = 0
	delay_ms(200);
//	rstport |=(1<<rst);//again pull high for normal operation
	PORT_SetBits(MDR_PORTB, PORT_Pin_7); 		// RESET = 1
	delay_ms(200);
}

void ili9341_init(void) 	// set up display using predefined command sequence
{
//	ili9341_hard_init(); 	// Инициализируем МК для работы с ili9341 (порты всякие)
//	ili9341_spi_init();		// Инициализируем контроллер SPI
	ili9341_hard_reset();	// Просто перезагрузка 
	ili9341_writecommand8(0x01);	//soft reset
	delay_ms(1000);

	//power control A
	ili9341_writecommand8(0xCB);
	ili9341_writedata8(0x39);
	ili9341_writedata8(0x2C);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0x34);
	ili9341_writedata8(0x02);

	//power control B
	ili9341_writecommand8(0xCF);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0xC1);
	ili9341_writedata8(0x30);

	//driver timing control A
	ili9341_writecommand8(0xE8);
	ili9341_writedata8(0x85);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0x78);

	//driver timing control B
	ili9341_writecommand8(0xEA);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0x00);

	//power on sequence control
	ili9341_writecommand8(0xED);
	ili9341_writedata8(0x64);
	ili9341_writedata8(0x03);
	ili9341_writedata8(0x12);
	ili9341_writedata8(0x81);

	//pump ratio control
	ili9341_writecommand8(0xF7);
	ili9341_writedata8(0x20);

	//power control,VRH[5:0]
	ili9341_writecommand8(0xC0);
	ili9341_writedata8(0x23);

	//Power control,SAP[2:0];BT[3:0]
	ili9341_writecommand8(0xC1);
	ili9341_writedata8(0x10);

	//vcm control
	ili9341_writecommand8(0xC5);
	ili9341_writedata8(0x3E);
	ili9341_writedata8(0x28);

	//vcm control 2
	ili9341_writecommand8(0xC7);
	ili9341_writedata8(0x86);

	//memory access control
	ili9341_writecommand8(0x36);
	ili9341_writedata8(0x48);

	//pixel format
	ili9341_writecommand8(0x3A);
	ili9341_writedata8(0x55);

	//frameration control,normal mode full colours
	ili9341_writecommand8(0xB1);
	ili9341_writedata8(0x00);
	ili9341_writedata8(0x18);

	//display function control
	ili9341_writecommand8(0xB6);
	ili9341_writedata8(0x08);
	ili9341_writedata8(0x82);
	ili9341_writedata8(0x27);

	//3gamma function disable
	ili9341_writecommand8(0xF2);
	ili9341_writedata8(0x00);

	//gamma curve selected
	ili9341_writecommand8(0x26);
	ili9341_writedata8(0x01);

	//set positive gamma correction
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

	//set negative gamma correction
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

	//exit sleep
	ili9341_writecommand8(0x11);
	delay_ms(120);
	//display on
	ili9341_writecommand8(0x29);
}

//set colour for drawing
void ili9341_pushcolour(uint16_t colour)
{
	ili9341_writedata8(colour>>8);
	ili9341_writedata8(colour);
}

//clear lcd and fill with colour
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

//draw pixel
void ili9341_drawpixel(uint16_t x3,uint16_t y3,uint16_t colour1) //pixels will always be counted from right side.x is representing LCD width which will always be less tha 240.Y is representing LCD height which will always be less than 320
{
	if ((x3 < 0) ||(x3 >= LCD_W) || (y3 < 0) || (y3 >= LCD_H))
	{
		return;
	}

	ili9341_setaddress(x3,y3,x3+1,y3+1);
	ili9341_pushcolour(colour1);
}

//draw vertical line
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


//draw horizental line

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


//draw colour filled rectangle
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
//rotate screen at desired orientation
void ili9341_setRotation(uint8_t m) 
{
	uint8_t rotation;

	ili9341_writecommand8(0x36);
	rotation=m%4;

	switch (rotation) 
	{
		case 0:
			ili9341_writedata8(0x40|0x08);
			LCD_W = 240;
			LCD_H = 320;
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
	ili9341_init();         	// Инициализируем ili9341
	ili9341_clear(YELLOW);   	// Заполняем все одним цветом
	delay_ms(1000);
	ili9341_setRotation(3); 	// Установим ориентацию экрана
}
