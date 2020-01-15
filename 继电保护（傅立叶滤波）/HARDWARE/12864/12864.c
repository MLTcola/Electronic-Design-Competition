 #include "12864.h"
 #include "led.h"
 #include "delay.h"
 
 /********************************************************************
* 名称 : sendbyte()
* 功能 : 按照液晶的串口通信协议，发送数据
* 输入 : zdata
* 输出 : 无
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
* 名称 : write_com()
* 功能 : 写串口指令
* 输入 : cmdcode
* 输出 : 无
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
* 名称 : write_data()
* 功能 : 写串口指令
* 输入 : cmdcode
* 输出 : 无
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
* 名称 : lcdinit()
* 功能 : 初始化函数
* 输入 : cmdcode
* 输出 : 无
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
* 名称 : DispString()
* 功能 : 显示字符串
* 输入 : *s
* 输出 : 无
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
* 名称 : Test()
* 功能 : 显示子函数
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Test()
{  
//	write_com(0x03);
//	delay_ms(5);    
//	write_com(0x81);
//	DispString(" 姜老板");
//	write_com(0x91);
//	DispString("姜老板niubi");
//	write_com(0x89);
//	DispString("          ");
//	write_com(0x98);
//	DispString("  343   ");
}

void Lcd_12864_Init()
{
		PSB = 0;	 //选择串行方式
		delay_us(100);
		lcdinit();
		delay_us(100);
}

/*
*****************************************************************************
** 函 数 名 ：void Lcd12232_MoveToXY(uint8 x, uint8 y)  
** 功    能 ：将光标移到指点位置 
** 说    明 ：第一行地址为80H~87H 第二行地址90H~97H
** 入口参数 ：
** 返 回 值 ：无
** 说明     ：
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



