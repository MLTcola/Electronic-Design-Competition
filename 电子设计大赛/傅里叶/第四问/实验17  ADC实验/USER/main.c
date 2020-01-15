#include "sys.h"
#include "math.h"
/************************************************
 ALIENTEK ս��STM32F103������ʵ��17
 ADC ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

u16 dat[] = 
{110,111,112,113,114,115,117,118,119,120,121,122,123,124,125,126,127,129,130,131,132,133,134,135,136,137,138,140,141,142,143,144,145,146,147,148,149,150,152,153,154,155,156,157,158,159,160,161,162,164,165,166,167,168,169,170,171,172,173,175,176,177,178,179,180,181,182,183,184,185,187,188,189,190,191,192,193,194,195,196,198,199,200,201,202,203,204,205,206,207,208,210,211,212,213,214,215,216,217,218,219,220,222,223,224,225,226,227,228,229,230,231,233,234,235,236,237,238,239,240,241,242,243,245,246,247,248,249,110,111,112,113,114,115,117,118,119,120,121,122,123,124,125,126,127,129,130,131,132,133,134,135,136,137,138,140,141,142,143,144,145,146,147,148,149,150,152,153,154,155,156,157,158,159,160,161,162,164,165,166,167,168,169,170,171,172,173,175,176,177,178,179,180,181,182,183,184,185,187,188,189,190,191,192,193,194,195,196,198,199,200,201,202,203,204,205,206,207,208,210,211,212,213,214,215,216,217,218,219,220,222,223,224,225,226,227,228,229,230,231,233,234,235,236,237,238,239,240,241,242,243,245,246,247,248,249,110,111,112,113,114,115,117,118,119,120,121,122,123,124,125,126,127,129,130,131,132,133,134,135,136,137,138,140,141,142,143,144,145,146,147,148,149,150,152,153,154,155,156,157,158,159,160,161,162,164,165,166,167,168,169,170,171,172,173,175,176,177,178,179,180,181,182,183,184,185,187,188,189,190,191,192,193,194,195,196,198,199,200,201,202,203,204,205,206,207,208,210,211,212,213,214,215,216,217,218,219,220,222,223,224,225,226,227,228,229,230,231,233,234,235,236,237,238,239,240,241,242,243,245,246,247,248,249,110,111,112,113,114,115,117,118,119,120,121,122,123,124,125,126,127,129,130,131,132,133,134,135,136,137,138,140,141,142,143,144,145,146,147,148,149,150,152,153,154,155,156,157,158,159,160,161,162,164,165,166,167,168,169,170,171,172,173,175,176,177,178,179,180,181,182,183,184,185,187,188,189,190,191,192,193,194,195,196,198,199,200,201,202,203,204,205,206,207,208,210,211,212,213,214,215,216,217,218,219,220,222,223,224,225,226,227,228,229,230,231,233,234,235,236,237,238,239,240,241,242,243,245,246,247,248,249,};
u16 H_FunDat[ADC_SIZE];
u16 H_SpeDat[ADC_SIZE];
 signed short lX,lY;
 float X,Y,Mag;
 float zhong;
 unsigned short i;
mycomplex DAT[ADC_SIZE] = {0};	
 void DrawUI(void);
 void test(void);
	
 int main(void)
 {	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	 
	KEY_Init();						//������ʼ��
 	LED_Init();			     	//LED�˿ڳ�ʼ��
	LCD_Init();			 	
 	Adc_Init();		  			//ADC��ʼ��
	TIM3_Int_Init(35,999);//72��Ƶ��1MHz/30=33kHz
	//TIM4_Int_Init(29999,7199);//7200��Ƶ��10kHz/10000=1Hz
	 
	//POINT_COLOR=RED;//��������Ϊ��ɫ 
	
	LCD_Fill(0,200,480,800,BLACK);				//����
	 POINT_COLOR=RED;
	 LCD_ShowString(0,20,200,16,16,"JP");	
	 LCD_ShowString(0,40,200,16,16,"ERJIE");	
	 LCD_ShowString(0,60,200,16,16,"SANJIE");	
	 LCD_ShowString(0,80,200,16,16,"SIJIE");	
	 LCD_ShowString(0,100,200,16,16,"WUJIE");	
	 
	while(1)
	{
		test();
	}
 }
 
void test(void)
{int min,j;
	LCD_ShowxNum(0,0,KEY_Scan(1),4,16,0);//��������

	if(KEY_Scan(1))LED0 = 0;						 //LED����
	else LED0 = 1;
	if(KEY_Scan(1))
	{
		TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx
	}		//ADC
	if(ADC_Flag==1)
	{
		ADC_Flag = 0;
		//LCD_Clear(DARKBLUE);
		LCD_DrawFunction(0,300,H_FunDat,480,200,BLACK);	//����
		//LCD_DrawSpectrum(0,550,H_SpeDat,480,200,BLACK);	//����
		LCD_DrawFunction(0,550,H_SpeDat,480,200,BLACK);	//����
		
		LCD_DrawGrid		(0,550,480,12,200,8,GRAY);	//��������
		LCD_DrawGrid		(0,300,480,12,200,8,GRAY);	//��������
		
		for(i=0; i<512; i++)
		{
			dat[i] = ADC_DAT_u32[i].real;
			H_FunDat[i] = dat[i]; 
			printf("Fun=%d\n",H_FunDat[i]);
		} 
		LCD_DrawFunction(0,300,H_FunDat,480,200,YELLOW);	//���ƺ���
		
		LCD_DrawGrid		(0,300,480,12,200,8,GRAY);	//��������
		
		fft(512,ADC_DAT_u32); 
		  
		for(i=0; i<512; i++)
		{
			dat[i] = (u16)(ADC_DAT_u32[i].real+50000)/30;
			H_SpeDat[i] = dat[i];
		}	
			for(i=0; i<512/2; i++){
			 lX  = ADC_DAT_u32[i].real;
        lY  = ADC_DAT_u32[i].imag;
        X = 512 * ((float)lX) / 32768;
        Y = 512 * ((float)lY) / 32768;
        Mag = sqrt(X * X + Y * Y) / 512;
        if(i == 0)
            dat[i] = (unsigned long)(Mag * 32768);
        else
            dat[i] = (unsigned long)(Mag * 65536);
			printf("Spe=%f,%d\n",ADC_DAT_u32[i].real,H_SpeDat[i]);
			printf("zhi=%d\n",dat[i]);
			}
			
		for(i=5;i<512/2;i++)
		{
			
			if(H_SpeDat[i-5]>H_SpeDat[i]&&H_SpeDat[i-4]>H_SpeDat[i]
				&&H_SpeDat[i-3]>H_SpeDat[i]&&H_SpeDat[i-2]>H_SpeDat[i]
				&&H_SpeDat[i]<H_SpeDat[i+2]&&H_SpeDat[i-1]>H_SpeDat[i]
			&&H_SpeDat[i]<H_SpeDat[i+1]&&H_SpeDat[i]<H_SpeDat[i+3]
			&&H_SpeDat[i]<H_SpeDat[i+4]&&H_SpeDat[i]<H_SpeDat[i+5])
			{
			j=i;
				break;
			}
			
		}
		POINT_COLOR=BLUE;
		LCD_ShowxNum(200,20,(float)j*3.9,4,16,0);
		zhong=(float)ADC_DAT_u32[j].real*1.414/120;
		
		if(zhong<0){

zhong=-zhong;}
		LCD_ShowxNum(300,20,zhong,16,16,0);
		delay_ms(300);
		for(i=j+1;i<512/2;i++)
		{
			
			if(H_SpeDat[i-5]>H_SpeDat[i]&&H_SpeDat[i-4]>H_SpeDat[i]
				&&H_SpeDat[i-3]>H_SpeDat[i]&&H_SpeDat[i-2]>H_SpeDat[i]
				&&H_SpeDat[i]<H_SpeDat[i+2]&&H_SpeDat[i-1]>H_SpeDat[i]
			&&H_SpeDat[i]<H_SpeDat[i+1]&&H_SpeDat[i]<H_SpeDat[i+3]
			&&H_SpeDat[i]<H_SpeDat[i+4]&&H_SpeDat[i]<H_SpeDat[i+5])
			{
			j=i;
				break;
			}
			
		}
		POINT_COLOR=BLUE;
		LCD_ShowxNum(200,40,(float)j*3.9,4,16,0);
		zhong=(float)ADC_DAT_u32[j].real*1.414/120;
		if(zhong<0){

zhong=-zhong;}
		LCD_ShowxNum(300,40,zhong,16,16,0);
		delay_ms(300);
		
		for(i=j+1;i<512/2;i++)
		{
			
			if(H_SpeDat[i-5]>H_SpeDat[i]&&H_SpeDat[i-4]>H_SpeDat[i]
				&&H_SpeDat[i-3]>H_SpeDat[i]&&H_SpeDat[i-2]>H_SpeDat[i]
				&&H_SpeDat[i]<H_SpeDat[i+2]&&H_SpeDat[i-1]>H_SpeDat[i]
			&&H_SpeDat[i]<H_SpeDat[i+1]&&H_SpeDat[i]<H_SpeDat[i+3]
			&&H_SpeDat[i]<H_SpeDat[i+4]&&H_SpeDat[i]<H_SpeDat[i+5])
			{
			j=i;
				break;
			}
			
		}
		POINT_COLOR=BLUE;
		LCD_ShowxNum(200,60,(float)j*3.9,4,16,0);
		zhong=(float)ADC_DAT_u32[j].real*1.414/120;
		if(zhong<0){

zhong=-zhong;}
		LCD_ShowxNum(300,60,zhong,16,16,0);
		delay_ms(300);
		
		for(i=j+1;i<512/2;i++)
		{
			
			if(H_SpeDat[i-5]>H_SpeDat[i]&&H_SpeDat[i-4]>H_SpeDat[i]
				&&H_SpeDat[i-3]>H_SpeDat[i]&&H_SpeDat[i-2]>H_SpeDat[i]
				&&H_SpeDat[i]<H_SpeDat[i+2]&&H_SpeDat[i-1]>H_SpeDat[i]
			&&H_SpeDat[i]<H_SpeDat[i+1]&&H_SpeDat[i]<H_SpeDat[i+3]
			&&H_SpeDat[i]<H_SpeDat[i+4]&&H_SpeDat[i]<H_SpeDat[i+5])
			{
			j=i;
				break;
			}
			
		}
		POINT_COLOR=BLUE;
		LCD_ShowxNum(200,80,(float)j*3.9,4,16,0);
		zhong=(float)ADC_DAT_u32[j].real*1.414/120;
		if(zhong<0){

zhong=-zhong;}
		LCD_ShowxNum(300,80,zhong,16,16,0);
		delay_ms(300);
		
		for(i=j+1;i<512/2;i++)
		{
			
			if(H_SpeDat[i-5]>H_SpeDat[i]&&H_SpeDat[i-4]>H_SpeDat[i]
				&&H_SpeDat[i-3]>H_SpeDat[i]&&H_SpeDat[i-2]>H_SpeDat[i]
				&&H_SpeDat[i]<H_SpeDat[i+2]&&H_SpeDat[i-1]>H_SpeDat[i]
			&&H_SpeDat[i]<H_SpeDat[i+1]&&H_SpeDat[i]<H_SpeDat[i+3]
			&&H_SpeDat[i]<H_SpeDat[i+4]&&H_SpeDat[i]<H_SpeDat[i+5])
			{
			j=i;
				break;
			}
			
		}
		
if(zhong<0){

zhong=-zhong;}
		POINT_COLOR=BLUE;
		LCD_ShowxNum(200,100,(float)j*3.9,4,16,0);
		zhong=(float)ADC_DAT_u32[j].real*1.414/120;
		
		LCD_ShowxNum(300,100,zhong,16,16,0);
		delay_ms(300);
		
//		zhong=ADC_DAT_u32[j*2].real*1.414/120;
//			LCD_ShowxNum(200,40,(float)2*j*3.9,4,16,0);
//		
//		if(zhong<0){
//		
//		zhong=-zhong;}
//		
//		LCD_ShowxNum(300,20,zhong,4,16,0);
//		zhong=ADC_DAT_u32[j*3].real*1.414/120;
//			LCD_ShowxNum(200,60,(float)3*j*3.9,4,16,0);
//		
//		if(zhong<0){
//		
//		zhong=-zhong;}
//		LCD_ShowxNum(300,20,zhong,4,16,0);
//		zhong=ADC_DAT_u32[j*4].real*1.414/120;
//			LCD_ShowxNum(200,60,(float)4*j*3.9,4,16,0);
//			if(zhong<0){
//		
//		zhong=-zhong;}
//		LCD_ShowxNum(300,20,zhong,4,16,0);
//		LCD_ShowxNum(300,60,ADC_DAT_u32[5*j].real/120,4,16,0);
//		zhong=ADC_DAT_u32[j*5].real*1.414/120;
//		if(zhong<0){
//		
//		zhong=-zhong;}
//		LCD_ShowxNum(300,20,zhong,4,16,0);
		//LCD_ShowxNum(300,60,ADC_DAT_u32[3*j].real/120,4,16,0);
		
//			LCD_ShowxNum(200,80,(float)4*j*3.9,4,16,0);
//		LCD_ShowxNum(300,80,ADC_DAT_u32[4*j].real/120,4,16,0);
//			LCD_ShowxNum(200,100,(float)5*j*3.9,4,16,0);
//		LCD_ShowxNum(300,100,ADC_DAT_u32[5*j].real/120,4,16,0);
		//LCD_DrawSpectrum(0,550,H_SpeDat,480,200,YELLOW);	//����Ƶ��
		LCD_DrawFunction(0,550,H_SpeDat,480,200,YELLOW);	//����Ƶ��
		LCD_DrawGrid		(0,550,480,12,200,8,GRAY);	//��������
		//LCD_ShowString(60,150,200,16,16,"ADC_CH0_VOL:0.000V");
		//LCD_ShowxNum(156,150,H_SpeDat[i],1,16,0);
		//TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx
	}
}
