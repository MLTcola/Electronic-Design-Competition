//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : OLED 4接口演示例程(51系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   接PD6（SCL）
//              D1   接PD7（SDA）
//              RES  接PD4
//              DC   接PD5
//              CS   接PD3               
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//******************************************************************************/

#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "usart.h"

 int main(void)
 {
		u8 t;
		u8 y1=0,y2=10,y3=0,y4=0,i=0;
		delay_init();	    	 //延时函数初始化	  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
		uart_init(9600);	 //串口初始化为115200
		OLED_Init();			//初始化OLED  
		OLED_Clear(); 
	while(1) 
	{		
//		USART_RX_STA=0;
			//向下
			while(flag==2)
			{
				for(i=0;i<15;i++)
				{
					USART_RX_STA=0;
					y2=10;y3=0;y4=0;
					y1=y1+1;
					OLED_DrawBMP(0,y1,128,8,BMP1);
					delay_ms(200);
					OLED_Clear(); 
					if(y1==5)
						y1=0;
					if(flag!=2)
					{
						i=0;
						break;
					}
				}
				
				if(flag==2&i==15)
				{
					for(i=0;i<6;i++)
					{
								y3=y3+1;
						if(y3==1)
						{
							OLED_DrawBMP(0,1,128,8,BMP4);
							delay_ms(500);
							OLED_Clear(); 
						}
						else if(y3==2)
						{
							OLED_DrawBMP(0,1,128,8,BMP5);
							delay_ms(500);
							OLED_Clear(); 
						}
						else if(y3==3)
						{
							OLED_DrawBMP(0,1,128,8,BMP6);
							delay_ms(500);
							OLED_Clear(); 
							y3=0;
						}
						if(flag!=2)
						break;
					}
				}
				
			}
			
			
			if(flag==1)
			{
						y1=0;y3=0;y4=0;
						y2=y2-1;
						OLED_DrawBMP(0,y2,128,8,BMP2);
						delay_ms(200);
						OLED_Clear(); 
						if(y2==0)
							y2=10;
			}
			//向右
			if(flag==3)
			{
				y1=0;y2=10;y4=0;
				y3=y3+1;
				if(y3==1)
				{
					OLED_DrawBMP(0,1,128,8,BMP4);
					delay_ms(500);
					OLED_Clear(); 
				}
				else if(y3==2)
				{
					OLED_DrawBMP(0,1,128,8,BMP5);
					delay_ms(500);
					OLED_Clear(); 
				}
				else if(y3==3)
				{
					OLED_DrawBMP(0,1,128,8,BMP6);
					delay_ms(500);
					OLED_Clear(); 
					y3=0;
				}
			}
			
			//向左
			if(flag==4)
			{
				y1=0;y2=10;y3=0;
				y4=y4+1;
				if(y4==1)
				{
					OLED_DrawBMP(0,1,128,8,BMP9);
					delay_ms(500);
					OLED_Clear(); 
				}
				else if(y4==2)
				{
					OLED_DrawBMP(0,1,128,8,BMP8);
					delay_ms(500);
					OLED_Clear(); 
				}
				else if(y4==3)
				{
					OLED_DrawBMP(0,1,128,8,BMP7);
					delay_ms(500);
					OLED_Clear(); 
					y4=0;
				}
			}
			//强行停止
			if(flag==9)
			{
					OLED_Clear(); 
			}
			USART_RX_STA=0;
		} 
	
}

