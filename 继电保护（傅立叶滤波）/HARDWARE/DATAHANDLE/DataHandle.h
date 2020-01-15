#ifndef __DataHandle_H
#define __DataHandle_H	 
#include "sys.h"

#define APV 0
#define BPV 1
#define CPV 2
#define APC 3
#define BPC 4
#define CPC 5

extern long APhaseCurrentMax, APhaseCurrentAngle,BPhaseCurrentMax,BPhaseCurrentAngle,CPhaseCurrentMax,CPhaseCurrentAngle,APhaseVoltageMax, APhaseVoltageAngle,BPhaseVoltageMax, BPhaseVoltageAngle,CPhaseVoltageMax, CPhaseVoltageAngle;
	

extern u16 sample[20];


void AdcFourier(u8 collect);
float NegativeSequence(float MAG1,float phase1,float MAG2,float phase2,float MAG3,float phase3);
#endif

