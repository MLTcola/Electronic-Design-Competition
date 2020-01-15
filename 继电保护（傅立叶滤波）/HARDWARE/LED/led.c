#include "led.h" 

/******************************
12864:
nRST    PA12
PSB     PC6
CLK     PA11
SID     PB15  
CS      PA8

矩阵键盘
PC0~PC5
****************************
*/
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PE端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 
 GPIO_SetBits(GPIOB,GPIO_Pin_13);	
	
	//nRST
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 
 GPIO_SetBits(GPIOA,GPIO_Pin_12);						 
//PSB
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 
 GPIO_SetBits(GPIOC,GPIO_Pin_6);	
//CLK
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 
 GPIO_SetBits(GPIOA,GPIO_Pin_11);		
 //SID
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 
 GPIO_SetBits(GPIOB,GPIO_Pin_15);	
 //CS
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 
 GPIO_SetBits(GPIOA,GPIO_Pin_8);	

}
