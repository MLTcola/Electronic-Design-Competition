 #include "12864.h"
 #include "led.h"
 #include "delay.h"
 
 /********************************************************************
* ���� : sendbyte()
* ���� : ����Һ���Ĵ���ͨ��Э�飬��������
* ���� : zdata
* ��� : ��
***********************************************************************/
void sendbyte(unsigned char zdata)
{
	unsigned int i;
	for(i=0; i<8; i++)
	{
		if((zdata << i) & 0x80)
		{
			SID = 1;
		}
		else 
		{
			SID = 0;
		}
		CLK = 0;
		CLK = 1;
	}
}

/********************************************************************
* ���� : write_com()
* ���� : д����ָ��
* ���� : cmdcode
* ��� : ��
***********************************************************************/
void write_com(unsigned char cmdcode)
{
	CS = 1;
	sendbyte(0xf8);
	sendbyte(cmdcode & 0xf0);
	sendbyte((cmdcode << 4) & 0xf0);
	delay_us(200);
}

/********************************************************************
* ���� : write_data()
* ���� : д����ָ��
* ���� : cmdcode
* ��� : ��
***********************************************************************/
void write_data(unsigned char Dispdata)
{
	CS = 1;
	sendbyte(0xfa);
	sendbyte(Dispdata & 0xf0);
	sendbyte((Dispdata << 4) & 0xf0);
	delay_us(200);
}

/********************************************************************
* ���� : lcdinit()
* ���� : ��ʼ������
* ���� : cmdcode
* ��� : ��
***********************************************************************/
void lcdinit()
{  
	delay_ms(20);
	write_com(0x30);
	delay_ms(5);
	write_com(0x0c);
	delay_ms(5);
}

/********************************************************************
* ���� : DispString()
* ���� : ��ʾ�ַ���
* ���� : *s
* ��� : ��
***********************************************************************/
void DispString (unsigned char *s)
{  
	while(*s > 0)
    { 
		write_data(*s);
		s++;
		delay_ms(5);
    }
}

/********************************************************************
* ���� : Test()
* ���� : ��ʾ�Ӻ���
* ���� : ��
* ��� : ��
***********************************************************************/
void Test()
{  
//	write_com(0x03);
//	delay_ms(5);    
//	write_com(0x81);
//	DispString(" ���ϰ�");
//	write_com(0x91);
//	DispString("���ϰ�niubi");
//	write_com(0x89);
//	DispString("          ");
//	write_com(0x98);
//	DispString("  343   ");
}

void Lcd_12864_Init()
{
		PSB = 0;	 //ѡ���з�ʽ
		delay_us(100);
		lcdinit();
		delay_us(100);
}

/*
*****************************************************************************
** �� �� �� ��void Lcd12232_MoveToXY(uint8 x, uint8 y)  
** ��    �� ��������Ƶ�ָ��λ�� 
** ˵    �� ����һ�е�ַΪ80H~87H �ڶ��е�ַ90H~97H
** ��ڲ��� ��
** �� �� ֵ ����
** ˵��     ��
*****************************************************************************/
void LCD_MoveToXY(unsigned char x, unsigned char y)  
{
	switch(x)
	{
		case 0:
			write_com(0x80 + y);
			break;
		case 1 :
			write_com(0x90 + y);
			break;
		case 2 :
			write_com(0x88 + y);
			break;
		case 3 :
			write_com(0x98 + y);
			break;
		default :
			break;
	}
}

void  LCD_StrShow(char *str, unsigned char x,unsigned char y)
{
	LCD_MoveToXY(x,y);

	while(*str)
	{
		write_data(*str++);
	}
}



