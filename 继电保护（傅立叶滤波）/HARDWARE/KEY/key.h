#ifndef __KEY_H__


#define __KEY_H__
#include "sys.h"

void KEY_Init(void);//IO≥ı ºªØ
uint8_t KEY_Scan(void);
u8 KEY_get(void);

extern u8 F;
extern u8 pagestate;

#define KEY1 1
#define KEY2 2
#define KEY3 3
#define KEY4 4
#define KEY5 5
#define KEY6 6
#define KEY7 7
#define KEY8 8
#define KEY9 9


#endif


