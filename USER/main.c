#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "step.h"
#include "hc_05.h"

int main(void)
{
    delay_init();	    	 //��ʱ������ʼ��
    uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
    TIM2_Int_Init(12,10);
	//tim_6_time_Init(999,719);
	//hc_05_int_init();
	//hc_05_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    while(1)
    {   
//		hc_05_left_send();
//		delay_ms(1000);
		
//		part_speed_up(239,2,16000);//45��
//		step_wait();
//		part_down(239,2,16000);
//        speed_up(2,16000);//25��
//        step_wait();
//        speed_down(2,16000);
//        speed_up(1,16000);
//        step_wait();
//        speed_down(1,16000);
//		speed_up(0,16000);
//        step_wait();
//		speed_down(0,3600);
//		speed_up(3,16000);
//        step_wait();
//		speed_down(3,3600);
    }
}

