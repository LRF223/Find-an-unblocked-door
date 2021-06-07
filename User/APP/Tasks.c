#include "Usart.h"
#include "Key.h" 
#include "Timer.h"

/******************************************************************************
函数原型：	void Nvic_Init(void)
功    能：	NVIC初始化
*******************************************************************************/ 
void Nvic_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//NVIC_PriorityGroup 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//优先级分组
	//Timer3
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//先占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//从占优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/******************************************************************************
函数原型：	void BSP_Int(void)
功    能：	硬件驱动初始化
*******************************************************************************/ 
void BSP_Init(void)
{
	RCC_Configuration(); 														//时钟设置
	Timer3_Init(10000 - 1);										 			//设置自动装载值10000,预分频系数7200,时钟频率=72 000 000/(10000)*(72 00) = 1HZ (1s)
	Nvic_Init();																		//中断优先级初始化		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2,2位抢占优先级,2位响应优先级
	USART1_Init(115200); 														//串口初始化为115200
	USART2_Init(115200); 														//串口初始化（参数是波特率）
	Key_GPIO_Config();
	USART1_printf("\r\n Bsp Init Finish"); 	
}

