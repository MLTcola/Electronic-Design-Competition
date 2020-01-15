#include "relay.h"
#include "DataHandle.h"
 
void RelayInit()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PE端口时钟
	
	//RT1
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 
 GPIO_SetBits(GPIOB,GPIO_Pin_5);		

	//RT2
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);					 
 GPIO_SetBits(GPIOD,GPIO_Pin_2);		

	//RT3
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 
 GPIO_SetBits(GPIOC,GPIO_Pin_12);			
}


void RelayWork(float tem)
{
	u16 max;
	max=APhaseCurrentMax;
	if(max<BPhaseCurrentMax)
		max=BPhaseCurrentMax;
	if(max<CPhaseCurrentMax)
		max=CPhaseCurrentMax;
	
//	if(APhaseCurrentMax>CurrentSetting)
//	{
//		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
//	}
//	else
//	{
//		GPIO_SetBits(GPIOB,GPIO_Pin_5);
//	}
//	
//	if(BPhaseCurrentMax>CurrentSetting)
//	{
//		GPIO_ResetBits(GPIOD,GPIO_Pin_2);
//	}
//	else
//	{
//		GPIO_SetBits(GPIOD,GPIO_Pin_2);
//	}
//	
//	if(CPhaseCurrentMax>CurrentSetting)
//	{
//		GPIO_ResetBits(GPIOC,GPIO_Pin_12);
//	}
//	else
//	{
//		GPIO_SetBits(GPIOC,GPIO_Pin_12);
//	}
//	if((NegativeSequence((float)APhaseVoltageMax*522.3/4096,0,(float)BPhaseVoltageMax*522.3/4096,120,(float)BPhaseVoltageMax*522.3/4096,-120)>VolageSetting))  //整定电流，负序电压
			if(tem>VolageSetting&&tem<3.9)  //整定电流，负序电压             夫婿低电压启动
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_13);
			GPIO_ResetBits(GPIOD,GPIO_Pin_2);
			GPIO_ResetBits(GPIOC,GPIO_Pin_12);
				GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		}
		else
		{
			 GPIO_SetBits(GPIOB,GPIO_Pin_5);	
			 GPIO_SetBits(GPIOD,GPIO_Pin_2);
			 GPIO_SetBits(GPIOC,GPIO_Pin_12);
			 GPIO_SetBits(GPIOB,GPIO_Pin_13);
		}
}





