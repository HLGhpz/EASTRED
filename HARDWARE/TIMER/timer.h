#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "stm32f10x_tim.h"
void TIM2_Int_Init(u16 arr,u16 psc);
typedef struct {
    int step;      //��ǰ����
    int target;    //Ŀ�경��
    int div;       //Ƶ��
} StepMotor;
extern StepMotor motor[4];
//�����ⲿ������ȫ�ֱ���ͨ����.h�ļ��ж���extern�ⲿ����������������.c�ļ��е��ã��ı�StepMotor motor[2]��ֵ
void MOTOR_IRQHandler(void);//���岽������ж�
void Motor_0(u32 timer);
void Motor_1(u32 timer);
void Motor_2(u32 timer);
void Motor_3(u32 timer);
void SetpMotor_SetStep(int id, int steps);      //���Ʋ���
void SetpMotor_SetSpeed(int id, int speed);     //�����ٶ�
void STEP_IO(void);
#endif

