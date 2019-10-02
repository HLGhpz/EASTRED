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

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��

    //PE.1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
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
void EXTIX_Init(void)     //PE.0��Ϊ����
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;  //�ṹ������

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC,ENABLE);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PE0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;            //��������
    GPIO_Init(GPIOE, &GPIO_InitStructure);                   //ǰ�೬����

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PD1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOD, &GPIO_InitStructure);                   //��೬����

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//PC2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOC, &GPIO_InitStructure);                   //�Ҳ೬����

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PE5
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOE, &GPIO_InitStructure);                   //���೬����

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;//PE6
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOE, &GPIO_InitStructure);                   //�Һ�೬����
    //��ʼ��I/O��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    //�ⲿʱ�ӱ���ʹ��
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource0);
    //�ж�ӳ��˿�
    //PE.0
    EXTI_InitStructure.EXTI_Line=EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	 //�¼�OR�жϣ��жϣ�
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  //�������ж�
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


    //��ʼ���ⲿ�ж�

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//�����ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //���ȼ�����Ϊ0��0	         PE.0

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//�����ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //���ȼ�����Ϊ0��1

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//�����ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);
}

u32 Now_tim=0;
float Front_dist;
float  Front_tim=0;
//float a[5]={0};
//int i=0;
//ǰ�೬����PE.0
//�ⲿ�жϺ���
void EXTI0_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line0)==SET)
    {
        if(PEin(0)==0)    // �����½���
        {
            Front_tim=Now_tim+(TIM6->CNT/1000.0)-Front_tim;
            Front_dist=Front_tim*170;


        }
        else   //����������
        {
            Front_tim=Now_tim+(TIM6->CNT/1000.0);

        }
        EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ
    }
}


float Left_dist=0;
float  Left_tim=0;
//��೬����PD.1

//PD.1   Left
void EXTI1_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line1)==SET)
    {
        if(PDin(1)==0)    //  �����½���
        {
            Left_tim=Now_tim+(TIM6->CNT/1000.0)-Left_tim;
            Left_dist=Left_tim*170;

        }
        else   //����������
        {
            Left_tim=Now_tim+(TIM6->CNT/1000.0);

        }
        EXTI_ClearITPendingBit(EXTI_Line1); //���LINE0�ϵ��жϱ�־λ
    }
}




float Right_dist;
float Right_tim=0;
//�Ҳ೬����PC.2
//PC.2  Right
void EXTI2_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line2)==SET)
    {
        if(PCin(2)==0)    //  �����½���
        {
            Right_tim=Now_tim+(TIM6->CNT/1000.0)-Right_tim;
            Right_dist=Right_tim*170;

        }
        else   //����������
        {
            Right_tim=Now_tim+(TIM6->CNT/1000.0);

        }
        EXTI_ClearITPendingBit(EXTI_Line2); //���LINE0�ϵ��жϱ�־λ
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
        if(PEin(5)==0)    // �����½���
        {
            BackLeft_tim=Now_tim+(TIM6->CNT/1000.0)-BackLeft_tim;
            BackLeft_dist=BackLeft_tim*170;


        }
        else   //����������
        {
            BackLeft_tim=Now_tim+(TIM6->CNT/1000.0);

        }
        EXTI_ClearITPendingBit(EXTI_Line5); //���LINE0�ϵ��жϱ�־λ
    }


    else if(EXTI_GetITStatus(EXTI_Line6)==SET)
    {
        if(PEin(6)==0)    // �����½���
        {
            BackRight_tim=Now_tim+(TIM6->CNT/1000.0)-BackRight_tim;
            BackRight_dist=BackRight_tim*170;
        }
        else   //����������
        {
            BackRight_tim=Now_tim+(TIM6->CNT/1000.0);
        }
        EXTI_ClearITPendingBit(EXTI_Line6); //���LINE0�ϵ��жϱ�־λ
    }
}
void TIM6_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    //ʱ��ʹ��

    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler =psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
//��ʱ����ʼ��

    TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE );
    //��������ж�

    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //�ж����ȼ�

    TIM_Cmd(TIM6, ENABLE);  //ʹ��TIMx����


    EXTIX_Init();
    Trig_Send();
}
//��ʱ��2�жϷ������
void TIM6_IRQHandler(void)   //TIM2�ж�
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ
    {
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update); //����жϱ�־λ
        Now_tim++;
    }
}





void UWaveCenter_Send(void) {
    PEout(1)=1;
    delay_us(20);
    PEout(1)=0;
}


void UWaveLeft_Send(void) { //���䳬����
    PDout(0)=1;
    delay_us(20);         //�̶�20us
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

float SortAndCal(float *num,int n) //�˲�
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

