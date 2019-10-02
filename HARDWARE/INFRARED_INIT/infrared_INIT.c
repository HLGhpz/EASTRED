#include "infrared_INIT.h"
void infrared_INIT(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	 //使能PF端口时钟    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				 //PA.0 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOF, &GPIO_InitStructure);					 //根据设定参数初始化GPIOF
    GPIO_ResetBits(GPIOF,GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);						 //拉低PF口

}

