#ifndef __TIME_6_TIME
#define __TIME_6_TIME
#include "sys.h"

extern int tim6;
void tim_6_time_Init(u16 arr,u16 psc);
#define NOW  (tim6*0.01+TIM6->CNT/100000.)

#endif
