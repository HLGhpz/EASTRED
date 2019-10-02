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
    GPIO_InitTypeDef GPIO_InitStructure;//端口结构体

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//TRIG C.1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//ECHO C.2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//下拉输入
    GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//TRIG D.0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//ECHO D.1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//下拉输入
    GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4;//TRIG E.1 .3 .4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_6;//ECHO E.0 .5 .6
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//下拉输入
    GPIO_Init(GPIOE,&GPIO_InitStructure);


}

//发送超声波
void hc_05_left_send(void)
{
	printf("hc_05_left_send\r\n");
    //ECHO拉高后 延时20us
    PDout(0)=1;
    delay_us(20);
    PDout(0)=0;
}

void hc_05_right_send(void)
{
    //ECHO拉高后 延时20us
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

//超声波中断初始化
void hc_05_int_init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    //中断结构体
    NVIC_InitTypeDef NVIC_InitStructure;
    //优先级结构体

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能复用功能时钟

	//E.0
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource0);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升沿和下升沿都触发
    EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
	//D.1
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource1);
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升沿和下升沿都触发
    EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
	//C.2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升沿和下升沿都触发
    EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
	//E.5
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource5);
    EXTI_InitStructure.EXTI_Line = EXTI_Line5;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升沿和下升沿都触发
    EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
	//E.6
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource6);
    EXTI_InitStructure.EXTI_Line = EXTI_Line6;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//上升沿和下升沿都触发
    EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);   //使能外部中断通道
	
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);   //使能外部中断通道

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);   //使能外部中断通道
	
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);   //使能外部中断通道
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
	if(EXTI_GetITStatus(EXTI_Line1) == SET)//左侧
    {
		EXTI_ClearITPendingBit(EXTI_Line1);
        if(PDin(1)==1 && flag_line5 == 0)
            //上升沿开始计时
        {
			flag_line5 = 1;
            time[0] = NOW;
        }
        else if(PDin(1)==0 && flag_line5 == 1)
            //下降沿结束计时
        {
			flag_line5 = 0;
            if(NOW-time[0]<0.005)
                //当距离小于170cm
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
//	if(EXTI_GetITStatus(EXTI_Line5) == SET)//左侧
//    {
//		EXTI_ClearITPendingBit(EXTI_Line5);
//        if(PAin(5)==1 && flag_line5 == 0)
//            //上升沿开始计时
//        {
//			flag_line5 = 1;
//            time[0] = NOW;
//        }
//        else if(PAin(5)==0 && flag_line5 == 1)
//            //下降沿结束计时
//        {
//			flag_line5 = 0;
//            if(NOW-time[0]<0.005)
//                //当距离小于170cm
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

//    if(EXTI_GetITStatus(EXTI_Line6) == SET)//右侧
//    {
//		EXTI_ClearITPendingBit(EXTI_Line6);
//        if(PAin(6) == 1 && flag_line6 == 0)
//            //上升沿开始计时
//        {
//			flag_line6 = 1;
//            time[1] = NOW;
//        }
//        else if(PAin(6) ==0 && flag_line6 ==1)
//            //下降沿结束计时
//        {
//			flag_line6 = 0;
//            if(NOW-time[1]<0.005)
//                //当距离小于170cm
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



	

