#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h" 

/************引脚定义***************/
#define KEY1_PIN                  GPIO_Pin_1              //GPIO引脚号   
#define KEY1_GPIO_PORT            GPIOB                   //GPIO端口   
#define KEY1_GPIO_CLK             RCC_AHB2Periph_GPIOB    //GPIO端口时钟

#define KEY2_PIN                  GPIO_Pin_13                 
#define KEY2_GPIO_PORT            GPIOC                      
#define KEY2_GPIO_CLK             RCC_AHB1Periph_GPIOC


/************按键标置宏****************
   * 按键按下高电平，KEY_ON=1，KEY_OFF=0，
   * 按键按下低电平，KEY_ON=0，KEY_OFF=1
***************************************/
#define KEY_ON  0
#define KEY_OFF 1

void Key_GPIO_Config(void); //定义KEY-GPIO初始化配置函数
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin); //按键按下检测

#endif 
