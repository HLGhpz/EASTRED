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
    GPIO_InitTypeDef GPIO_InitStructure;//端口结构体

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//TRIG C.1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//ECHO C.2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//下拉输入
    GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//TRIG D.0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//ECHO D.1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//下拉输入
    GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4;//TRIG E.1 .3 .4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_6;//ECHO E.0 .5 .6
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//下拉输入
    GPIO_Init(GPIOE,&GPIO_InitStructure);

}
void EXTIX_Init(void)     //PE.0作为检测端
{
    EXTI_InitTypeDef EXTI_InitStructure;
    //中断结构体
    NVIC_InitTypeDef NVIC_InitStructure;
    //优先级结构体

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能复用功能时钟

	//E.0
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource0);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升沿和下升沿都触发
    EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
	//D.1
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource1);
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升沿和下升沿都触发
    EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
	//C.2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升沿和下升沿都触发
    EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
	//E.5
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource5);
    EXTI_InitStructure.EXTI_Line = EXTI_Line5;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升沿和下升沿都触发
    EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
	//E.6
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource6);
    EXTI_InitStructure.EXTI_Line = EXTI_Line6;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升沿和下升沿都触发
    EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);   //使能外部中断通道
	
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);   //使能外部中断通道

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);   //使能外部中断通道
	
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);   //使能外部中断通道
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

//定时器6中断服务程序
void TIM6_IRQHandler(void)   //TIM2中断
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
    {
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update); //清除中断标志位
        Now_tim++;
    }
}

