#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "rs485.h"
#include "timer.h"
 
/************************************************
 ALIENTEK战舰STM32开发板实验25
 485通信实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
extern u8  TIM5CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值	
 				 	
 int main(void)
 {	 
	u8 rs485buf[6]; 
	u32 temp=0; 
	u16 Distance;
	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD 	
	KEY_Init();				//按键初始化		 	 
	RS485_Init(115200);	//初始化RS485
 	TIM3_PWM_Init(899,0); 		//不分频。PWM频率=72000/(899+1)=80Khz
 	TIM5_Cap_Init(0XFFFF,72-1);	//以1Mhz的频率计数 
	
 									  
	while(1)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
		delay_us(15);
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		delay_ms(70);
		
		TIM_SetCompare2(TIM3,TIM_GetCapture2(TIM3)+1);

		if(TIM_GetCapture2(TIM3)==300)TIM_SetCompare2(TIM3,0);	
		 		 
 		if(TIM5CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
		{
			temp=TIM5CH1_CAPTURE_STA&0X3F;
			temp*=65536;//溢出时间总和
			temp+=TIM5CH1_CAPTURE_VAL;//得到总的高电平时间  12345
			Distance=temp*170/100;	
			
			rs485buf[0]=Distance/10000+48;
			rs485buf[1]=Distance%10000/1000+48;
			rs485buf[2]=Distance%10000%1000/100+48;
			rs485buf[3]=46;
			rs485buf[4]=Distance%10000%1000%100/10+48;
			rs485buf[5]=Distance%10000%1000%100%10+48;

			RS485_Send_Data(rs485buf,6);//发送5个字节
				delay_ms(500);
			rs485buf[0]=10;
			RS485_Send_Data(rs485buf,1);//发送5个字节
	   	TIM5CH1_CAPTURE_STA=0;//开启下一次捕获
		} 
		
	}		
}
