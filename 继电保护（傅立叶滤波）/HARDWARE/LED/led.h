#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved		
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	

//12864
#define NRST PAout(12)
#define PSB PCout(6)
#define CLK PAout(11)
#define SID PBout(15)
#define CS PAout(8)



void LED_Init(void);//��ʼ��

		 				    
#endif
