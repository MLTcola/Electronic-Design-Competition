#include "timer.h"
 
uint16_t tim4_counter = 0,atim4_counter = 0;
u16 ADC_Flag = 0;
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB,PE端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 //LED0-->PB.5 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	GPIO_SetBits(GPIOA,GPIO_Pin_4);						 //PB.5 输出高
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update );  	//清除TIMx更新中断标志 
		
		//LED0 = ~LED0;
		ADC_DAT_u32[ADC_DAT_INDEX_u16].real = (float)Get_Adc_Average(ADC_Channel_1,1);
		ADC_DAT_u32[ADC_DAT_INDEX_u16].imag = 0;
		if(++ADC_DAT_INDEX_u16==ADC_SIZE)
		{
			ADC_DAT_INDEX_u16=0;
			ADC_Flag = 1;
			TIM_Cmd(TIM3, DISABLE);//除能
		}
	}
}

void TIM4_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能
	
	//定时器TIM4初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM4向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据指定的参数初始化TIM4的时间基数单位
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM4中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM4, ENABLE);  //使能TIM4			
}
void TIM4_IRQHandler(void)   //TIM4中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM4更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIM4更新中断标志 
		
		TIM_Cmd(TIM3, ENABLE);  //使能TIMx
		
		tim4_counter++;																
		if(tim4_counter==50000)											//防止溢出tim4_counter（其实并不会溢出）
		{
			tim4_counter = 0;
			atim4_counter++;
		}
		
	}
}


//定时器5通道1输入捕获配置

TIM_ICInitTypeDef  TIM5_ICInitStructure;

void TIM5_Cap_Init(u16 arr,u16 psc)
{	 
	   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


//	TIM_Cmd(TIM5, ENABLE);  //使能TIMx	
	
	
	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//   	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能TIM5时钟
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟
//	
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;  //PA0 清除之前设置  
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 输入  
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_3);						 //PA0 下拉
//	
//	//初始化定时器5 TIM5	 
//	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
//  
//	//初始化TIM5输入捕获参数
//	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	选择输入端 IC1映射到TI1上
//  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
//  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
//  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
//  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
//  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
//	
//	//中断分组初始化
//	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
//	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
//	
//	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC4,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
//	
//   	TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5
//   
}


u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值
u32 num=0;
 
//定时器5中断服务程序	 
void TIM5_IRQHandler(void)
{ 
if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //清除TIMx更新中断标志 
		num++;	
		}
	
	
// 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
//	{	  
//		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
//		 
//		{	    
//			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
//			{
//				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
//				{
//					TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
//					TIM5CH1_CAPTURE_VAL=0XFFFF;
//				}else TIM5CH1_CAPTURE_STA++;
//			}	 
//		}
//	if (TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)//捕获1发生捕获事件
//		{	
//			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
//			{	  			
//				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
//				TIM5CH1_CAPTURE_VAL=TIM_GetCapture4(TIM5);
//		   		TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
//			}else  								//还未开始,第一次捕获上升沿
//			{
//				TIM5CH1_CAPTURE_STA=0;			//清空
//				TIM5CH1_CAPTURE_VAL=0;
//	 			TIM_SetCounter(TIM5,0);
//				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
//		   		TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Rising);		//CC1P=1 设置为下降沿捕获
//			}		    
//		}			     	    					   
// 	}
// 
//    TIM_ClearITPendingBit(TIM5, TIM_IT_CC4|TIM_IT_Update); //清除中断标志位
 
}










