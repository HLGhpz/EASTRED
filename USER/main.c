#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "step.h"
#include "wave.h"
#include "infrared_INIT.h"

int main(void)
{
    delay_init();	    	 //��ʱ������ʼ��
	infrared_INIT();         //����˿ڳ�ʼ��
    uart_init(115200);	     //���ڳ�ʼ��Ϊ115200
    TIM2_Int_Init(12,10);    //TIM2��ʼ��
	TIM6_Int_Init(999,71);   //TIM6��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

    while(1)
    {  
		GO(1);
		GO(0);
	}
}

