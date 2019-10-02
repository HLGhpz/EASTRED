#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "step.h"
#include "wave.h"

int main(void)
{
    delay_init();	    	 //��ʱ������ʼ��
    uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
    TIM2_Int_Init(12,10);
	TIM6_Int_Init(999,71);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
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

