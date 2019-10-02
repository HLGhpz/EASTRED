#include "timer.h"
#include "sys.h"
#include "stdio.h"

StepMotor motor[4];
int timer=0;
void STEP_IO(void)//使能步进电机IO口
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PE端口时钟

    //设置输出端口
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5;		//PA.0 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.0
    GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5);			//输出低

    //设置方向端口
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;			//LED0-->PB.5 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);			//输出低
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5;				 //LED0-->PB.5 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_5);			//输出低

}

void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
    TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM2中断,允许更新中断

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设

    STEP_IO();//使能步进电机IO口
}

void SetpMotor_SetStep(int id, s32 steps)//控制步数
{
    motor[id].step = 0;
	motor[id].target = 0;
    motor[id].target=motor[id].step+steps*2;
}

void SetpMotor_SetSpeed(int id, int speed)//控制速度
{
    motor[id].div=speed;//每隔div一段时间，执行内容一次
}

void TIM2_IRQHandler(void)//中断服务函数，每隔一段时间进入一次函数
{
	printf("TIM2_IRQHandler\r\n");
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)       //判断使能
    {
       timer++;
	   MOTOR_IRQHandler();        
    }
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}

void MOTOR_IRQHandler(void)//步进电机中断
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

