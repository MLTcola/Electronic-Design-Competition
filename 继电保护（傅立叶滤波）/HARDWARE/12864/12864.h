#ifndef __12864_H
#define __12864_H	 
#include "sys.h"

void sendbyte(unsigned char zdata);
void write_com(unsigned char cmdcode);
void write_data(unsigned char Dispdata);
void lcdinit(void);
void DispString (unsigned char *s);
void Test(void);
void Lcd_12864_Init(void);
void LCD_MoveToXY(unsigned char x, unsigned char y);
void  LCD_StrShow(char *str, unsigned char x,unsigned char y);

#endif

