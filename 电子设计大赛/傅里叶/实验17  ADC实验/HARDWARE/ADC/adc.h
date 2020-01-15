#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

#define ADC_SIZE 1024
extern mycomplex ADC_DAT_u32[ADC_SIZE];
extern u16 ADC_DAT_INDEX_u16;
extern u32 adcmax,adcmin;

void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc2(u8 ch);
u16 Get_Adc_Average(u8 ch,u16 times); 
u16 Get_Adc_Average_fuzhi(u8 ch,u32 times);
 
#endif 
