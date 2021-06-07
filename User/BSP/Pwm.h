#ifndef  _PWM_H
#define  _PWM_H
#include "sys.h"
#include "stm32f10x.h"

#define PWM_GPIO GPIOB
#define M1_Pin GPIO_Pin_6
#define M2_Pin GPIO_Pin_7
#define M3_Pin GPIO_Pin_8
#define M4_Pin GPIO_Pin_9

/******************************************************************************
							全局函数声明
*******************************************************************************/ 
void TIM4_PWM_Init(u16 arr,u16 psc);
void Motor_Out(int16_t duty1,int16_t duty2,int16_t duty3,int16_t duty4);

#endif
