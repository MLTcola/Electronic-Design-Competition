#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "pwm.h"
#include "timer.h"


 int main(void)
 {	
		u32 temp=0;
		int Distance1;
	 int Distance2;
	 int Distance3;
		int cache[14];
	 int flag1=0;
	 int flag2=0;
	 int flag3=0;
	 int i;
		delay_init();	    	 //ÑÓÊ±º¯Êý³õÊ¼»¯	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// ÉèÖÃÖÐ¶ÏÓÅÏÈ¼¶·Ö×é2
		uart_init(9600);	 //´®¿Ú³õÊ¼»¯Îª9600
		LED_Init();		  	 //³õÊ¼»¯ÓëLEDÁ¬½ÓµÄÓ²¼þ½Ó¿Ú 
		TIM1_PWM_Init(899,0);//²»·ÖÆµ¡£PWMÆµÂÊ=72000/(899+1)=80Khz//¿ØÖÆµç»ú
		TIM_SetCompare1(TIM1,899);	 
		TIM_SetCompare4(TIM1,899);	 
//		TIM2_Int_Init(899,0);//³¬Éù²¨
		TIM2_Cap_Init(0XFFFF,72-1);
		TIM3_PWM_Init(899,0);
		TIM5_Cap_Init(0XFFFF,72-1);	//ÒÔ1MhzµÄÆµÂÊ¼ÆÊ		
		TIM4_Cap_Init(0XFFFF,72-1);	//ÒÔ1MhzµÄÆµÂÊ¼ÆÊ		
		while(1)
		{	
			
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
			delay_us(15);
			GPIO_ResetBits(GPIOB,GPIO_Pin_0);
			delay_ms(70);
			
			GPIO_SetBits(GPIOB,GPIO_Pin_1);
			delay_us(15);
			GPIO_ResetBits(GPIOB,GPIO_Pin_1);
			delay_ms(70);
			
			GPIO_SetBits(GPIOB,GPIO_Pin_11);
			delay_us(15);
			GPIO_ResetBits(GPIOB,GPIO_Pin_11);
			delay_ms(70);
					 
			if(TIM5CH1_CAPTURE_STA&0X80)//³É¹¦²¶»ñµ½ÁËÒ»´ÎÉÏÉýÑØ
			{
				temp=TIM5CH1_CAPTURE_STA&0X3F;
				temp*=65536;//Òç³öÊ±¼ä×ÜºÍ
				temp+=TIM5CH1_CAPTURE_VAL;//µÃµ½×ÜµÄ¸ßµçÆ½Ê±¼ä
				Distance1=temp*170.0/10000;
//				if(Distance1<100)
//					printf("00%d",Distance1);//´òÓ¡×ÜµÄ¸ßµãÆ½Ê±¼ä
//				if((Distance1>=100)&&(Distance1<1000))
//					printf("0%d",Distance1);//´òÓ¡×ÜµÄ¸ßµãÆ½Ê±¼ä
//				if(Distance1>=1000)
//					printf("%d",Distance1);//´òÓ¡×ÜµÄ¸ßµãÆ½Ê±¼ä
				TIM5CH1_CAPTURE_STA=0;//¿ªÆôÏÂÒ»´Î²¶»ñ
				flag1=1;
			}
			
			if(TIM4CH1_CAPTURE_STA&0X80)//³É¹¦²¶»ñµ½ÁËÒ»´ÎÉÏÉýÑØ
			{
				temp=TIM4CH1_CAPTURE_STA&0X3F;
				temp*=65536;//Òç³öÊ±¼ä×ÜºÍ
				temp+=TIM4CH1_CAPTURE_VAL;//µÃµ½×ÜµÄ¸ßµçÆ½Ê±¼ä
				Distance2=temp*170.0/10000;
				
//				if(Distance2<100)
//					printf("00%d",Distance2);//´òÓ¡×ÜµÄ¸ßµãÆ½Ê±¼ä
//				if((Distance2>=100)&&(Distance2<1000))
//					printf("0%d",Distance2);//´òÓ¡×ÜµÄ¸ßµãÆ½Ê±¼ä
//				if(Distance2>=1000)
//					printf("%d",Distance2);//´òÓ¡×ÜµÄ¸ßµãÆ½Ê±¼ä
				TIM4CH1_CAPTURE_STA=0;//¿ªÆôÏÂÒ»´Î²¶»ñ
				flag2=1;
			}
			
			if(TIM2CH1_CAPTURE_STA&0X80)//³É¹¦²¶»ñµ½ÁËÒ»´ÎÉÏÉýÑØ
			{
				temp=TIM2CH1_CAPTURE_STA&0X3F;
				temp*=65536;//Òç³öÊ±¼ä×ÜºÍ
				temp+=TIM2CH1_CAPTURE_VAL;//µÃµ½×ÜµÄ¸ßµçÆ½Ê±¼ä
				Distance3=temp*170.0/10000;
				
//				if(Distance3<100)
//					printf("00%d",Distance3);//´òÓ¡×ÜµÄ¸ßµãÆ½Ê±¼ä
//				if((Distance3>=100)&&(Distance3<1000))
//					printf("0%d",Distance3);//´òÓ¡×ÜµÄ¸ßµãÆ½Ê±¼ä
//				if(Distance3>=1000)
//					printf("%d",Distance3);//´òÓ¡×ÜµÄ¸ßµãÆ½Ê±¼ä
				TIM2CH1_CAPTURE_STA=0;//¿ªÆôÏÂÒ»´Î²¶»ñ
				flag3=1;
			}
			
			if(flag1==1&&flag2==1&&flag3==1)
			{
					flag1=0;flag2=0;flag3=0;
					cache[0]=0x0b;
					cache[1]=Distance1/1000;
					cache[2]=Distance1%1000/100;
					cache[3]=Distance1%1000%100/10;
					cache[4]=Distance1%1000%100%10;
				
					cache[5]=Distance2/1000;
					cache[6]=Distance2%1000/100;
					cache[7]=Distance2%1000%100/10;
					cache[8]=Distance2%1000%100%10;
				
					cache[9]=Distance3/1000;
					cache[10]=Distance3%1000/100;
					cache[11]=Distance3%1000%100/10;
					cache[12]=Distance3%1000%100%10;
				
					cache[13]=0x0d;
				for(i=0;i<14;i++)
					{
						//while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						//printf("%d",cache[i]);
						USART_SendData(USART1,cache[i]);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
					}
				//printf("\n");
			}
			delay_ms(500);
		}	 
}


