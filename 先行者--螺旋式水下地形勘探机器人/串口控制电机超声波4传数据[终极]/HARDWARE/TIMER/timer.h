#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

extern u8  TIM5CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值	
extern u8  TIM4CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM4CH1_CAPTURE_VAL;	//输入捕获值	
extern u8  TIM2CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM2CH1_CAPTURE_VAL;	//输入捕获值

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM5_Cap_Init(u16 arr,u16 psc);
void TIM4_Cap_Init(u16 arr,u16 psc);
void TIM2_Cap_Init(u16 arr,u16 psc);
#endif
