#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "adc.h"
#include "12864.h"
#include "DataHandle.h"
#include "timer.h"
#include "relay.h"
 
long APhaseCurrentMax, APhaseCurrentAngle,BPhaseCurrentMax,BPhaseCurrentAngle,CPhaseCurrentMax,CPhaseCurrentAngle,APhaseVoltageMax, APhaseVoltageAngle,BPhaseVoltageMax, BPhaseVoltageAngle,CPhaseVoltageMax, CPhaseVoltageAngle;
 
 u8 KeyUtimate;//键盘最后值
float CurrentSetting;//电流整定值
float VolageSetting;//电流整定值
u8 page=1;//处在初级界面
u8 hang=1;//处在第几行
char s[4];
u8 n=0;
u8 sta=0;
int ele=0;
u8 F=0;
u8 g=0;
u8 pagestate=0;
u16 sample[20];
float tem=0;
//int maya=0;
 
void welcome(); 
void Start();
void Election();
void TimeData(u16 ACM,u16 ACA,u16 BCM,u16 BCA,u16 CCM,u16 CCA,u16 AVM,u16 AVA,u16 BVM,u16 BVA,u16 CVM,u16 CVA,u16 num);
void ChangeSetting(float current,float volage); 
 
 int main(void)
 {	
	int i=1;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
 	LED_Init();			     //LED端口初始化	
	KEY_Init();	 
 	Adc_Init();		  		//ADC初始化
	TIM3_Int_Init(499,7199);//50ms检测一次
	Lcd_12864_Init();
	RelayInit();
	 
	CurrentSetting=1.62;
	VolageSetting=2; 
	 
	KeyUtimate=0;	
	GPIO_SetBits(GPIOC,GPIO_Pin_12);
	while(1)
	{			
		while(n<=13)
			welcome();
		sta=1;
		while(sta==1)
		{
			if(page==1&&pagestate==0)
			{
				Start();
				pagestate=1;
			}
			while(page==2&&KeyUtimate!=3)
			{
				
				for(g=1;g<6;g++)
				{
					AdcFourier(g);
					delay_ms(5);
				}
				if((page==2&&pagestate==0))
				{
//					maya=0;
//					RelayWork();
					pagestate=1;
					if(KeyUtimate==8)
					{
						i++;///////////////////////////////
					}
						if(i==1)
						{
							delay_ms(50);
							AdcFourier(0);
							delay_ms(100);
							TimeData(APhaseCurrentMax,APhaseCurrentAngle,BPhaseCurrentMax,BPhaseCurrentAngle,CPhaseCurrentMax,CPhaseCurrentAngle,
										APhaseVoltageMax,APhaseVoltageAngle,BPhaseVoltageMax,BPhaseVoltageAngle,CPhaseVoltageMax,CPhaseVoltageAngle,i);				
						}
						if(i==2)
						{		
							delay_ms(50);
							AdcFourier(1);
							delay_ms(100);
							TimeData(APhaseCurrentMax,APhaseCurrentAngle,BPhaseCurrentMax,BPhaseCurrentAngle,CPhaseCurrentMax,CPhaseCurrentAngle,
										APhaseVoltageMax,APhaseVoltageAngle,BPhaseVoltageMax,BPhaseVoltageAngle,CPhaseVoltageMax,CPhaseVoltageAngle,i);
						}
						if(i==3)
						{
							delay_ms(50);
							AdcFourier(2);
							delay_ms(100);
							TimeData(APhaseCurrentMax,APhaseCurrentAngle,BPhaseCurrentMax,BPhaseCurrentAngle,CPhaseCurrentMax,CPhaseCurrentAngle,
										APhaseVoltageMax,APhaseVoltageAngle,BPhaseVoltageMax,BPhaseVoltageAngle,CPhaseVoltageMax,CPhaseVoltageAngle,i);
						}
						if(i==4)
						{
							delay_ms(50);
							AdcFourier(3);
							delay_ms(100);
							TimeData(APhaseCurrentMax,APhaseCurrentAngle,BPhaseCurrentMax,BPhaseCurrentAngle,CPhaseCurrentMax,CPhaseCurrentAngle,
										APhaseVoltageMax,APhaseVoltageAngle,BPhaseVoltageMax,BPhaseVoltageAngle,CPhaseVoltageMax,CPhaseVoltageAngle,i);
						}
						if(i==5)
						{
							delay_ms(50);
							AdcFourier(4);
							delay_ms(100);
							TimeData(APhaseCurrentMax,APhaseCurrentAngle,BPhaseCurrentMax,BPhaseCurrentAngle,CPhaseCurrentMax,CPhaseCurrentAngle,
										APhaseVoltageMax,APhaseVoltageAngle,BPhaseVoltageMax,BPhaseVoltageAngle,CPhaseVoltageMax,CPhaseVoltageAngle,i);
						}
						if(i==6)
						{
							delay_ms(50);
							AdcFourier(5);
							delay_ms(100);
							TimeData(APhaseCurrentMax,APhaseCurrentAngle,BPhaseCurrentMax,BPhaseCurrentAngle,CPhaseCurrentMax,CPhaseCurrentAngle,
										APhaseVoltageMax,APhaseVoltageAngle,BPhaseVoltageMax,BPhaseVoltageAngle,CPhaseVoltageMax,CPhaseVoltageAngle,i);
						}
						if(i==7)
						{
							while(i==7&&KeyUtimate!=3)
							{
								delay_ms(500);
								
									
									for(g=1;g<6;g++)
									{
										AdcFourier(g);
										delay_ms(5);
									}  
								TimeData(APhaseCurrentMax,APhaseCurrentAngle,BPhaseCurrentMax,BPhaseCurrentAngle,CPhaseCurrentMax,CPhaseCurrentAngle,
										APhaseVoltageMax,APhaseVoltageAngle,BPhaseVoltageMax,BPhaseVoltageAngle,CPhaseVoltageMax,CPhaseVoltageAngle,7);
								RelayWork(tem);
									if(tem>4)
									{
														 GPIO_SetBits(GPIOB,GPIO_Pin_5);	
										 GPIO_SetBits(GPIOD,GPIO_Pin_2);
										 GPIO_SetBits(GPIOC,GPIO_Pin_12);
										 GPIO_SetBits(GPIOB,GPIO_Pin_13);
									}
							}
						}
						if(i==7) i=0;
					}
			}
			
			while(page==3&&KeyUtimate!=3)
			{
				if(page==3&&pagestate==0)
				{					
					pagestate=1;
					if(KeyUtimate==4)
					{
						CurrentSetting=CurrentSetting+0.01;
					}
					if(KeyUtimate==6)
					{
						CurrentSetting=CurrentSetting-0.01;
					}
					if(KeyUtimate==7)
					{
						VolageSetting=VolageSetting+0.01;
					}
					if(KeyUtimate==9)
					{
						VolageSetting=VolageSetting-0.01;
					}
					ChangeSetting(CurrentSetting,VolageSetting);
			}
				if(KeyUtimate==3) 
				{
					page=1;
					hang=1;
					pagestate=0;
				}
		}
//			RelayWork();
	}
 }
} 

void ChangeSetting(float current,float volage)
{
		LCD_StrShow("电流",0,0);
		sprintf(s, "%3.2f",current);
		LCD_StrShow(s,0,2);
		LCD_StrShow("        ",0,4);
	
		LCD_StrShow("                  ",1,0);
	
		LCD_StrShow("电压",2,0);
		sprintf(s, "%3.2f",volage);
		LCD_StrShow(s,2,3);
	LCD_StrShow("        ",2,5);
		LCD_StrShow("确定",3,0);
		LCD_StrShow("返回",3,6);
}

void TimeData(u16 ACM,u16 ACA,u16 BCM,u16 BCA,u16 CCM,u16 CCA,u16 AVM,u16 AVA,u16 BVM,u16 BVA,u16 CVM,u16 CVA,u16 num)
{
	
	if(num==1)
	{
//		write_com(0x01);	//清除显示
		LCD_StrShow("A 相电流：",0,0);
		LCD_StrShow("    ",0,4);	
		LCD_StrShow("幅值：",1,0);
		sprintf(s, "%3.2f", (float)ACM*44.2/4096 );
		LCD_StrShow(s,1,3);
		LCD_StrShow("    ",1,5);
		
		LCD_StrShow("角度：",2,0);
		sprintf(s, "%3.1f", (float) ACA*44.2/4096 );
		LCD_StrShow(s,2,3);
		LCD_StrShow("    ",2,5);
		LCD_StrShow("确定",3,0);
		LCD_StrShow("返回",3,6);
	}
	
	if(num==2)
	{
//		write_com(0x01);	//清除显示
		LCD_StrShow("B 相电流：",0,0);
		LCD_StrShow("    ",0,4);	
		LCD_StrShow("幅值：",1,0);
		sprintf(s, "%3.2f", (float) BCM*44.2/4096 );
		LCD_StrShow(s,1,3);
		LCD_StrShow("    ",1,5);
		
		LCD_StrShow("角度：",2,0);
		sprintf(s, "%3.2f", (float) BCA*44.2/4096 );
		LCD_StrShow(s,2,3);
		LCD_StrShow("    ",2,5);
		LCD_StrShow("确定",3,0);
		LCD_StrShow("返回",3,6);
	}
	
	if(num==3)
	{
		LCD_StrShow("C 相电流：",0,0);
		LCD_StrShow("    ",0,4);	
		LCD_StrShow("幅值：",1,0);
		sprintf(s, "%3.2f", (float) CCM*44.2/4096);
		LCD_StrShow(s,1,3);
		LCD_StrShow("    ",1,5);
		
		LCD_StrShow("角度：",2,0);
		sprintf(s, "%3.2f", (float)CCA*44.2/4096);
		LCD_StrShow(s,2,3);
		LCD_StrShow("    ",2,5);
		LCD_StrShow("确定",3,0);
		LCD_StrShow("返回",3,6);
	}
	if(num==4)
	{
		LCD_StrShow("A 相电压：",0,0);
		LCD_StrShow("    ",0,4);	
		LCD_StrShow("幅值：",1,0);
		sprintf(s, "%3.2f", (float)AVM*663.3/4096);
		LCD_StrShow(s,1,3);
		LCD_StrShow("    ",1,5);
		
		LCD_StrShow("角度：",2,0);
		sprintf(s, "%3.2f", (float)AVA*663.3/4096);
		LCD_StrShow(s,2,3);
		LCD_StrShow("    ",2,5);
		LCD_StrShow("确定",3,0);
		LCD_StrShow("返回",3,6);
	}
	if(num==5)
	{
		LCD_StrShow("B 相电压：",0,0);
		LCD_StrShow("    ",0,4);	
		LCD_StrShow("幅值：",1,0);
		sprintf(s, "%3.2f", (float)BVM*663.3/4096);
		LCD_StrShow(s,1,3);
		LCD_StrShow("    ",1,5);
		
		LCD_StrShow("角度：",2,0);
		sprintf(s, "%3.2f", (float)BVA*663.3/4096);
		LCD_StrShow(s,2,3);
		LCD_StrShow("    ",2,5);
		LCD_StrShow("确定",3,0);
		LCD_StrShow("返回",3,6);
	}
	if(num==6)
	{
		LCD_StrShow("C 相电压：",0,0);
		LCD_StrShow("    ",0,4);	
		LCD_StrShow("幅值：",1,0);
		sprintf(s, "%3.2f", (float)CVM*663.3/4096);
		LCD_StrShow(s,1,3);
		LCD_StrShow("    ",1,5);
		
		LCD_StrShow("角度：",2,0);
		sprintf(s, "%3.2f", (float)CVA*663.3/4096);
		LCD_StrShow(s,2,3);
		LCD_StrShow("    ",2,5);
		LCD_StrShow("确定",3,0);
		LCD_StrShow("返回",3,6);
	}
	if(num==7)
	{
		LCD_StrShow("负序电流",0,0);
		LCD_StrShow("    ",0,4);	
		tem=(float)(NegativeSequence((float)APhaseVoltageMax*663.3/4096,0,(float)BPhaseVoltageMax*663.3/4096,120,(float)CPhaseVoltageMax*663.3/4096,-120)-0.20);
		{
		if(tem<2)
		{
			tem=0.05;
		}
		if(tem>4.5)
		{tem=0.04;
		}		
		}
		sprintf(s, "%3.2f  ", tem);
//		LCD_StrShow("      ",2,6);	
		LCD_StrShow(s,1,0);	
		LCD_StrShow("            ",1,3);
		LCD_StrShow("                ",2,0);	
		LCD_StrShow("                ",3,0);	
		LCD_StrShow("确定",3,0);
		LCD_StrShow("返回",3,6);
	}
}

void Start()
{	
			delay_ms(500);
			LCD_StrShow("--> ",0,0);
			LCD_StrShow("实时数据",0,2);
			LCD_StrShow("    ",1,0);
			LCD_StrShow("整定值调整",1,2);
			LCD_StrShow("确定",3,0);
			LCD_StrShow("返回",3,6);
	if(KeyUtimate==8&F==0)
	{
		F=1;
//		write_com(0x01);	//清除显示
		if(ele==1)
		{			
			LCD_StrShow("--> ",0,0);
			LCD_StrShow("实时数据",0,2);
			LCD_StrShow("    ",1,0);
			LCD_StrShow("整定值调整",1,2);
			LCD_StrShow("                ",2,0);
			LCD_StrShow("确定",3,0);
			LCD_StrShow("返回",3,6);			
			ele=0;
			hang=1;
		}
		else
		{
			LCD_StrShow("    ",0,0);
			LCD_StrShow("实时数据",0,2);
			LCD_StrShow("--> ",1,0);
			LCD_StrShow("整定值调整",1,2);
			LCD_StrShow("                ",2,0);
			LCD_StrShow("确定",3,0);
			LCD_StrShow("返回",3,6);
			ele=1;
			hang=2;
		}				
	}
}	
 
 void welcome()
 {
	 while(n==1)
		 write_com(0x01);	//清除显示
	 delay_ms(500);
		while(n==2)
			LCD_StrShow("欢迎",3,1);
		write_com(0x01);	//清除显示
		while(n==3)
			LCD_StrShow("欢迎",2,1);
		write_com(0x01);	//清除显示
		while(n==4)
			LCD_StrShow("欢迎",1,1);
		write_com(0x01);	//清除显示
		while(n==5)
			LCD_StrShow("欢迎",0,1);
		while(n==6)
		{
			LCD_StrShow("欢迎",0,1);
			LCD_StrShow("进入",3,3);
			
		}
		write_com(0x01);	//清除显示
		while(n==7)
		{
			LCD_StrShow("欢迎",0,1);
			LCD_StrShow("进入",2,3);
			
		}	write_com(0x01);	//清除显示
		 while(n==8)
		{
			LCD_StrShow("欢迎",0,1);
			LCD_StrShow("进入",1,3);		
		}
		write_com(0x01);	//清除显示
		while(n==9)
		{
			LCD_StrShow("欢迎",0,1);
			LCD_StrShow("进入",1,3);
			LCD_StrShow("M",2,5);
			LCD_StrShow("小队",2,6);
		}
		write_com(0x01);	//清除显示 
		while(n==10)
		{
			write_com(0x01);	//清除显示
		}
		while(n==11)
		{
			LCD_StrShow("  ",0,0);
			LCD_StrShow("欢迎",0,1);
			LCD_StrShow("进入",1,3);
			LCD_StrShow("M",2,5);
			LCD_StrShow("小队",2,6);
		}
		write_com(0x01);	//清除显示 
		while(n==12)
		{
			write_com(0x01);	//清除显示
		}
		while(n==13)
		{
			delay_ms(50);
			LCD_StrShow("欢迎",0,1);
			LCD_StrShow("进入",1,3);
			LCD_StrShow("M",2,5);
			LCD_StrShow("小队",2,6);
			sta=1;
		}
		write_com(0x01);	//清除显示 
		
 }
 
 
 
 
 
 
 
 
 
 

