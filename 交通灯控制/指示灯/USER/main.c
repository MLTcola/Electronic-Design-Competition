//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : OLED 4�ӿ���ʾ����(51ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PD6��SCL��
//              D1   ��PD7��SDA��
//              RES  ��PD4
//              DC   ��PD5
//              CS   ��PD3               
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2014/3/16
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
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		uart_init(9600);	 //���ڳ�ʼ��Ϊ115200
		OLED_Init();			//��ʼ��OLED  
		OLED_Clear(); 
	while(1) 
	{		
//		USART_RX_STA=0;
			//����
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
			//����
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
			
			//����
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
			//ǿ��ֹͣ
			if(flag==9)
			{
					OLED_Clear(); 
			}
			USART_RX_STA=0;
		} 
	
}

