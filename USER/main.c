#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "step.h"
#include "wave.h"

int main(void)
{
    delay_init();	    	 //延时函数初始化
    uart_init(115200);	 //串口初始化为115200
    TIM2_Int_Init(12,10);
	TIM6_Int_Init(999,71);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);

    while(1)
    {  speed_up(1,160000);
	   step_wait();
	   speed_down(1,160000);
	}
}

