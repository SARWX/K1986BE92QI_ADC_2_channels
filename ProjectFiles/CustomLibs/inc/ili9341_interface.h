#include <stdint.h>

#ifndef _ILI9341_INTERFACE_H_
#define _ILI9341_INTERFACE_H_

void display_signal(uint16_t *arr, int size, int signal_number, int skip_every);
int draw_box(int row_num, uint16_t color);
void display_main_menu(void);


#endif
