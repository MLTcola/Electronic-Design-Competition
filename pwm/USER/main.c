#include "stm32f10x.h"
#include "delay.h"
#include "tim3.h"



 int main(void)
 {	
	 u16 led0pwmval=0;
	 u8 dir=1;
	 delay_init();
	 TIM3_PWM_Init(899,0);
	 while(1)
	 {
		 delay_ms(10);
		if(dir) led0pwmval++;
		 else  led0pwmval--;
		if(led0pwmval>300)dir=0;
		 if(led0pwmval==0) dir=1;
		 
	 TIM_SetCompare2(TIM3,led0pwmval);
	 }
 }
