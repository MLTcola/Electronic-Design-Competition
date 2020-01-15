#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "rs485.h"
#include "timer.h"
 
/************************************************
 ALIENTEKս��STM32������ʵ��25
 485ͨ��ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
extern u8  TIM5CH1_CAPTURE_STA;		//���벶��״̬		    				
extern u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ	
 				 	
 int main(void)
 {	 
	u8 rs485buf[6]; 
	u32 temp=0; 
	u16 Distance;
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD 	
	KEY_Init();				//������ʼ��		 	 
	RS485_Init(115200);	//��ʼ��RS485
 	TIM3_PWM_Init(899,0); 		//����Ƶ��PWMƵ��=72000/(899+1)=80Khz
 	TIM5_Cap_Init(0XFFFF,72-1);	//��1Mhz��Ƶ�ʼ��� 
	
 									  
	while(1)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
		delay_us(15);
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		delay_ms(70);
		
		TIM_SetCompare2(TIM3,TIM_GetCapture2(TIM3)+1);

		if(TIM_GetCapture2(TIM3)==300)TIM_SetCompare2(TIM3,0);	
		 		 
 		if(TIM5CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			temp=TIM5CH1_CAPTURE_STA&0X3F;
			temp*=65536;//���ʱ���ܺ�
			temp+=TIM5CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��  12345
			Distance=temp*170/100;	
			
			rs485buf[0]=Distance/10000+48;
			rs485buf[1]=Distance%10000/1000+48;
			rs485buf[2]=Distance%10000%1000/100+48;
			rs485buf[3]=46;
			rs485buf[4]=Distance%10000%1000%100/10+48;
			rs485buf[5]=Distance%10000%1000%100%10+48;

			RS485_Send_Data(rs485buf,6);//����5���ֽ�
				delay_ms(500);
			rs485buf[0]=10;
			RS485_Send_Data(rs485buf,1);//����5���ֽ�
	   	TIM5CH1_CAPTURE_STA=0;//������һ�β���
		} 
		
	}		
}
