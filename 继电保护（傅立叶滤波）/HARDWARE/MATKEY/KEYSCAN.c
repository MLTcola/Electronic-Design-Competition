#include "KEYSCAN.h"
#include "delay.h"

unsigned char flagn=0;
void KeyScanInit(unsigned char flag)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PE端口时钟
	if(flagn==0)
	{
		//PC0
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 
	 GPIO_SetBits(GPIOC,GPIO_Pin_0);						 
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_5;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //推挽输入
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 
	 GPIO_SetBits(GPIOC,GPIO_Pin_4);						 
	}
	else if(flagn==1)
	{
	//PC0
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 
	 GPIO_SetBits(GPIOC,GPIO_Pin_0);						 
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_5;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输入
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOC, &GPIO_InitStructure);					 
	 GPIO_SetBits(GPIOC,GPIO_Pin_4);				
		
	}
}

u8 key;
u8 KeyValue;

u8 KeyScanValue(void)
{
	KeyScanInit(0);
	GPIO_WriteBit(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2,Bit_RESET);
//	GPIO_WriteBit(GPIOC,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5,Bit_SET);
	
	
	
	if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)&GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)&GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)))
	{
		delay_ms(10);
	if(~(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)&GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)&GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)))
		{
			GPIO_WriteBit(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2,Bit_RESET);
//			GPIO_WriteBit(GPIOC,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5,Bit_SET);
			if(~GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3))key=1;
			else if(~GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4))key=2;
			else if(~GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5))key=3;
			switch(key)
			{
				case(1):KeyValue=1;GPIO_ResetBits(GPIOB,GPIO_Pin_5);break;
				case(2):KeyValue=2;break;
				case(3):KeyValue=3;break;
			}
			
//			KeyScanInit(1);
//			
//			GPIO_WriteBit(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2,Bit_SET);
//			GPIO_WriteBit(GPIOC,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5,Bit_RESET);
//			key = GPIO_ReadInputData(GPIOC);
//			key=key&0x0007;
//			switch(key)
//			{
//				case(0x0006):KeyValue=KeyValue+0;break;
//				case(0x0005):KeyValue=KeyValue+3;break;
//				case(0x0003):KeyValue=KeyValue+6;break;
//			}
//			delay_ms(10);
		}
	}
	return KeyValue;
}









