#include "sys.h"
#include "stdio.h"
#include "delay.h"
#include "tim_6_time.h"

#ifndef __HC_05
#define __HC_05

void hc_05_init(void);
void hc_05_left_send(void);
void hc_05_right_send(void);
void hc_05_send(void);
void hc_05_int_init(void);
int sort(int *num,int n);
#endif

