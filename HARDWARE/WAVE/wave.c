#include "wave.h"
#include "usart.h"
#include "sys.h"
#include "delay.h"
int flag;
/*
					R				T
	Front    		PE.0			PE.1
	Left			PD.1			PD.0
	Right			PC.2			PC.1
	Left_Back		PE.5			PE3
	Right_Front		PE.6			PE.4
 */

void Trig_Send(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟

    //PE.1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOE,GPIO_Pin_1);

    //PD.0
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOD,GPIO_Pin_0);

    //PC.1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOC,GPIO_Pin_1);

    //PE.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOE,GPIO_Pin_3);

    //PE.4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOE,GPIO_Pin_4);

}
void EXTIX_Init(void)     //PE.0作为检测端
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;  //结构体声明

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC,ENABLE);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PE0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;            //下拉输入
    GPIO_Init(GPIOE, &GPIO_InitStructure);                   //前侧超声波

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PD1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOD, &GPIO_InitStructure);                   //左侧超声波

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//PC2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOC, &GPIO_InitStructure);                   //右侧超声波

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PE5
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOE, &GPIO_InitStructure);                   //左后侧超声波

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;//PE6
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOE, &GPIO_InitStructure);                   //右后侧超声波
    //初始化I/O口

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    //外部时钟必须使能
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource0);
    //中断映射端口
    //PE.0
    EXTI_InitStructure.EXTI_Line=EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	 //事件OR中断（中断）
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  //上升沿中断
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    //PD.1
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource1);
    EXTI_InitStructure.EXTI_Line=EXTI_Line1;
    EXTI_Init(&EXTI_InitStructure);

    //PC.2
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
    EXTI_InitStructure.EXTI_Line=EXTI_Line2;
    EXTI_Init(&EXTI_InitStructure);

    //PE.5
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource5);
    EXTI_InitStructure.EXTI_Line=EXTI_Line5;
    EXTI_Init(&EXTI_InitStructure);

    //PE.6
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource6);
    EXTI_InitStructure.EXTI_Line=EXTI_Line6;
    EXTI_Init(&EXTI_InitStructure);


    //初始化外部中断

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//子优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //优先级设置为0，0	         PE.0

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//子优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //优先级设置为0，1

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//子优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);
}

u32 Now_tim=0;
float Front_dist;
float  Front_tim=0;
//float a[5]={0};
//int i=0;
//前侧超声波PE.0
//外部中断函数
void EXTI0_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line0)==SET)
    {
        if(PEin(0)==0)    // 捕获到下降沿
        {
            Front_tim=Now_tim+(TIM6->CNT/1000.0)-Front_tim;
            Front_dist=Front_tim*170;


        }
        else   //捕获到上升沿
        {
            Front_tim=Now_tim+(TIM6->CNT/1000.0);

        }
        EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位
    }
}


float Left_dist=0;
float  Left_tim=0;
//左侧超声波PD.1

//PD.1   Left
void EXTI1_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line1)==SET)
    {
        if(PDin(1)==0)    //  捕获到下降沿
        {
            Left_tim=Now_tim+(TIM6->CNT/1000.0)-Left_tim;
            Left_dist=Left_tim*170;

        }
        else   //捕获到上升沿
        {
            Left_tim=Now_tim+(TIM6->CNT/1000.0);

        }
        EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE0上的中断标志位
    }
}




float Right_dist;
float Right_tim=0;
//右侧超声波PC.2
//PC.2  Right
void EXTI2_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line2)==SET)
    {
        if(PCin(2)==0)    //  捕获到下降沿
        {
            Right_tim=Now_tim+(TIM6->CNT/1000.0)-Right_tim;
            Right_dist=Right_tim*170;

        }
        else   //捕获到上升沿
        {
            Right_tim=Now_tim+(TIM6->CNT/1000.0);

        }
        EXTI_ClearITPendingBit(EXTI_Line2); //清除LINE0上的中断标志位
    }
}



float BackLeft_dist;
float  BackLeft_tim=0;
float BackRight_dist;
float  BackRight_tim=0;

void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line5)==SET)
    {
        if(PEin(5)==0)    // 捕获到下降沿
        {
            BackLeft_tim=Now_tim+(TIM6->CNT/1000.0)-BackLeft_tim;
            BackLeft_dist=BackLeft_tim*170;


        }
        else   //捕获到上升沿
        {
            BackLeft_tim=Now_tim+(TIM6->CNT/1000.0);

        }
        EXTI_ClearITPendingBit(EXTI_Line5); //清除LINE0上的中断标志位
    }


    else if(EXTI_GetITStatus(EXTI_Line6)==SET)
    {
        if(PEin(6)==0)    // 捕获到下降沿
        {
            BackRight_tim=Now_tim+(TIM6->CNT/1000.0)-BackRight_tim;
            BackRight_dist=BackRight_tim*170;
        }
        else   //捕获到上升沿
        {
            BackRight_tim=Now_tim+(TIM6->CNT/1000.0);
        }
        EXTI_ClearITPendingBit(EXTI_Line6); //清除LINE0上的中断标志位
    }
}
void TIM6_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    //时钟使能

    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler =psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
//定时器初始化

    TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE );
    //允许更新中断

    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //中断优先级

    TIM_Cmd(TIM6, ENABLE);  //使能TIMx外设


    EXTIX_Init();
    Trig_Send();
}
//定时器2中断服务程序
void TIM6_IRQHandler(void)   //TIM2中断
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
    {
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update); //清除中断标志位
        Now_tim++;
    }
}





void UWaveCenter_Send(void) {
    PEout(1)=1;
    delay_us(20);
    PEout(1)=0;
}


void UWaveLeft_Send(void) { //发射超声波
    PDout(0)=1;
    delay_us(20);         //固定20us
    PDout(0)=0;
}


void UWaveRight_Send(void) {
    PCout(1)=1;
    delay_us(20);
    PCout(1)=0;
}

void UWaveBackLeft_Send(void) {
    PEout(3)=1;
    delay_us(20);
    PEout(3)=0;
}

void UWaveBackRight_Send(void) {
    PEout(4)=1;
    delay_us(20);
    PEout(4)=0;
}

float SortAndCal(float *num,int n) //滤波
{
    int i = 0;
    int min = i,max=i;
    float tmp = 0;
    for(i = 0; i < n; i++)
    {   if(num[min]>num[i])
            min=i;
        if(num[max]<num[i])
            max=i;
    }
    for(i=0; i<n; i++) tmp+=num[i];
    return (tmp-num[min]-num[max])/(n-2);
}

