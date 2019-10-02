#include "timer.h"
#include "sys.h"
#include "stdio.h"

StepMotor motor[4];
int timer=0;
void STEP_IO(void)//ʹ�ܲ������IO��
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PB,PE�˿�ʱ��

    //��������˿�
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5;		//PA.0 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.0
    GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5);			//�����

    //���÷���˿�
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;			//LED0-->PB.5 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
	GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);			//�����
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_5);			//�����

}

void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM2�ж�,��������ж�

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
    TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����

    STEP_IO();//ʹ�ܲ������IO��
}

void SetpMotor_SetStep(int id, s32 steps)//���Ʋ���
{
    motor[id].step = 0;
	motor[id].target = 0;
    motor[id].target=motor[id].step+steps*2;
}

void SetpMotor_SetSpeed(int id, int speed)//�����ٶ�
{
    motor[id].div=speed;//ÿ��divһ��ʱ�䣬ִ������һ��
}

void TIM2_IRQHandler(void)//�жϷ�������ÿ��һ��ʱ�����һ�κ���
{
	printf("TIM2_IRQHandler\r\n");
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)       //�ж�ʹ��
    {
       timer++;
	   MOTOR_IRQHandler();        
    }
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}

void MOTOR_IRQHandler(void)//��������ж�
{
    Motor_0(timer);
    Motor_1(timer);
    Motor_2(timer);
    Motor_3(timer);
}

void Motor_0(u32 timer)
    //A0 B0
{
	if(motor[0].div!=0)
	{
		if(timer%motor[0].div==0)
		{
			if(motor[0].step<motor[0].target)
			{
				PBout(0)=0;
				PAout(0)=timer/motor[0].div&1;
				motor[0].step++;
			}
			else if(motor[0].step>motor[0].target)
			{
				PBout(0)=1;
				PAout(0)=timer/motor[0].div&1;
				motor[0].step--;
			}
		}
	}
    
}

void Motor_1(u32 timer)
{
    //A1 B1
	if(motor[1].div!=0)
	{
		if(timer%motor[1].div==0)
		{
			if(motor[1].step<motor[1].target)
			{
				PBout(1)=0;
				PAout(1)=timer/motor[1].div&1;
				motor[1].step++;
			}
			else if(motor[1].step>motor[1].target)
			{
				PBout(1)=1;
				PAout(1)=timer/motor[1].div&1;
				motor[1].step--;
			}
		}
	}
}

void Motor_2(u32 timer)
{
    //A4 B2
	if(motor[2].div!=0)
	{
		if(timer%motor[2].div==0)
		{
			if(motor[2].step<motor[2].target)
			{
				PBout(2)=0;
				PAout(4)=timer/motor[2].div&1;
				motor[2].step++;
			}
			else if(motor[2].step>motor[2].target)
			{
				PBout(2)=1;
				PAout(4)=timer/motor[2].div&1;
				motor[2].step--;
			}
		}
	}
}

void Motor_3(u32 timer)
{
    //A5 C5
	if(motor[3].div!=0)
	{
		if(timer%motor[3].div==0)
		{
			if(motor[3].step<motor[3].target)
			{
				PCout(5)=0;
				PAout(5)=timer/motor[3].div&1;
				motor[3].step++;
			}
			else if(motor[3].step>motor[3].target)
			{
				PCout(5)=1;
				PAout(5)=timer/motor[3].div&1;
				motor[3].step--;
			}
		}
	}
}

