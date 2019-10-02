#ifndef __WAVE
#define __WAVE
#include "sys.h"

void UWaveBackRight_Send(void);
void UWaveBackLeft_Send(void);
void UWaveRight_Send(void);
void UWaveLeft_Send(void);
void UWaveCenter_Send(void);
float SortAndCal(float *num,int n);
void Trig_Send(void);
void EXTIX_Init(void);
void TIM6_Int_Init(u16 arr,u16 psc);
#endif


