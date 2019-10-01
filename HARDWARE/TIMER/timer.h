#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "stm32f10x_tim.h"
void TIM2_Int_Init(u16 arr,u16 psc);
typedef struct {
    int step;      //当前步数
    int target;    //目标步数
    int div;       //频率
} StepMotor;
extern StepMotor motor[4];
//定义外部变量，全局变量通过在.h文件中定义extern外部变量，可以在其他.c文件中调用，改变StepMotor motor[2]的值
void MOTOR_IRQHandler(void);//定义步进电机中断
void Motor_0(u32 timer);
void Motor_1(u32 timer);
void Motor_2(u32 timer);
void Motor_3(u32 timer);
void SetpMotor_SetStep(int id, int steps);      //控制步数
void SetpMotor_SetSpeed(int id, int speed);     //控制速度
void STEP_IO(void);
#endif

