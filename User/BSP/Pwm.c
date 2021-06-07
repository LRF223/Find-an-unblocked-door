#include "pwm.h"
#include "struct_all.h"

/******************************************************************************
函数原型：	void TIM4_PWM_Init(u16 arr,u16 psc)
功    能：	tim4初始化
*******************************************************************************/ 
void TIM4_PWM_Init(u16 arr,u16 psc)																//TIM4 PWM初始化 arr重装载值 psc预分频系数
{  														
	GPIO_InitTypeDef    		 GPIO_InitStrue;
  TIM_OCInitTypeDef    		 TIM_OCInitStrue;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStrue;
      
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);						//使能TIM4和相关GPIO时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);					//使能GPIOB时钟
    
  GPIO_InitStrue.GPIO_Pin= M1_Pin | M2_Pin | M3_Pin | M4_Pin;		
  GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;											//复用推挽
  GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;										//设置最大输出速度
  GPIO_Init(PWM_GPIO,&GPIO_InitStrue);													//GPIO端口初始化设置
	      
  TIM_TimeBaseInitStrue.TIM_Period=arr;    											//设置自动重装载值
  TIM_TimeBaseInitStrue.TIM_Prescaler=psc;        		  				//预分频系数
  TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;     //计数器向上溢出
  TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;         //不分频
  TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStrue);        				//TIM4初始化设置(设置PWM的周期)

  TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        						//PWM模式1:CNT < CCR时输出有效电平
  TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;						//设置极性-有效电平为：高电平
  TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;				//输出使能

	TIM_OC1Init(TIM4,&TIM_OCInitStrue);  							
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);      			  //使能预装载寄存器
	TIM_OC2Init(TIM4,&TIM_OCInitStrue);  							
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);      			  //使能预装载寄存器
	TIM_OC3Init(TIM4,&TIM_OCInitStrue);  							
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);      			  //使能预装载寄存器		
	TIM_OC4Init(TIM4,&TIM_OCInitStrue);  							
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);      			  //使能预装载寄存器		

	TIM_ARRPreloadConfig(TIM4, ENABLE); 													//使能TIM4在ARR上的预装载寄存器
	TIM_Cmd(TIM4, ENABLE);  																			//使能TIM4外设
   
}

/******************************************************************************
函数原型：	void Motor_Out(int16_t duty1,int16_t duty2,int16_t duty3,int16_t duty4)
功    能：	电机驱动
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
