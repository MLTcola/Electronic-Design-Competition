#include "key.h"
#include "delay.h"
#include "led.h"
/*****************************************************************************
** �������� ��KEY_Init
** �������� ����ʼ������IO
** ��ڲ��� ����
** ���ڲ��� ����
** ˵��     ���ⲿ����,��ʼ������IO
*****************************************************************************/
void KEY_Init(void) 
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;   //������Ϊ�������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;  //��������������
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPD;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
		 

}
/*****************************************************************************
** �������� ��KEY_Scan
** �������� ����ֵ��ȡ
** ��ڲ��� ����
** ���ڲ��� ��1-9������  δ����: 0x00    ���Ӵ���: 0xff
** ˵��     ���ڲ�����,��ʼ������IO
*****************************************************************************/

uint8_t KEY_Scan(void)
{	 
	uint8_t temp=0;                   //��ʱֵ
	GPIOC->ODR = (GPIOC->ODR&0xFF00)|0xFF07;   //��PC 0.1.2	����Ϊ��� 1  �������Ϊ1
	temp =( GPIOC->IDR&0xFF3f);       //��ȡ345�˿ڵ�ֵ  11,1000 ��ֵ
	if(temp!= 0x07)                   //��ȡ����λ��ֵ �����ͬ���ʾ�����Ѿ�����  ��ȡ����IO״̬00.0111
	{
		delay_ms(10);//ȥ����
		if(temp!= 0x07)                   //ȷʵ�м�����
	  {
			F=0;
			pagestate=0;
		switch(temp)
		{
	/************************��һ�б�����**************************************************************/		
			case 0x0f:  
				PCout(0)=0;//����һ������Ϊ��
				if(PCin(3)== 0)//��ȡ�е�ֵ �����ȡ��ֵΪ0���ʾ[1.1]����
				{				
				return KEY1; }  //���ؼ�ֵ ������ѭ��

				PCout(1)=0;//���ڶ�������Ϊ�� 
				if(PCin(3)== 0)//��ȡ�е�ֵ �����ȡ��ֵΪ0���ʾ[2.1]����
				{				
				return KEY4;}  //���ؼ�ֵ ����
				
				PCout(2)=0;//������������Ϊ�� 
				if(PCin(3)== 0)//��ȡ�е�ֵ �����ȡ��ֵΪ0 ���ʾ[3.1]����
				{				
				return KEY7;}  //���ؼ�ֵ ����
				break;
				
/**************************�ڶ��б�����************************************************************/					
			case 0x17: 
				PCout(0)=0;//����һ������Ϊ��
				if(PCin(4)== 0)//��ȡ�е�ֵ �����ȡ��ֵΪ0 ���ʾ[2.1]����
				{				
				return KEY2;}  //���ؼ�ֵ ������ѭ��

				PCout(1)=0;//���ڶ�������Ϊ�� 1010,0000
				if(PCin(4)== 0)//��ȡ����λ��ֵ �����ȡ��ֵΪ0 ���ʾ[2.2]���� 
				{				
				return KEY5;}  //���ؼ�ֵ ����
				
				PCout(2)=0;//������������Ϊ�� 1100,0000
				if(PCout(4)== 0)//��ȡ����λ��ֵ �����ȡ��ֵΪ0 ���ʾ[2.3]���� 
				{				
				return KEY8;}  //���ؼ�ֵ ����
				break;
				
	/**************************�����б�����************************************************************/				
			case 0x27: 
				PCout(0)=0;//����һ������Ϊ��
				if(PCin(5)== 0)//��ȡ�е�ֵ �����ȡ��ֵΪ0���ʾ��һ����������
				{				
				return KEY3;}  //���ؼ�ֵ ������ѭ��

				PCout(1)=0;//���ڶ�������Ϊ�� 1010,0000
				if(PCin(5)== 0)//��ȡ����λ��ֵ �����ȡ��ֵΪ1010,00 ���ʾ��һ����������
				{
				return KEY6;}  //���ؼ�ֵ ����
				
				PCout(2)=0;//������������Ϊ�� 1100,0000
				if(PCin(5)== 0)//��ȡ����λ��ֵ �����ȡ��ֵΪ1100,00 ���ʾ��һ����������
				{
				return KEY9;}  //���ؼ�ֵ ����
				break;
				
				
		}
	}
	else
		return 0x00;//δ����
   
} 
	return 0xff; //	�������Ӵ���..  ������ִ�в������
}


u8 KEY_get(void)
{
	static u8 KEY=0;
	if(KEY1==KEY_Scan())
	{
	//	delay_ms(10);//ȥ����
		if(KEY1==KEY_Scan()) //ȷʵ��KEY1����
		{
			KEY=1;
			while(KEY1==KEY_Scan()); //����
			delay_ms(10);//ȥ����
		}
	}
	
	if(KEY2==KEY_Scan())
	{
	//	delay_ms(10);//ȥ����
		if(KEY2==KEY_Scan()) //ȷʵ��KEY2����
		{
			KEY=2;
			while(KEY2==KEY_Scan()); //����
			delay_ms(10);//ȥ����
		}
	}
	
	if(KEY3==KEY_Scan())
	{
	//	delay_ms(10);//ȥ����
		if(KEY3==KEY_Scan()) //ȷʵ��KEY3����
		{
			KEY=3;
			while(KEY3==KEY_Scan()); //����
			delay_ms(10);//ȥ����
		}
	}
	
	if(KEY4==KEY_Scan())
	{
	//	delay_ms(10);//ȥ����
		if(KEY4==KEY_Scan()) //ȷʵ��KEY4����
		{
			KEY=4;
			while(KEY4==KEY_Scan()); //����
			delay_ms(10);//ȥ����
		}
	}
	
	if(KEY5==KEY_Scan())
	{
	//	delay_ms(10);//ȥ����
		if(KEY5==KEY_Scan()) //ȷʵ��KEY5����
		{
			KEY=5;
			while(KEY5==KEY_Scan()); //����
			delay_ms(10);//ȥ����
		}
	}
	
	if(KEY6==KEY_Scan())
	{
	//	delay_ms(10);//ȥ����
		if(KEY6==KEY_Scan()) //ȷʵ��KEY6����
		{
			KEY=6;
			while(KEY6==KEY_Scan()); //����
			delay_ms(10);//ȥ����
		}
	}
	
	if(KEY7==KEY_Scan())
	{
	//	delay_ms(10);//ȥ����
		if(KEY7==KEY_Scan()) //ȷʵ��KEY7����
		{
			KEY=7;
			while(KEY7==KEY_Scan()); //����
			delay_ms(10);//ȥ����
		}
	}
	
	if(KEY8==KEY_Scan())
	{
	//	delay_ms(10);//ȥ����
		if(KEY8==KEY_Scan()) //ȷʵ��KEY8����
		{
			KEY=8;
			while(KEY8==KEY_Scan()); //����
			delay_ms(10);//ȥ����
		}
	}
	
	if(KEY9==KEY_Scan())
	{
	//	delay_ms(10);//ȥ����
		if(KEY9==KEY_Scan()) //ȷʵ��KEY9����
		{
			KEY=9;
			while(KEY9==KEY_Scan()); //����
			delay_ms(10);//ȥ����
		}
	}
	return KEY;
}

