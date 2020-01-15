#ifndef __relay_H
#define __relay_H	 
#include "sys.h"

extern float CurrentSetting;
extern float VolageSetting;

void RelayInit();
void RelayWork(float tem);

#endif