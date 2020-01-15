#include "key.h"
#include "delay.h"
#include "led.h"
/*****************************************************************************
** 函数名称 ：KEY_Init
** 函数功能 ：初始化按键IO
** 入口参数 ：无
** 出口参数 ：无
** 说明     ：外部调用,初始化按键IO
*****************************************************************************/
void KEY_Init(void) 
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;   //行设置为推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;  //列设置下拉输入
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPD;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
		 

}
/*****************************************************************************
** 函数名称 ：KEY_Scan
** 函数功能 ：键值获取
** 入口参数 ：无
** 出口参数 ：1-9按键码  未按下: 0x00    连接错误: 0xff
** 说明     ：内部调用,初始化按键IO
*****************************************************************************/

uint8_t KEY_Scan(void)
{	 
	uint8_t temp=0;                   //临时值
	GPIOC->ODR = (GPIOC->ODR&0xFF00)|0xFF07;   //将PC 0.1.2	设置为输出 1  及行输出为1
	temp =( GPIOC->IDR&0xFF3f);       //获取345端口的值  11,1000 列值
	if(temp!= 0x07)                   //获取高六位的值 如果不同则表示按键已经按下  获取六个IO状态00.0111
	{
		delay_ms(10);//去抖动
		if(temp!= 0x07)                   //确实有键按下
	  {
			F=0;
			pagestate=0;
		switch(temp)
		{
	/************************第一列被触发**************************************************************/		
			case 0x0f:  
				PCout(0)=0;//将第一行设置为零
				if(PCin(3)== 0)//获取列的值 如果获取的值为0则表示[1.1]按下
				{				
				return KEY1; }  //返回键值 并跳出循环

				PCout(1)=0;//将第二行设置为零 
				if(PCin(3)== 0)//获取列的值 如果获取的值为0则表示[2.1]按下
				{				
				return KEY4;}  //返回键值 跳出
				
				PCout(2)=0;//将第三行设置为零 
				if(PCin(3)== 0)//获取列的值 如果获取的值为0 则表示[3.1]按下
				{				
				return KEY7;}  //返回键值 跳出
				break;
				
/**************************第二列被触发************************************************************/					
			case 0x17: 
				PCout(0)=0;//将第一行设置为零
				if(PCin(4)== 0)//获取列的值 如果获取的值为0 则表示[2.1]按下
				{				
				return KEY2;}  //返回键值 并跳出循环

				PCout(1)=0;//将第二行设置为零 1010,0000
				if(PCin(4)== 0)//获取高六位的值 如果获取的值为0 则表示[2.2]按下 
				{				
				return KEY5;}  //返回键值 跳出
				
				PCout(2)=0;//将第三行设置为零 1100,0000
				if(PCout(4)== 0)//获取高六位的值 如果获取的值为0 则表示[2.3]按下 
				{				
				return KEY8;}  //返回键值 跳出
				break;
				
	/**************************第三列被触发************************************************************/				
			case 0x27: 
				PCout(0)=0;//将第一行设置为零
				if(PCin(5)== 0)//获取列的值 如果获取的值为0则表示第一个按键按下
				{				
				return KEY3;}  //返回键值 并跳出循环

				PCout(1)=0;//将第二行设置为零 1010,0000
				if(PCin(5)== 0)//获取高六位的值 如果获取的值为1010,00 则表示第一个按键按下
				{
				return KEY6;}  //返回键值 跳出
				
				PCout(2)=0;//将第三行设置为零 1100,0000
				if(PCin(5)== 0)//获取高六位的值 如果获取的值为1100,00 则表示第一个按键按下
				{
				return KEY9;}  //返回键值 跳出
				break;
				
				
		}
	}
	else
		return 0x00;//未按下
   
} 
	return 0xff; //	键盘连接错误..  正常是执行不到这的
}


u8 KEY_get(void)
{
	static u8 KEY=0;
	if(KEY1==KEY_Scan())
	{
	//	delay_ms(10);//去抖动
		if(KEY1==KEY_Scan()) //确实是KEY1按下
		{
			KEY=1;
			while(KEY1==KEY_Scan()); //松手
			delay_ms(10);//去抖动
		}
	}
	
	if(KEY2==KEY_Scan())
	{
	//	delay_ms(10);//去抖动
		if(KEY2==KEY_Scan()) //确实是KEY2按下
		{
			KEY=2;
			while(KEY2==KEY_Scan()); //松手
			delay_ms(10);//去抖动
		}
	}
	
	if(KEY3==KEY_Scan())
	{
	//	delay_ms(10);//去抖动
		if(KEY3==KEY_Scan()) //确实是KEY3按下
		{
			KEY=3;
			while(KEY3==KEY_Scan()); //松手
			delay_ms(10);//去抖动
		}
	}
	
	if(KEY4==KEY_Scan())
	{
	//	delay_ms(10);//去抖动
		if(KEY4==KEY_Scan()) //确实是KEY4按下
		{
			KEY=4;
			while(KEY4==KEY_Scan()); //松手
			delay_ms(10);//去抖动
		}
	}
	
	if(KEY5==KEY_Scan())
	{
	//	delay_ms(10);//去抖动
		if(KEY5==KEY_Scan()) //确实是KEY5按下
		{
			KEY=5;
			while(KEY5==KEY_Scan()); //松手
			delay_ms(10);//去抖动
		}
	}
	
	if(KEY6==KEY_Scan())
	{
	//	delay_ms(10);//去抖动
		if(KEY6==KEY_Scan()) //确实是KEY6按下
		{
			KEY=6;
			while(KEY6==KEY_Scan()); //松手
			delay_ms(10);//去抖动
		}
	}
	
	if(KEY7==KEY_Scan())
	{
	//	delay_ms(10);//去抖动
		if(KEY7==KEY_Scan()) //确实是KEY7按下
		{
			KEY=7;
			while(KEY7==KEY_Scan()); //松手
			delay_ms(10);//去抖动
		}
	}
	
	if(KEY8==KEY_Scan())
	{
	//	delay_ms(10);//去抖动
		if(KEY8==KEY_Scan()) //确实是KEY8按下
		{
			KEY=8;
			while(KEY8==KEY_Scan()); //松手
			delay_ms(10);//去抖动
		}
	}
	
	if(KEY9==KEY_Scan())
	{
	//	delay_ms(10);//去抖动
		if(KEY9==KEY_Scan()) //确实是KEY9按下
		{
			KEY=9;
			while(KEY9==KEY_Scan()); //松手
			delay_ms(10);//去抖动
		}
	}
	return KEY;
}

