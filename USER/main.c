#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "step.h"

 int main(void)
 {		
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
    TIM2_Int_Init(12,10);
    while(1)
    {
    speed_up(1,16000);
	step_wait();
    speed_down(1,160); 
    speed_up(0,16000);
	step_wait();
    speed_down(0,160);        
    }        
 }

