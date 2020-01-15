#include "sys.h"
#include "usart.h"	  
#include "lcd.h" 
#include "usart1.h"
#include "rs485.h"


  u16 USART1_RX_STA=0;
  u8 USART1_RX_BUF[USART_REC_LEN]; 
void USART1_Init(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
	
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
GPIO_Init(GPIOA,&GPIO_InitStructure);
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
GPIO_Init(GPIOA,&GPIO_InitStructure);
	
USART_InitStructure.USART_BaudRate = 9600;//���ڲ�����
USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

USART_Init(USART1, &USART_InitStructure); //��ʼ������1	
USART_Cmd(USART1,ENABLE);
USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

	

	
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

}



//void  USART1_IRQHandler(void)
//{
//	u8 jieshou;
//	u8 i=0;
//  if(USART_GetITStatus(USART1,USART_IT_RXNE))
//	{
//	
//		jieshou=USART_ReceiveData(USART1);
//		if(USART1_RX_STA<64)
//		{
//			USART1_RX_BUF[USART1_RX_STA]=jieshou;		//��¼���յ���ֵ
//			USART1_RX_STA++;						//������������1 
//		} 
//		
//		
////		USART_SendData(USART2,jieshou);
//		RS485_Send_Data(USART1_RX_BUF,5);
//		LCD_ShowString(30,210,200,16,16,"Receive Data");
//		for(i=0;i<5;i++){
//		LCD_ShowxNum(30+i*32,230,USART1_RX_BUF[i],3,16,0X80);	//��ʾ����
//		}
//	
//	}
//}


