#include "tim_6_time.h"
#include "stdio.h"

int tim6 = 0;

void tim_6_time_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = arr;//设置预装载值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;//设置预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);//允许更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM6,ENABLE);//使能TIM6
}

void TIM6_IRQHandler(void)
{
	printf("TIM6_IRQHandler\r\n");
	if(TIM_GetITStatus(TIM6,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
		tim6++;
	}
}

