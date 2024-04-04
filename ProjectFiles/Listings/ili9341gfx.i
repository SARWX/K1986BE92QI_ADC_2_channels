# 1 "CustomLibs/src/ili9341gfx.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 379 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "CustomLibs/src/ili9341gfx.c" 2
# 1 "./CustomLibs/inc\\ili9341.h" 1
# 1 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 1 3
# 56 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 3
typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int int64_t;


typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;





typedef signed char int_least8_t;
typedef signed short int int_least16_t;
typedef signed int int_least32_t;
typedef signed long long int int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long long int uint_least64_t;




typedef signed int int_fast8_t;
typedef signed int int_fast16_t;
typedef signed int int_fast32_t;
typedef signed long long int int_fast64_t;


typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long int uint_fast64_t;






typedef signed int intptr_t;
typedef unsigned int uintptr_t;



typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
# 2 "./CustomLibs/inc\\ili9341.h" 2
# 39 "./CustomLibs/inc\\ili9341.h"
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

void test(void);
void custom_ili9341_setaddress(uint16_t x,uint16_t y);
# 2 "CustomLibs/src/ili9341gfx.c" 2
# 1 "./CustomLibs/inc\\delay.h" 1





void delay_tick(uint32_t count);
void delay_ms(uint32_t delay);
void delay_us(uint32_t delay);
# 3 "CustomLibs/src/ili9341gfx.c" 2
# 1 "./CustomLibs/inc\\ili9341gfx.h" 1



# 1 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 1 3
# 53 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    typedef unsigned int size_t;
# 68 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    typedef __builtin_va_list __va_list;
# 87 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
typedef struct __fpos_t_struct {
    unsigned long long int __pos;





    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
# 108 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
typedef struct __FILE FILE;
# 119 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
struct __FILE {
    union {
        long __FILE_alignment;



        char __FILE_size[84];

    } __FILE_opaque;
};
# 138 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;
# 224 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int remove(const char * ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int rename(const char * , const char * ) __attribute__((__nonnull__(1,2)));
# 243 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) FILE *tmpfile(void);






extern __attribute__((__nothrow__)) char *tmpnam(char * );
# 265 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fclose(FILE * ) __attribute__((__nonnull__(1)));
# 275 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fflush(FILE * );
# 285 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) FILE *fopen(const char * __restrict ,
                           const char * __restrict ) __attribute__((__nonnull__(1,2)));
# 329 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) FILE *freopen(const char * __restrict ,
                    const char * __restrict ,
                    FILE * __restrict ) __attribute__((__nonnull__(2,3)));
# 342 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) void setbuf(FILE * __restrict ,
                    char * __restrict ) __attribute__((__nonnull__(1)));






extern __attribute__((__nothrow__)) int setvbuf(FILE * __restrict ,
                   char * __restrict ,
                   int , size_t ) __attribute__((__nonnull__(1)));
# 370 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int fprintf(FILE * __restrict ,
                    const char * __restrict , ...) __attribute__((__nonnull__(1,2)));
# 393 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int _fprintf(FILE * __restrict ,
                     const char * __restrict , ...) __attribute__((__nonnull__(1,2)));





#pragma __printf_args
extern __attribute__((__nothrow__)) int printf(const char * __restrict , ...) __attribute__((__nonnull__(1)));






#pragma __printf_args
extern __attribute__((__nothrow__)) int _printf(const char * __restrict , ...) __attribute__((__nonnull__(1)));





#pragma __printf_args
extern __attribute__((__nothrow__)) int sprintf(char * __restrict , const char * __restrict , ...) __attribute__((__nonnull__(1,2)));








#pragma __printf_args
extern __attribute__((__nothrow__)) int _sprintf(char * __restrict , const char * __restrict , ...) __attribute__((__nonnull__(1,2)));






#pragma __printf_args
extern __attribute__((__nothrow__)) int __ARM_snprintf(char * __restrict , size_t ,
                     const char * __restrict , ...) __attribute__((__nonnull__(3)));


#pragma __printf_args
extern __attribute__((__nothrow__)) int snprintf(char * __restrict , size_t ,
                     const char * __restrict , ...) __attribute__((__nonnull__(3)));
# 460 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int _snprintf(char * __restrict , size_t ,
                      const char * __restrict , ...) __attribute__((__nonnull__(3)));





#pragma __scanf_args
extern __attribute__((__nothrow__)) int fscanf(FILE * __restrict ,
                    const char * __restrict , ...) __attribute__((__nonnull__(1,2)));
# 503 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __scanf_args
extern __attribute__((__nothrow__)) int _fscanf(FILE * __restrict ,
                     const char * __restrict , ...) __attribute__((__nonnull__(1,2)));





#pragma __scanf_args
extern __attribute__((__nothrow__)) int scanf(const char * __restrict , ...) __attribute__((__nonnull__(1)));








#pragma __scanf_args
extern __attribute__((__nothrow__)) int _scanf(const char * __restrict , ...) __attribute__((__nonnull__(1)));





#pragma __scanf_args
extern __attribute__((__nothrow__)) int sscanf(const char * __restrict ,
                    const char * __restrict , ...) __attribute__((__nonnull__(1,2)));
# 541 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __scanf_args
extern __attribute__((__nothrow__)) int _sscanf(const char * __restrict ,
                     const char * __restrict , ...) __attribute__((__nonnull__(1,2)));







extern __attribute__((__nothrow__)) int vfscanf(FILE * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) int vscanf(const char * __restrict , __va_list) __attribute__((__nonnull__(1)));
extern __attribute__((__nothrow__)) int vsscanf(const char * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));

extern __attribute__((__nothrow__)) int _vfscanf(FILE * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) int _vscanf(const char * __restrict , __va_list) __attribute__((__nonnull__(1)));
extern __attribute__((__nothrow__)) int _vsscanf(const char * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) int __ARM_vsscanf(const char * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));

extern __attribute__((__nothrow__)) int vprintf(const char * __restrict , __va_list ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int _vprintf(const char * __restrict , __va_list ) __attribute__((__nonnull__(1)));





extern __attribute__((__nothrow__)) int vfprintf(FILE * __restrict ,
                    const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));
# 584 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int vsprintf(char * __restrict ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));
# 594 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int __ARM_vsnprintf(char * __restrict , size_t ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(3)));

extern __attribute__((__nothrow__)) int vsnprintf(char * __restrict , size_t ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(3)));
# 609 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int _vsprintf(char * __restrict ,
                      const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));





extern __attribute__((__nothrow__)) int _vfprintf(FILE * __restrict ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));





extern __attribute__((__nothrow__)) int _vsnprintf(char * __restrict , size_t ,
                      const char * __restrict , __va_list ) __attribute__((__nonnull__(3)));
# 635 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int __ARM_asprintf(char ** , const char * __restrict , ...) __attribute__((__nonnull__(2)));
extern __attribute__((__nothrow__)) int __ARM_vasprintf(char ** , const char * __restrict , __va_list ) __attribute__((__nonnull__(2)));
# 649 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fgetc(FILE * ) __attribute__((__nonnull__(1)));
# 659 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) char *fgets(char * __restrict , int ,
                    FILE * __restrict ) __attribute__((__nonnull__(1,3)));
# 673 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fputc(int , FILE * ) __attribute__((__nonnull__(2)));
# 683 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fputs(const char * __restrict , FILE * __restrict ) __attribute__((__nonnull__(1,2)));






extern __attribute__((__nothrow__)) int getc(FILE * ) __attribute__((__nonnull__(1)));
# 704 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    extern __attribute__((__nothrow__)) int (getchar)(void);
# 713 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) char *gets(char * ) __attribute__((__nonnull__(1)));
# 725 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int putc(int , FILE * ) __attribute__((__nonnull__(2)));
# 737 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    extern __attribute__((__nothrow__)) int (putchar)(int );






extern __attribute__((__nothrow__)) int puts(const char * ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int ungetc(int , FILE * ) __attribute__((__nonnull__(2)));
# 778 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) size_t fread(void * __restrict ,
                    size_t , size_t , FILE * __restrict ) __attribute__((__nonnull__(1,4)));
# 794 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) size_t __fread_bytes_avail(void * __restrict ,
                    size_t , FILE * __restrict ) __attribute__((__nonnull__(1,3)));
# 810 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) size_t fwrite(const void * __restrict ,
                    size_t , size_t , FILE * __restrict ) __attribute__((__nonnull__(1,4)));
# 822 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fgetpos(FILE * __restrict , fpos_t * __restrict ) __attribute__((__nonnull__(1,2)));
# 833 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fseek(FILE * , long int , int ) __attribute__((__nonnull__(1)));
# 850 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fsetpos(FILE * __restrict , const fpos_t * __restrict ) __attribute__((__nonnull__(1,2)));
# 863 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) long int ftell(FILE * ) __attribute__((__nonnull__(1)));
# 877 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) void rewind(FILE * ) __attribute__((__nonnull__(1)));
# 886 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) void clearerr(FILE * ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int feof(FILE * ) __attribute__((__nonnull__(1)));




extern __attribute__((__nothrow__)) int ferror(FILE * ) __attribute__((__nonnull__(1)));




extern __attribute__((__nothrow__)) void perror(const char * );
# 917 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int _fisatty(FILE * ) __attribute__((__nonnull__(1)));



extern __attribute__((__nothrow__)) void __use_no_semihosting_swi(void);
extern __attribute__((__nothrow__)) void __use_no_semihosting(void);
# 5 "./CustomLibs/inc\\ili9341gfx.h" 2
# 1 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdbool.h" 1 3
# 6 "./CustomLibs/inc\\ili9341gfx.h" 2
# 1 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\inttypes.h" 1 3
# 217 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\inttypes.h" 3
      typedef unsigned short wchar_t;




typedef struct imaxdiv_t { intmax_t quot, rem; } imaxdiv_t;






__attribute__((__nothrow__)) intmax_t strtoimax(const char * __restrict ,
                   char ** __restrict , int ) __attribute__((__nonnull__(1)));

__attribute__((__nothrow__)) uintmax_t strtoumax(const char * __restrict ,
                    char ** __restrict , int ) __attribute__((__nonnull__(1)));


__attribute__((__nothrow__)) intmax_t wcstoimax(const wchar_t * __restrict ,
                   wchar_t ** __restrict , int ) __attribute__((__nonnull__(1)));
__attribute__((__nothrow__)) uintmax_t wcstoumax(const wchar_t * __restrict ,
                    wchar_t ** __restrict , int ) __attribute__((__nonnull__(1)));

extern __attribute__((__nothrow__)) __attribute__((__const__)) intmax_t imaxabs(intmax_t );





extern __attribute__((__nothrow__)) __attribute__((__const__)) imaxdiv_t imaxdiv(intmax_t , intmax_t );
# 7 "./CustomLibs/inc\\ili9341gfx.h" 2

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
# 4 "CustomLibs/src/ili9341gfx.c" 2

volatile uint16_t cursor_x;
volatile uint16_t cursor_y;
volatile uint16_t textcolour;
volatile uint16_t textbgcolour;
volatile uint8_t textsize;
uint16_t vsetx,vsety,vactualx,vactualy,isetx,isety,iactualx,iactualy;
# 20 "CustomLibs/src/ili9341gfx.c"
void backuplocationvset(void)
{
 vsetx=cursor_x;
 vsety=cursor_y;
}

void backuplocationvactual(void)
{
 vactualx=cursor_x;
 vactualy=cursor_y;
}

void backuplocationiset(void)
{
 isetx=cursor_x;
 isety=cursor_y;
}

void backuplocationiactual(void)
{
 iactualx=cursor_x;
 iactualy=cursor_y;
}


static const unsigned char font[1275] = {
 0x00, 0x00, 0x00, 0x00, 0x00,
 0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
 0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
 0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
 0x18, 0x3C, 0x7E, 0x3C, 0x18,
 0x1C, 0x57, 0x7D, 0x57, 0x1C,
 0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
 0x00, 0x18, 0x3C, 0x18, 0x00,
 0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
 0x00, 0x18, 0x24, 0x18, 0x00,
 0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
 0x30, 0x48, 0x3A, 0x06, 0x0E,
 0x26, 0x29, 0x79, 0x29, 0x26,
 0x40, 0x7F, 0x05, 0x05, 0x07,
 0x40, 0x7F, 0x05, 0x25, 0x3F,
 0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
 0x7F, 0x3E, 0x1C, 0x1C, 0x08,
 0x08, 0x1C, 0x1C, 0x3E, 0x7F,
 0x14, 0x22, 0x7F, 0x22, 0x14,
 0x5F, 0x5F, 0x00, 0x5F, 0x5F,
 0x06, 0x09, 0x7F, 0x01, 0x7F,
 0x00, 0x66, 0x89, 0x95, 0x6A,
 0x60, 0x60, 0x60, 0x60, 0x60,
 0x94, 0xA2, 0xFF, 0xA2, 0x94,
 0x08, 0x04, 0x7E, 0x04, 0x08,
 0x10, 0x20, 0x7E, 0x20, 0x10,
 0x08, 0x08, 0x2A, 0x1C, 0x08,
 0x08, 0x1C, 0x2A, 0x08, 0x08,
 0x1E, 0x10, 0x10, 0x10, 0x10,
 0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
 0x30, 0x38, 0x3E, 0x38, 0x30,
 0x06, 0x0E, 0x3E, 0x0E, 0x06,
 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x5F, 0x00, 0x00,
 0x00, 0x07, 0x00, 0x07, 0x00,
 0x14, 0x7F, 0x14, 0x7F, 0x14,
 0x24, 0x2A, 0x7F, 0x2A, 0x12,
 0x23, 0x13, 0x08, 0x64, 0x62,
 0x36, 0x49, 0x56, 0x20, 0x50,
 0x00, 0x08, 0x07, 0x03, 0x00,
 0x00, 0x1C, 0x22, 0x41, 0x00,
 0x00, 0x41, 0x22, 0x1C, 0x00,
 0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
 0x08, 0x08, 0x3E, 0x08, 0x08,
 0x00, 0x80, 0x70, 0x30, 0x00,
 0x08, 0x08, 0x08, 0x08, 0x08,
 0x00, 0x00, 0x60, 0x60, 0x00,
 0x20, 0x10, 0x08, 0x04, 0x02,
 0x3E, 0x51, 0x49, 0x45, 0x3E,
 0x00, 0x42, 0x7F, 0x40, 0x00,
 0x72, 0x49, 0x49, 0x49, 0x46,
 0x21, 0x41, 0x49, 0x4D, 0x33,
 0x18, 0x14, 0x12, 0x7F, 0x10,
 0x27, 0x45, 0x45, 0x45, 0x39,
 0x3C, 0x4A, 0x49, 0x49, 0x31,
 0x41, 0x21, 0x11, 0x09, 0x07,
 0x36, 0x49, 0x49, 0x49, 0x36,
 0x46, 0x49, 0x49, 0x29, 0x1E,
 0x00, 0x00, 0x14, 0x00, 0x00,
 0x00, 0x40, 0x34, 0x00, 0x00,
 0x00, 0x08, 0x14, 0x22, 0x41,
 0x14, 0x14, 0x14, 0x14, 0x14,
 0x00, 0x41, 0x22, 0x14, 0x08,
 0x02, 0x01, 0x59, 0x09, 0x06,
 0x3E, 0x41, 0x5D, 0x59, 0x4E,
 0x7C, 0x12, 0x11, 0x12, 0x7C,
 0x7F, 0x49, 0x49, 0x49, 0x36,
 0x3E, 0x41, 0x41, 0x41, 0x22,
 0x7F, 0x41, 0x41, 0x41, 0x3E,
 0x7F, 0x49, 0x49, 0x49, 0x41,
 0x7F, 0x09, 0x09, 0x09, 0x01,
 0x3E, 0x41, 0x41, 0x51, 0x73,
 0x7F, 0x08, 0x08, 0x08, 0x7F,
 0x00, 0x41, 0x7F, 0x41, 0x00,
 0x20, 0x40, 0x41, 0x3F, 0x01,
 0x7F, 0x08, 0x14, 0x22, 0x41,
 0x7F, 0x40, 0x40, 0x40, 0x40,
 0x7F, 0x02, 0x1C, 0x02, 0x7F,
 0x7F, 0x04, 0x08, 0x10, 0x7F,
 0x3E, 0x41, 0x41, 0x41, 0x3E,
 0x7F, 0x09, 0x09, 0x09, 0x06,
 0x3E, 0x41, 0x51, 0x21, 0x5E,
 0x7F, 0x09, 0x19, 0x29, 0x46,
 0x26, 0x49, 0x49, 0x49, 0x32,
 0x03, 0x01, 0x7F, 0x01, 0x03,
 0x3F, 0x40, 0x40, 0x40, 0x3F,
 0x1F, 0x20, 0x40, 0x20, 0x1F,
 0x3F, 0x40, 0x38, 0x40, 0x3F,
 0x63, 0x14, 0x08, 0x14, 0x63,
 0x03, 0x04, 0x78, 0x04, 0x03,
 0x61, 0x59, 0x49, 0x4D, 0x43,
 0x00, 0x7F, 0x41, 0x41, 0x41,
 0x02, 0x04, 0x08, 0x10, 0x20,
 0x00, 0x41, 0x41, 0x41, 0x7F,
 0x04, 0x02, 0x01, 0x02, 0x04,
 0x40, 0x40, 0x40, 0x40, 0x40,
 0x00, 0x03, 0x07, 0x08, 0x00,
 0x20, 0x54, 0x54, 0x78, 0x40,
 0x7F, 0x28, 0x44, 0x44, 0x38,
 0x38, 0x44, 0x44, 0x44, 0x28,
 0x38, 0x44, 0x44, 0x28, 0x7F,
 0x38, 0x54, 0x54, 0x54, 0x18,
 0x00, 0x08, 0x7E, 0x09, 0x02,
 0x18, 0xA4, 0xA4, 0x9C, 0x78,
 0x7F, 0x08, 0x04, 0x04, 0x78,
 0x00, 0x44, 0x7D, 0x40, 0x00,
 0x20, 0x40, 0x40, 0x3D, 0x00,
 0x7F, 0x10, 0x28, 0x44, 0x00,
 0x00, 0x41, 0x7F, 0x40, 0x00,
 0x7C, 0x04, 0x78, 0x04, 0x78,
 0x7C, 0x08, 0x04, 0x04, 0x78,
 0x38, 0x44, 0x44, 0x44, 0x38,
 0xFC, 0x18, 0x24, 0x24, 0x18,
 0x18, 0x24, 0x24, 0x18, 0xFC,
 0x7C, 0x08, 0x04, 0x04, 0x08,
 0x48, 0x54, 0x54, 0x54, 0x24,
 0x04, 0x04, 0x3F, 0x44, 0x24,
 0x3C, 0x40, 0x40, 0x20, 0x7C,
 0x1C, 0x20, 0x40, 0x20, 0x1C,
 0x3C, 0x40, 0x30, 0x40, 0x3C,
 0x44, 0x28, 0x10, 0x28, 0x44,
 0x4C, 0x90, 0x90, 0x90, 0x7C,
 0x44, 0x64, 0x54, 0x4C, 0x44,
 0x00, 0x08, 0x36, 0x41, 0x00,
 0x00, 0x00, 0x77, 0x00, 0x00,
 0x00, 0x41, 0x36, 0x08, 0x00,
 0x02, 0x01, 0x02, 0x04, 0x02,
 0x3C, 0x26, 0x23, 0x26, 0x3C,
 0x1E, 0xA1, 0xA1, 0x61, 0x12,
 0x3A, 0x40, 0x40, 0x20, 0x7A,
 0x38, 0x54, 0x54, 0x55, 0x59,
 0x21, 0x55, 0x55, 0x79, 0x41,
 0x22, 0x54, 0x54, 0x78, 0x42,
 0x21, 0x55, 0x54, 0x78, 0x40,
 0x20, 0x54, 0x55, 0x79, 0x40,
 0x0C, 0x1E, 0x52, 0x72, 0x12,
 0x39, 0x55, 0x55, 0x55, 0x59,
 0x39, 0x54, 0x54, 0x54, 0x59,
 0x39, 0x55, 0x54, 0x54, 0x58,
 0x00, 0x00, 0x45, 0x7C, 0x41,
 0x00, 0x02, 0x45, 0x7D, 0x42,
 0x00, 0x01, 0x45, 0x7C, 0x40,
 0x7D, 0x12, 0x11, 0x12, 0x7D,
 0xF0, 0x28, 0x25, 0x28, 0xF0,
 0x7C, 0x54, 0x55, 0x45, 0x00,
 0x20, 0x54, 0x54, 0x7C, 0x54,
 0x7C, 0x0A, 0x09, 0x7F, 0x49,
 0x32, 0x49, 0x49, 0x49, 0x32,
 0x3A, 0x44, 0x44, 0x44, 0x3A,
 0x32, 0x4A, 0x48, 0x48, 0x30,
 0x3A, 0x41, 0x41, 0x21, 0x7A,
 0x3A, 0x42, 0x40, 0x20, 0x78,
 0x00, 0x9D, 0xA0, 0xA0, 0x7D,
 0x3D, 0x42, 0x42, 0x42, 0x3D,
 0x3D, 0x40, 0x40, 0x40, 0x3D,
 0x3C, 0x24, 0xFF, 0x24, 0x24,
 0x48, 0x7E, 0x49, 0x43, 0x66,
 0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
 0xFF, 0x09, 0x29, 0xF6, 0x20,
 0xC0, 0x88, 0x7E, 0x09, 0x03,
 0x20, 0x54, 0x54, 0x79, 0x41,
 0x00, 0x00, 0x44, 0x7D, 0x41,
 0x30, 0x48, 0x48, 0x4A, 0x32,
 0x38, 0x40, 0x40, 0x22, 0x7A,
 0x00, 0x7A, 0x0A, 0x0A, 0x72,
 0x7D, 0x0D, 0x19, 0x31, 0x7D,
 0x26, 0x29, 0x29, 0x2F, 0x28,
 0x26, 0x29, 0x29, 0x29, 0x26,
 0x30, 0x48, 0x4D, 0x40, 0x20,
 0x38, 0x08, 0x08, 0x08, 0x08,
 0x08, 0x08, 0x08, 0x08, 0x38,
 0x2F, 0x10, 0xC8, 0xAC, 0xBA,
 0x2F, 0x10, 0x28, 0x34, 0xFA,
 0x00, 0x00, 0x7B, 0x00, 0x00,
 0x08, 0x14, 0x2A, 0x14, 0x22,
 0x22, 0x14, 0x2A, 0x14, 0x08,
 0xAA, 0x00, 0x55, 0x00, 0xAA,
 0xAA, 0x55, 0xAA, 0x55, 0xAA,
 0x00, 0x00, 0x00, 0xFF, 0x00,
 0x10, 0x10, 0x10, 0xFF, 0x00,
 0x14, 0x14, 0x14, 0xFF, 0x00,
 0x10, 0x10, 0xFF, 0x00, 0xFF,
 0x10, 0x10, 0xF0, 0x10, 0xF0,
 0x14, 0x14, 0x14, 0xFC, 0x00,
 0x14, 0x14, 0xF7, 0x00, 0xFF,
 0x00, 0x00, 0xFF, 0x00, 0xFF,
 0x14, 0x14, 0xF4, 0x04, 0xFC,
 0x14, 0x14, 0x17, 0x10, 0x1F,
 0x10, 0x10, 0x1F, 0x10, 0x1F,
 0x14, 0x14, 0x14, 0x1F, 0x00,
 0x10, 0x10, 0x10, 0xF0, 0x00,
 0x00, 0x00, 0x00, 0x1F, 0x10,
 0x10, 0x10, 0x10, 0x1F, 0x10,
 0x10, 0x10, 0x10, 0xF0, 0x10,
 0x00, 0x00, 0x00, 0xFF, 0x10,
 0x10, 0x10, 0x10, 0x10, 0x10,
 0x10, 0x10, 0x10, 0xFF, 0x10,
 0x00, 0x00, 0x00, 0xFF, 0x14,
 0x00, 0x00, 0xFF, 0x00, 0xFF,
 0x00, 0x00, 0x1F, 0x10, 0x17,
 0x00, 0x00, 0xFC, 0x04, 0xF4,
 0x14, 0x14, 0x17, 0x10, 0x17,
 0x14, 0x14, 0xF4, 0x04, 0xF4,
 0x00, 0x00, 0xFF, 0x00, 0xF7,
 0x14, 0x14, 0x14, 0x14, 0x14,
 0x14, 0x14, 0xF7, 0x00, 0xF7,
 0x14, 0x14, 0x14, 0x17, 0x14,
 0x10, 0x10, 0x1F, 0x10, 0x1F,
 0x14, 0x14, 0x14, 0xF4, 0x14,
 0x10, 0x10, 0xF0, 0x10, 0xF0,
 0x00, 0x00, 0x1F, 0x10, 0x1F,
 0x00, 0x00, 0x00, 0x1F, 0x14,
 0x00, 0x00, 0x00, 0xFC, 0x14,
 0x00, 0x00, 0xF0, 0x10, 0xF0,
 0x10, 0x10, 0xFF, 0x10, 0xFF,
 0x14, 0x14, 0x14, 0xFF, 0x14,
 0x10, 0x10, 0x10, 0x1F, 0x00,
 0x00, 0x00, 0x00, 0xF0, 0x10,
 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
 0xFF, 0xFF, 0xFF, 0x00, 0x00,
 0x00, 0x00, 0x00, 0xFF, 0xFF,
 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
 0x38, 0x44, 0x44, 0x38, 0x44,
 0xFC, 0x4A, 0x4A, 0x4A, 0x34,
 0x7E, 0x02, 0x02, 0x06, 0x06,
 0x02, 0x7E, 0x02, 0x7E, 0x02,
 0x63, 0x55, 0x49, 0x41, 0x63,
 0x38, 0x44, 0x44, 0x3C, 0x04,
 0x40, 0x7E, 0x20, 0x1E, 0x20,
 0x06, 0x02, 0x7E, 0x02, 0x02,
 0x99, 0xA5, 0xE7, 0xA5, 0x99,
 0x1C, 0x2A, 0x49, 0x2A, 0x1C,
 0x4C, 0x72, 0x01, 0x72, 0x4C,
 0x30, 0x4A, 0x4D, 0x4D, 0x30,
 0x30, 0x48, 0x78, 0x48, 0x30,
 0xBC, 0x62, 0x5A, 0x46, 0x3D,
 0x3E, 0x49, 0x49, 0x49, 0x00,
 0x7E, 0x01, 0x01, 0x01, 0x7E,
 0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
 0x44, 0x44, 0x5F, 0x44, 0x44,
 0x40, 0x51, 0x4A, 0x44, 0x40,
 0x40, 0x44, 0x4A, 0x51, 0x40,
 0x00, 0x00, 0xFF, 0x01, 0x03,
 0xE0, 0x80, 0xFF, 0x00, 0x00,
 0x08, 0x08, 0x6B, 0x6B, 0x08,
 0x36, 0x12, 0x36, 0x24, 0x36,
 0x06, 0x0F, 0x09, 0x0F, 0x06,
 0x00, 0x00, 0x18, 0x18, 0x00,
 0x00, 0x00, 0x10, 0x10, 0x00,
 0x30, 0x40, 0xFF, 0x01, 0x01,
 0x00, 0x1F, 0x01, 0x01, 0x1E,
 0x00, 0x19, 0x1D, 0x17, 0x12,
 0x00, 0x3C, 0x3C, 0x3C, 0x3C,
 0x00, 0x00, 0x00, 0x00, 0x00
};

extern uint16_t LCD_W,LCD_H;

void ili9341_drawchar(int16_t x, int16_t y, unsigned char c,uint16_t color, uint16_t bg, uint8_t size)
{

 if ((x >=LCD_W) ||
     (y >=LCD_H) ||
     ((x + 6 * size - 1) < 0) ||
     ((y + 8 * size - 1) < 0))
 {
  return;
 }

 for (int8_t i=0; i<6; i++ )
 {
  uint8_t line;

  if (i == 5)
  {
   line = 0x0;
  }
  else
  {
   line = font[(c*5)+i];
  }

  for (int8_t j = 0; j<8; j++)
  {
   if (line & 0x1)
   {
    if (size == 1)
    {
     ili9341_drawpixel(x+i, y+j, color);
    }
    else {
     ili9341_fillrect(x+(i*size), y+(j*size), size, size, color);
    }
   } else if (bg != color)
   {
    if (size == 1)
    {
     ili9341_drawpixel(x+i, y+j, bg);
    }
    else
    {
     ili9341_fillrect(x+i*size, y+j*size, size, size, bg);
    }
   }

   line >>= 1;
  }
 }
}

void ili9341_setcursor(uint16_t x,uint16_t y)
{
 cursor_x=x;
 cursor_y=y;
}

void ili9341_settextcolour(uint16_t x,uint16_t y)
{
 textcolour=x;
 textbgcolour=y;
}

void ili9341_settextsize(uint8_t s)
{
 if(s>8) return;
 textsize=(s>0) ? s: 1;
}

void ili9341_write(uint8_t c)
{
 if (c == '\n')
 {
  cursor_y += textsize*8;
  cursor_x = 0;
 }
 else if (c == '\r')
 {

 }
 else
 {
  ili9341_drawchar(cursor_x, cursor_y, c, textcolour, textbgcolour, textsize);
  cursor_x += textsize*6;
 }
}


void display_init(void)
{

 ili9341_setcursor(4,4);
 delay_ms(2);
 ili9341_settextcolour(0x0E70,0x0000);
 delay_ms(2);
 ili9341_settextsize(2);
 delay_ms(2);
 printf("mode - ");
 delay_ms(2);
 ili9341_settextcolour(0x008F,0x0000);
 delay_ms(2);
 ili9341_settextsize(2);
 delay_ms(2);
 printf("constant voltage");
 delay_ms(2);
 ili9341_setcursor(4,40);
 delay_ms(2);
 ili9341_settextcolour(0xFF70,0x0000);
 delay_ms(2);
 ili9341_settextsize(4);
 delay_ms(2);
 ili9341_write('V');
 delay_ms(2);
 cursor_y=cursor_y+6;
 ili9341_settextsize(3);
 delay_ms(2);
 printf("set\n");
 delay_ms(2);
 cursor_y=cursor_y+12;
 backuplocationvset();
 printf("00.00v");
 delay_ms(2);
 ili9341_setcursor(4,120);
 delay_ms(2);
 ili9341_settextsize(4);
 delay_ms(2);
 ili9341_write('V');
 delay_ms(2);
 cursor_y=cursor_y+6;
 ili9341_settextsize(3);
 delay_ms(2);
 printf("actual\n\n");
 delay_ms(2);
 backuplocationvactual();
 ili9341_settextsize(5);
 printf("00.00");
 delay_ms(2);

 ili9341_setcursor(164,40);
 delay_ms(2);
 ili9341_settextcolour(0x0EFF,0x0000);
 delay_ms(2);
 ili9341_settextsize(4);
 delay_ms(2);
 ili9341_write('I');
 delay_ms(2);
 cursor_y=cursor_y+6;
 ili9341_settextsize(3);
 delay_ms(2);
 printf("set");
 delay_ms(2);
 cursor_x=164;
 cursor_y=(cursor_y+36);
 backuplocationiset();
 ili9341_settextsize(3);
 printf("00.00a");
 delay_ms(2);
 ili9341_setcursor(164,120);
 delay_ms(2);
 ili9341_settextsize(4);
 delay_ms(2);
 ili9341_write('I');
 delay_ms(2);
 cursor_y=cursor_y+6;
 ili9341_settextsize(3);
 delay_ms(2);
 printf("actual");
 delay_ms(2);
 cursor_x=164;
 backuplocationiactual();
 cursor_y=cursor_y+48;
 ili9341_settextsize(5);
 printf("00.00");
 delay_ms(2000);
}
