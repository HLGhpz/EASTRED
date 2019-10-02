#include "step.h"
#include "sys.h"
#include "timer.h"
#include "delay.h"
#include "stdio.h"
int value[]=
{

    1471,1389,1316,1316,1250,1190,1190,1136,1087,1042,
    1000,962,926,893,862,833,806,781,758,714,
    694,658,641,625,595,568,556,532,510,490,
    472,455,439,424,410,397,385,368,357,342,
    333,321,312,301,291,281,272,263,258,250,
    240,234,227,221,216,210,205,198,194,189,
    184,180,176,172,168,164,161,158,155,152,
    150,146,144,142,140,137,135,133,131,130,
    128,126,124,123,121,120,119,118,117,116,
    115,114,113,112,111,110,109,108,108,107,
    106,106,105,105,104,104,103,103,102,102,
    102,101,101,100,100,100,100,99,99,99,
    98,98,98,98,98,98,97,97,97,97,
    97,97,97,97,96,96,96,96,96,96,
    96,95,95,95,95,95,95,95,95,95,
    95,95,95,95,95,95,95,95,95,95,
    95,95,95,94,93,92,91,90,89,88,
    87,86,85,84,82,80,78,76,74,72,
    70,68,66,64,62,60,58,56,54,53,
    52,51,50,49,48,47,46,45,45,45,
    44,44,44,44,43,43,43,43,43,43,
    42,42,42,42,42,42,42,41,41,41,
    41,41,41,41,40,40,40,40,40,40,
    40,40,39,39,39,39,39,39,39,39,
    39,38,38,38,38,38,38,38,38,38,
    38,37,37,37,37,37,37,37,37,37,
    37,37,36,36,36,36,36,36,36,36,
    36,36,36,36,35,35,35,35,35,35,
    35,35,35,35,35,35,35,34,34,34,
    34,34,34,34,34,34,34,34,34,34,
    34,33,33,33,33,33,33,33,33,33,
    33,33,33,33,33,33,32,32,32,32,
    32,32,32,32,32,32,32,32,32,32,
    32,32,31,31,31,31,31,31,31,31,
    31,31,31,31,31,31,31,31,31,30,
    30,30,30,30,30,30,30,30,30,30,
    30,30,30,30,30,30,30,30,29,29,
    29,29,29,29,29,29,29,29,29,29,
    29,29,29,29,29,29,29,28,28,28,
    28,28,28,28,28,28,28,28,28,28,
    28,28,28,28,28,28,28,27,27,27,
    27,27,27,27,27,27,27,27,27,27,
    27,27,27,27,27,27,27,27,26,26,
    26,26,26,26,26,26,26,26,26,26,
    26,26,26,26,26,26,26,26,26,26,
    26,25,25,25,25,25,25,25,25,25,
    25,25,25,25,25,25,25,25,25,25
};

void speed_up(int ia,int step)//四个电机一起加速
{
    int Count=0;//加速标志数
    int Speed;
	
    switch(ia)//设定四个步进电机目标步数
    {
    case 0:
        //
        SetpMotor_SetStep(0,step);	//后退
        SetpMotor_SetStep(1,step);
        SetpMotor_SetStep(2,-step);
        SetpMotor_SetStep(3,-step);
        break;
    case 1:
        SetpMotor_SetStep(0,-step);	//前进
        SetpMotor_SetStep(1,-step);
        SetpMotor_SetStep(2,step);
        SetpMotor_SetStep(3,step);
        break;
    case 2:
        SetpMotor_SetStep(0,step);	//左移
        SetpMotor_SetStep(1,-step);
        SetpMotor_SetStep(2,step);
        SetpMotor_SetStep(3,-step);
        break;
    case 3:
        SetpMotor_SetStep(0,-step);	//右移
        SetpMotor_SetStep(1,step);
        SetpMotor_SetStep(2,-step);
        SetpMotor_SetStep(3,step);
        break;
    }


    for(Count = 0; Count<469; Count++)//每隔2ms重复设定速度值，越小越快
    {
        Speed=value[Count];
        delay_ms(2);
        SetpMotor_SetSpeed(0,Speed);
        SetpMotor_SetSpeed(1,Speed);
        SetpMotor_SetSpeed(2,Speed);
        SetpMotor_SetSpeed(3,Speed);
    }
}

void speed_down(int ia,int step)//四个电机一起加速
{
    int Count;//加速标志数
    int Speed;
    switch(ia)//设定四个步进电机目标步数
    {
    case 0:
        SetpMotor_SetStep(0,step);	//后退
        SetpMotor_SetStep(1,step);
        SetpMotor_SetStep(2,-step);
        SetpMotor_SetStep(3,-step);
        break;
    case 1:
        SetpMotor_SetStep(0,-step);	//前进
        SetpMotor_SetStep(1,-step);
        SetpMotor_SetStep(2,step);
        SetpMotor_SetStep(3,step);
        break;
    case 2:
        SetpMotor_SetStep(0,step);	//左移
        SetpMotor_SetStep(1,-step);
        SetpMotor_SetStep(2,step);
        SetpMotor_SetStep(3,-step);
        break;
    case 3:
        SetpMotor_SetStep(0,-step);	//右移
        SetpMotor_SetStep(1,step);
        SetpMotor_SetStep(2,-step);
        SetpMotor_SetStep(3,step);
        break;
    }
    for(Count = 469; Count>0; Count--)//每隔2ms重复设定速度值，越大越慢
    {
        Speed=value[Count];
        Speed=value[Count];
        Speed=value[Count];
        Speed=value[Count];
        delay_ms(1);
        SetpMotor_SetSpeed(0,Speed);
        SetpMotor_SetSpeed(1,Speed);
        SetpMotor_SetSpeed(2,Speed);
        SetpMotor_SetSpeed(3,Speed);
    }
}

void step_wait(void)
{   int wait=0;
    if(motor[0].target!=motor[0].step) 
        wait=1;
    while(wait)
    {
        if(motor[0].target==motor[0].step)
        {
            motor[0].step=motor[0].target=0;
            motor[1].step=motor[1].target=0;
            motor[2].step=motor[2].target=0;
            motor[3].step=motor[3].target=0;
            wait=0;
        }
    }

}

