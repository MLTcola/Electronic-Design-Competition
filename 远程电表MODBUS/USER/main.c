#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h" 
#include "rs485.h"
//#include "usart1.h"
#include "modbusCRC.h"

float changeint(u32 num);
float changefloat(u32 num);
u32 cifangint(u16 i);
float cifangfloat(u16 i);

u32 add(u8 b,u8 c,u8 d,u8 e);

u8 PowerTable[8]={  0x02,//表地址
										0x04,//功能码
										0x00,0x00,//表内部内存器地址
										0x00,0x02,//读两个字的数据
										0x71,0xF8};//CRC校验

u8 flag;
u8 flag1=1;
float PowerSum;
u32 a;			
 int main(void)
 {	
//	u16 t;  
//	uint crc;
	 float PowerShiWei;
	 float PowerGeWei;
	delay_init();	    //延时函数初始化	  
	LED_Init();	
	
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	USART1_Init();
	 uart_init(9600);
	 RS485_Init(9600);
 /*数组为49e48e68
		PowerShiWei=changeint(0x49e4);//电量十位
		PowerGeWei=changefloat(0x49e4);//电量各位
		PowerSum=PowerShiWei*(1+PowerGeWei);//总和
		printf("%f",PowerSum);
		*/
	while(1)
	{
		if(USART_RX_STA)
		{
			flag1=1;
		}
		else
		{
			flag1=0;
		}
		if(USART_RX_BUF[0]==0x13&&USART_RX_BUF[1]==0x14&&flag1==1)
		{
				RS485_Send_Data(PowerTable,8);	
			USART_RX_STA=0;
		} 
			
		delay_ms(200);
		if(RS485_RX_CNT)
		{
			RS485_RX_CNT=0;
			if(RS485_RX_BUF[0]==0x02)
			{
				a=add(RS485_RX_BUF[3],RS485_RX_BUF[4],RS485_RX_BUF[5],RS485_RX_BUF[6]);
				PowerShiWei=changeint(a);//电量十位
				PowerGeWei=changefloat(a);//电量各位
				PowerSum=PowerShiWei*(1.0000+PowerGeWei);//总和
				delay_ms(100);
				USART_SendData(USART1,0x00);
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			USART_SendData(USART1,0x04);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			USART_SendData(USART1,0x01);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
				delay_ms(5);
				USART_SendData(USART1,0x00);
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			USART_SendData(USART1,0x04);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			USART_SendData(USART1,0x01);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
				printf("Electric meter1：%f kW.h",PowerSum);
				printf("\r\n\r\n");//插入换行
				RS485_RX_BUF[0]=0xff;
			}
		}
	}
 }

 u32 add(u8 b,u8 c,u8 d,u8 e)
 {
		u32 flag=0x00000000;
		flag=flag|b;
		flag=flag<<8;
	 
	 flag=flag|c;
		flag=flag<<8;
	 
	 flag=flag|d;
		flag=flag<<8;
	 
	 flag=flag|e;
	 
	 return flag;
 }
 
 float changeint(u32 num)
 {
		u16 shiweinum=0;
		float shiwei=0;
	 int i;
	 num=num>>23;
	 shiweinum=num; 
	 for(i=0;i<8;i++)
	 {
			shiweinum=shiweinum&0x00000001;
			shiwei=shiwei+shiweinum*cifangint(i);
		 num=num>>1;	 
		 shiweinum=num;		 
	 }
	
	 if(shiwei<127)
		 shiwei=cifangfloat(127-shiwei);
	 else
			shiwei=cifangint(shiwei-127);
	 return shiwei;
 }
 
 float changefloat(u32 num)
 {
		u32 shiweinum=0;
		float shiwei=0;
	 int i;
	 num=num<<9;
	 shiweinum=num; 
	 for(i=1;i<23;i++)
	 {
		 if(shiweinum&0x80000000)
			 shiweinum=1;
		 else  
			 shiweinum=0;
		shiwei=shiwei+shiweinum*cifangfloat(i);
		 num=num<<1;	 
		 shiweinum=num;		 
	 }
	 return shiwei;
 }
 u32 cifangint(u16 i)
 {
	 int m=0;
	 u32 num=1;
		for(m=0;m<i;m++)
	 {
			num=2*num;
	 }
	 return num;
 }
 
 float cifangfloat(u16 i)
 {
		int m=0;
		float num=1;
		for(m=0;m<i;m++)
	 {
			num=num/2;
	 }
	 return num;
 }
 /**
 *****************下面注视的代码是通过调用库函数来实现IO控制的方法*****************************************
int main(void)
{ 
 
	delay_init();		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	while(1)
	{
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);  //LED0对应引脚GPIOB.5拉低，亮  等同LED0=0;
			GPIO_SetBits(GPIOE,GPIO_Pin_5);   //LED1对应引脚GPIOE.5拉高，灭 等同LED1=1;
			delay_ms(300);  		   //延时300ms
			GPIO_SetBits(GPIOB,GPIO_Pin_5);	   //LED0对应引脚GPIOB.5拉高，灭  等同LED0=1;
			GPIO_ResetBits(GPIOE,GPIO_Pin_5); //LED1对应引脚GPIOE.5拉低，亮 等同LED1=0;
			delay_ms(300);                     //延时300ms
	}
} 
 
 ****************************************************************************************************
 ***/
 

	
/**
*******************下面注释掉的代码是通过 直接操作寄存器 方式实现IO口控制**************************************
int main(void)
{ 
 
	delay_init();		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	while(1)
	{
     GPIOB->BRR=GPIO_Pin_5;//LED0亮
	   GPIOE->BSRR=GPIO_Pin_5;//LED1灭
		 delay_ms(300);
     GPIOB->BSRR=GPIO_Pin_5;//LED0灭
	   GPIOE->BRR=GPIO_Pin_5;//LED1亮
		 delay_ms(300);

	 }
 }
**************************************************************************************************
**/

