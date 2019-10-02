#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "step.h"
#include "wave.h"
#include "infrared_INIT.h"

int main(void)
{
    delay_init();	    	 //延时函数初始化
	infrared_INIT();         //红外端口初始化
    uart_init(115200);	     //串口初始化为115200
    TIM2_Int_Init(12,10);    //TIM2初始化
	TIM6_Int_Init(999,71);   //TIM6初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级

    while(1)
    {  
		GO(1);
		GO(0);
	}
}

