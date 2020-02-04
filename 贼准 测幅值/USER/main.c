#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "adc.h"
 
#include "oled.h"
#include "bmp.h"

 
/************************************************
 ALIENTEK ս��STM32F103������ʵ��17
 ADC ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


 
 int main(void)
 {	 
  u16 adcx;
	float temp;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 
 	Adc_Init();		  		//ADC��ʼ��
  OLED_Init();			//��ʼ��OLED  
		OLED_Clear() ;
	
	
	
	while(1)
	{
		OLED_Clear();
		OLED_ShowString(0,0,"I:");
		OLED_ShowString(0,3,"VCL:");
		OLED_ShowString(90,3,"mvpp");
		adcx=Get_Adc_Average(ADC_Channel_1,100);
		OLED_ShowNum(30,3,adcx,4,16);
		//LCD_ShowxNum(156,130,adcx,4,16,0);//��ʾADC��ֵ
		temp=(float)adcx*(3.3/4096);
		adcx=1000*temp;
		if(temp<630)
		{
			adcx=3.5726*adcx-218.4;
		}
				if(temp>630)
		{
			adcx=3.232*adcx-228;
		}
		
		
		OLED_ShowNum(30,0,adcx,4,16);
		//LCD_ShowxNum(156,150,adcx,1,16,0);//��ʾ��ѹֵ
		
		temp-=adcx;
		temp*=1000;
		
		//LCD_ShowxNum(172,150,temp,3,16,0X80);
		LED0=!LED0;
		delay_ms(5500);	
	}
 }

