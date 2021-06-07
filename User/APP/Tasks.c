#include "Usart.h"
#include "Key.h" 
#include "Timer.h"

/******************************************************************************
����ԭ�ͣ�	void Nvic_Init(void)
��    �ܣ�	NVIC��ʼ��
*******************************************************************************/ 
void Nvic_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//NVIC_PriorityGroup 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���ȼ�����
	//Timer3
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/******************************************************************************
����ԭ�ͣ�	void BSP_Int(void)
��    �ܣ�	Ӳ��������ʼ��
*******************************************************************************/ 
void BSP_Init(void)
{
	RCC_Configuration(); 														//ʱ������
	Timer3_Init(10000 - 1);										 			//�����Զ�װ��ֵ10000,Ԥ��Ƶϵ��7200,ʱ��Ƶ��=72 000 000/(10000)*(72 00) = 1HZ (1s)
	Nvic_Init();																		//�ж����ȼ���ʼ��		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2,2λ��ռ���ȼ�,2λ��Ӧ���ȼ�
	USART1_Init(115200); 														//���ڳ�ʼ��Ϊ115200
	USART2_Init(115200); 														//���ڳ�ʼ���������ǲ����ʣ�
	Key_GPIO_Config();
	USART1_printf("\r\n Bsp Init Finish"); 	
}

