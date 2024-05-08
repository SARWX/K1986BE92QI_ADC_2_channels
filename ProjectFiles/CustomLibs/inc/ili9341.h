#include <stdint.h>
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ILI9341_H_
#define _ILI9341_H_


#define controlport PORTB
#define controlddr DDRB
#define controlpin PINB
#define rstport PORTD       // ���� ����� �������� �� ���-�� ����� GPIOD->ODR
#define rstddr DDRD
#define rstpin PIND
#define dc 0
#define cs 1
#define rst 7
#define ILI9341_TFTHEIGHT 240 
#define ILI9341_TFTWIDTH 320

#define BLACK       0x0000     
#define NAVY        0xF000      
#define DARKGREEN   0x0E30      
#define DARKCYAN    0xFE30      
#define MAROON      0x0087      
#define PURPLE      0xF087      
#define OLIVE       0x0EB7      
#define LIGHTGREY   0x816C      
#define DARKGREY    0xFEB7     
#define BLUE        0xF100      
#define GREEN       0x0E70      
#define CYAN        0xFF70      
#define RED         0x008F     
#define MAGENTA     0xF18F      
#define YELLOW      0x0EFF     
#define WHITE       0xFFFF  
#define ORANGE      0x02DF      
#define GREENYELLOW 0x5EFA     
#define PINK        0xF18F

void ili9341_hard_init(void);
void ili9341_spi_init(void);
void ili9341_spi_send(unsigned char spi_data);
void ili9341_writecommand8(uint8_t com);
void ili9341_writedata8(uint8_t data);
void ili9341_setaddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void ili9341_hard_reset(void);
void ili9341_init(void);
void ili9341_pushcolour(uint16_t colour);
void ili9341_clear(uint16_t colour);
void ili9341_drawpixel(uint16_t x3,uint16_t y3,uint16_t colour1);
void ili9341_drawvline(uint16_t x,uint16_t y,uint16_t h,uint16_t colour);
void ili9341_drawhline(uint16_t x,uint16_t y,uint16_t w,uint16_t colour);
void ili9341_fillrect(uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t colour);
void ili9341_setRotation(uint8_t x);
void Setup_ili9341(void);
void ili9341_filltriangle(uint16_t x, uint16_t y, int base, int height, uint16_t colour);
// void dysplay_signal(uint16_t *arr, int size, int signal_number, int skip_every);
void test(void);
void custom_ili9341_setaddress(uint16_t x,uint16_t y);

#endif
