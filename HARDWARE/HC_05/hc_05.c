#include "hc_05.h"
#include "delay.h"

/*
					T				R
	Front    		PE.1			PE.0
	Left			PD.0			PD.1
	Right			PC.1			PC.2
	Left_Back		PE.3			PE.5
	Right_Front		PE.4			PE.6
 */
 
extern int tim6;

float time[2];
int dist[2];
int left_dist;

void hc_05_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;//�˿ڽṹ��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//TRIG C.1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//ECHO C.2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������
    GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//TRIG D.0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//ECHO D.1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������
    GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4;//TRIG E.1 .3 .4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_6;//ECHO E.0 .5 .6
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������
    GPIO_Init(GPIOE,&GPIO_InitStructure);


}

//���ͳ�����
void hc_05_left_send(void)
{
	printf("hc_05_left_send\r\n");
    //ECHO���ߺ� ��ʱ20us
    PDout(0)=1;
    delay_us(20);
    PDout(0)=0;
}

void hc_05_right_send(void)
{
    //ECHO���ߺ� ��ʱ20us
    PAout(4)=1;
    delay_us(20);
    PAout(4)=0;
}
void hc_05_send(void)
{
	hc_05_right_send();
	delay_ms(5);
	hc_05_left_send();
	delay_ms(5);
}

//�������жϳ�ʼ��
void hc_05_int_init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    //�жϽṹ��
    NVIC_InitTypeDef NVIC_InitStructure;
    //���ȼ��ṹ��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ�ܸ��ù���ʱ��

	//E.0
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource0);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//�����غ������ض�����
    EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
	//D.1
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource1);
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//�����غ������ض�����
    EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
	//C.2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//�����غ������ض�����
    EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
	//E.5
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource5);
    EXTI_InitStructure.EXTI_Line = EXTI_Line5;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//�����غ������ض�����
    EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
	//E.6
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource6);
    EXTI_InitStructure.EXTI_Line = EXTI_Line6;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//�����غ������ض�����
    EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);   //ʹ���ⲿ�ж�ͨ��
	
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);   //ʹ���ⲿ�ж�ͨ��

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);   //ʹ���ⲿ�ж�ͨ��
	
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);   //ʹ���ⲿ�ж�ͨ��
}
int i = 0;
int j = 0;
int flag_line5 = 0;
int flag_line6 = 0;
int flag_5_6 = 5;

//LEFT
void EXTI1_IRQHandler(void)
{
	printf("EXTI1_IRQHandler\r\n");
	if(EXTI_GetITStatus(EXTI_Line1) == SET)//���
    {
		EXTI_ClearITPendingBit(EXTI_Line1);
        if(PDin(1)==1 && flag_line5 == 0)
            //�����ؿ�ʼ��ʱ
        {
			flag_line5 = 1;
            time[0] = NOW;
        }
        else if(PDin(1)==0 && flag_line5 == 1)
            //�½��ؽ�����ʱ
        {
			flag_line5 = 0;
            if(NOW-time[0]<0.005)
                //������С��170cm
            {
                dist[0] = (NOW-time[0])*17000*10;
            }
            else
            {
                dist[0] = 99999;
            }
            printf("dist[0] = %d\r\n",dist[0]);
        }
    }
}

//void EXTI9_5_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line5) == SET)//���
//    {
//		EXTI_ClearITPendingBit(EXTI_Line5);
//        if(PAin(5)==1 && flag_line5 == 0)
//            //�����ؿ�ʼ��ʱ
//        {
//			flag_line5 = 1;
//            time[0] = NOW;
//        }
//        else if(PAin(5)==0 && flag_line5 == 1)
//            //�½��ؽ�����ʱ
//        {
//			flag_line5 = 0;
//            if(NOW-time[0]<0.005)
//                //������С��170cm
//            {
//                dist[0] = (NOW-time[0])*17000*10;
//            }
//            else
//            {
//                dist[0] = 99999;
//            }
//            printf("dist[0] = %d\r\n",dist[0]);
//        }
//    }

//    if(EXTI_GetITStatus(EXTI_Line6) == SET)//�Ҳ�
//    {
//		EXTI_ClearITPendingBit(EXTI_Line6);
//        if(PAin(6) == 1 && flag_line6 == 0)
//            //�����ؿ�ʼ��ʱ
//        {
//			flag_line6 = 1;
//            time[1] = NOW;
//        }
//        else if(PAin(6) ==0 && flag_line6 ==1)
//            //�½��ؽ�����ʱ
//        {
//			flag_line6 = 0;
//            if(NOW-time[1]<0.005)
//                //������С��170cm
//            {
//                dist[1] = (NOW-time[1])*17000*10;
//                //				printf("dist[1] = %d\r\n",dist[1]);
//            }
//            else
//            {
//                dist[1] = 99999;
//                //				printf("dist[1] = %d\r\n",dist[1]);
//            }
//            printf("dist[1] = %d\r\n",dist[1]);
//        }
//    }
//}



	

