#include "pwm.h"
#include "struct_all.h"

/******************************************************************************
����ԭ�ͣ�	void TIM4_PWM_Init(u16 arr,u16 psc)
��    �ܣ�	tim4��ʼ��
*******************************************************************************/ 
void TIM4_PWM_Init(u16 arr,u16 psc)																//TIM4 PWM��ʼ�� arr��װ��ֵ pscԤ��Ƶϵ��
{  														
	GPIO_InitTypeDef    		 GPIO_InitStrue;
  TIM_OCInitTypeDef    		 TIM_OCInitStrue;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStrue;
      
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);						//ʹ��TIM4�����GPIOʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);					//ʹ��GPIOBʱ��
    
  GPIO_InitStrue.GPIO_Pin= M1_Pin | M2_Pin | M3_Pin | M4_Pin;		
  GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;											//��������
  GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;										//�����������ٶ�
  GPIO_Init(PWM_GPIO,&GPIO_InitStrue);													//GPIO�˿ڳ�ʼ������
	      
  TIM_TimeBaseInitStrue.TIM_Period=arr;    											//�����Զ���װ��ֵ
  TIM_TimeBaseInitStrue.TIM_Prescaler=psc;        		  				//Ԥ��Ƶϵ��
  TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;     //�������������
  TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;         //����Ƶ
  TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStrue);        				//TIM4��ʼ������(����PWM������)

  TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        						//PWMģʽ1:CNT < CCRʱ�����Ч��ƽ
  TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;						//���ü���-��Ч��ƽΪ���ߵ�ƽ
  TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;				//���ʹ��

	TIM_OC1Init(TIM4,&TIM_OCInitStrue);  							
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);      			  //ʹ��Ԥװ�ؼĴ���
	TIM_OC2Init(TIM4,&TIM_OCInitStrue);  							
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);      			  //ʹ��Ԥװ�ؼĴ���
	TIM_OC3Init(TIM4,&TIM_OCInitStrue);  							
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);      			  //ʹ��Ԥװ�ؼĴ���		
	TIM_OC4Init(TIM4,&TIM_OCInitStrue);  							
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);      			  //ʹ��Ԥװ�ؼĴ���		

	TIM_ARRPreloadConfig(TIM4, ENABLE); 													//ʹ��TIM4��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(TIM4, ENABLE);  																			//ʹ��TIM4����
   
}

/******************************************************************************
����ԭ�ͣ�	void Motor_Out(int16_t duty1,int16_t duty2,int16_t duty3,int16_t duty4)
��    �ܣ�	�������
*******************************************************************************/ 
void Motor_Out(int16_t duty1,int16_t duty2,int16_t duty3,int16_t duty4)
{
	if(duty1>2000)	duty1=2000;
	if(duty1<1000)	duty1=1000;
	
	if(duty2>2000)	duty2=2000;
	if(duty2<1000)	duty2=1000;
	
	if(duty3>2000)	duty3=2000;
	if(duty3<1000)	duty3=1000;
	
	if(duty4>2000)	duty4=2000;
	if(duty4<1000)	duty4=1000;
	
	TIM4->CCR1 = duty1;
	TIM4->CCR2 = duty2;
	TIM4->CCR3 = duty3;
	TIM4->CCR4 = duty4;
	
//	USART1_printf("	TIM4->CCR1 = %d",TIM4->CCR1); 
//	USART1_printf("	TIM4->CCR2 = %d",TIM4->CCR2);
//	USART1_printf("	TIM4->CCR3 = %d",TIM4->CCR3);	
//	USART1_printf("	TIM4->CCR4 = %d\r\n",TIM4->CCR4);

}
