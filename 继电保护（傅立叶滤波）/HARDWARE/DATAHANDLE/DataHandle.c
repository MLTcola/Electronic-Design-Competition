#include "DataHandle.h"
#include "adc.h"
#include "delay.h"
#include "math.h"

//extern u16 sample[20];
static u8 N=20;//采样个数
static u8 n=1;//几次谐波
static float pi=3.1415926;//pai

float NegativeSequence(float MAG1,float phase1,float MAG2,float phase2,float MAG3,float phase3)
{
	 float x,y,z;
   x=MAG1*cos(phase1*3.1415/180)+ MAG2*cos(phase2*3.1415/180)+MAG3*cos(phase3*3.1415/180); 
	 y=MAG1*sin(phase1*3.1415/180)+ MAG2*sin(phase2*3.1415/180)+MAG3*sin(phase3*3.1415/180);
	 z=sqrt(x*x+y*y)/3;
	return z;
}


void AdcFourier(u8 collect)
{
	u8 i;
	long an=0;
	long bn=0;
	if(collect==0)
	{
		for(i=0;i<N;i++)
		{
			sample[i]=Get_Adc(collect);
			delay_ms(20/N);
		}
		
		for(i=0;i<N;i++)
		{
			an=an+sample[i]*sin(i*2*n*pi/N)/N;
		}
//		an=2*an;
		for(i=0;i<N;i++)
		{
			bn=bn+sample[i]*cos(i*2*n*pi/N)/N;
		}
//		bn=2*bn;
		APhaseVoltageMax=sqrt(an*an+bn*bn);
		APhaseVoltageAngle=atan(bn/an);
	}
	else if(collect==1)
	{
		for(i=0;i<N;i++)
		{
			sample[i]=Get_Adc(collect);
			delay_ms(20/N);
		}
		for(i=0;i<N;i++)
		{
			an=an+sample[i]*sin(i*2*n*pi/N)/N;
		}
		
		for(i=0;i<N;i++)
		{
			bn=bn+sample[i]*cos(i*2*n*pi/N)/N;
		}
		
		BPhaseVoltageMax=sqrt(an*an+bn*bn);
		BPhaseVoltageAngle=atan(bn/an);
	}
	if(collect==2)
	{
		for(i=0;i<N;i++)
		{
			sample[i]=Get_Adc(collect);
			delay_ms(20/N);
		}
		for(i=0;i<N;i++)
		{
			an=an+sample[i]*sin(i*2*n*pi/N)/N;
		}
		
		for(i=0;i<N;i++)
		{
			bn=bn+sample[i]*cos(i*2*n*pi/N)/N;
		}
		
		CPhaseVoltageMax=sqrt(an*an+bn*bn);
		CPhaseVoltageAngle=atan(bn/an);
	}
	
	if(collect==3)
	{
		for(i=0;i<N;i++)
		{
			sample[i]=Get_Adc(collect);
			delay_ms(20/N);
		}
		for(i=0;i<N;i++)
		{
			an=an+sample[i]*sin(i*2*n*pi/N)/N;
		}
		
		for(i=0;i<N;i++)
		{
			bn=bn+sample[i]*cos(i*2*n*pi/N)/N;
		}
		
		APhaseCurrentMax=sqrt(an*an+bn*bn);
		APhaseCurrentAngle=atan(bn/an);
	}
	
	if(collect==4)
	{
		for(i=0;i<N;i++)
		{
			sample[i]=Get_Adc(collect);
			delay_ms(20/N);
		}
		for(i=0;i<N;i++)
		{
			an=an+sample[i]*sin(i*2*n*pi/N)/N;
		}
		
		for(i=0;i<N;i++)
		{
			bn=bn+sample[i]*cos(i*2*n*pi/N)/N;
		}
		
		BPhaseCurrentMax=sqrt(an*an+bn*bn);
		BPhaseCurrentAngle=atan(bn/an);
	}
	
	if(collect==5)
	{
		for(i=0;i<N;i++)
		{
			sample[i]=Get_Adc(collect);
			delay_ms(20/N);
		}
		for(i=0;i<N;i++)
		{
			an=an+sample[i]*sin(i*2*n*pi/N)/N;
		}
		
		for(i=0;i<N;i++)
		{
			bn=bn+sample[i]*cos(i*2*n*pi/N)/N;
		}
		
		CPhaseCurrentMax=sqrt(an*an+bn*bn);
		CPhaseCurrentAngle=atan(bn/an);
	}
}






