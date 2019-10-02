#ifndef __STEP_H
#define __STEP_H
#include "sys.h"
void speed_up(int ia,s32 step);
void part_speed_up(int CONT,int ia,s32 step);
void speed_down(int ia,int step);
void part_down(int CONT,int ia,s32 step);
void step_wait(void);
#endif

