#include "tim3.h"

void TIM3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitTypeSture;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeSture;
	TIM_OCInitTypeDef TIM_OCInitTypeSture;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
	
	GPIO_InitTypeSture.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitTypeSture.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitTypeSture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitTypeSture);
	
	TIM_TimeBaseInitTypeSture.TIM_Period=arr;
	TIM_TimeBaseInitTypeSture.TIM_Prescaler=psc;
	TIM_TimeBaseInitTypeSture.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitTypeSture.TIM_ClockDivision=0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitTypeSture);
	
	TIM_OCInitTypeSture.TIM_OCMode=TIM_OCMode_PWM2;
	TIM_OCInitTypeSture.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitTypeSture.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC2Init(TIM3,&TIM_OCInitTypeSture);
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM3,ENABLE);
}	

