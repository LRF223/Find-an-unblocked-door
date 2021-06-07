#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h" 

/************���Ŷ���***************/
#define KEY1_PIN                  GPIO_Pin_1              //GPIO���ź�   
#define KEY1_GPIO_PORT            GPIOB                   //GPIO�˿�   
#define KEY1_GPIO_CLK             RCC_AHB2Periph_GPIOB    //GPIO�˿�ʱ��

#define KEY2_PIN                  GPIO_Pin_13                 
#define KEY2_GPIO_PORT            GPIOC                      
#define KEY2_GPIO_CLK             RCC_AHB1Periph_GPIOC


/************�������ú�****************
   * �������¸ߵ�ƽ��KEY_ON=1��KEY_OFF=0��
   * �������µ͵�ƽ��KEY_ON=0��KEY_OFF=1
***************************************/
#define KEY_ON  0
#define KEY_OFF 1

void Key_GPIO_Config(void); //����KEY-GPIO��ʼ�����ú���
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin); //�������¼��

#endif 
