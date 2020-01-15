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
 ALIENTEK 战舰STM32F103开发板实验17
 ADC 实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


 
 int main(void)
 {	 
  u16 adcx;
	float temp;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 
 	Adc_Init();		  		//ADC初始化
  OLED_Init();			//初始化OLED  
		OLED_Clear() ;
	
	
	
	while(1)
	{
		OLED_Clear();
		OLED_ShowString(0,0,"I:");
		OLED_ShowString(0,3,"VCL:");
		OLED_ShowString(90,3,"mvpp");
		adcx=Get_Adc_Average(ADC_Channel_1,100);
		OLED_ShowNum(30,3,adcx,4,16);
		//LCD_ShowxNum(156,130,adcx,4,16,0);//显示ADC的值
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
		//LCD_ShowxNum(156,150,adcx,1,16,0);//显示电压值
		
		temp-=adcx;
		temp*=1000;
		
		//LCD_ShowxNum(172,150,temp,3,16,0X80);
		LED0=!LED0;
		delay_ms(5500);	
	}
 }

