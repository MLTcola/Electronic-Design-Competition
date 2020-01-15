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

u8 PowerTable[8]={  0x02,//���ַ
										0x04,//������
										0x00,0x00,//���ڲ��ڴ�����ַ
										0x00,0x02,//�������ֵ�����
										0x71,0xF8};//CRCУ��

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
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();	
	
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	USART1_Init();
	 uart_init(9600);
	 RS485_Init(9600);
 /*����Ϊ49e48e68
		PowerShiWei=changeint(0x49e4);//����ʮλ
		PowerGeWei=changefloat(0x49e4);//������λ
		PowerSum=PowerShiWei*(1+PowerGeWei);//�ܺ�
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
				PowerShiWei=changeint(a);//����ʮλ
				PowerGeWei=changefloat(a);//������λ
				PowerSum=PowerShiWei*(1.0000+PowerGeWei);//�ܺ�
				delay_ms(100);
				USART_SendData(USART1,0x00);
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			USART_SendData(USART1,0x04);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			USART_SendData(USART1,0x01);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
				delay_ms(5);
				USART_SendData(USART1,0x00);
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			USART_SendData(USART1,0x04);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			USART_SendData(USART1,0x01);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
				printf("Electric meter1��%f kW.h",PowerSum);
				printf("\r\n\r\n");//���뻻��
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
 *****************����ע�ӵĴ�����ͨ�����ÿ⺯����ʵ��IO���Ƶķ���*****************************************
int main(void)
{ 
 
	delay_init();		  //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED�˿�
	while(1)
	{
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);  //LED0��Ӧ����GPIOB.5���ͣ���  ��ͬLED0=0;
			GPIO_SetBits(GPIOE,GPIO_Pin_5);   //LED1��Ӧ����GPIOE.5���ߣ��� ��ͬLED1=1;
			delay_ms(300);  		   //��ʱ300ms
			GPIO_SetBits(GPIOB,GPIO_Pin_5);	   //LED0��Ӧ����GPIOB.5���ߣ���  ��ͬLED0=1;
			GPIO_ResetBits(GPIOE,GPIO_Pin_5); //LED1��Ӧ����GPIOE.5���ͣ��� ��ͬLED1=0;
			delay_ms(300);                     //��ʱ300ms
	}
} 
 
 ****************************************************************************************************
 ***/
 

	
/**
*******************����ע�͵��Ĵ�����ͨ�� ֱ�Ӳ����Ĵ��� ��ʽʵ��IO�ڿ���**************************************
int main(void)
{ 
 
	delay_init();		  //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED�˿�
	while(1)
	{
     GPIOB->BRR=GPIO_Pin_5;//LED0��
	   GPIOE->BSRR=GPIO_Pin_5;//LED1��
		 delay_ms(300);
     GPIOB->BSRR=GPIO_Pin_5;//LED0��
	   GPIOE->BRR=GPIO_Pin_5;//LED1��
		 delay_ms(300);

	 }
 }
**************************************************************************************************
**/

