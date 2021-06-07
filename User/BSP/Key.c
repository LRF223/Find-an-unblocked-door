#include "Key.h" 

/************************************
  * ���ð����õ���IO��
*************************************/
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ĳ�ʼ��ö�ٽṹ	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);       
  GPIO_InitStructure.GPIO_Pin = KEY1_PIN; //ѡ��˿ںţ�0~15��all��                        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ѡ��IO�ӿڹ�����ʽ //��������       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����IO�ӿ��ٶȣ�2/10/50MHz��    
	GPIO_Init(KEY1_GPIO_PORT ,&GPIO_InitStructure);			
}

/*********************************************
  * @brief      ����Ƿ��а�������     
  * @param  GPIOx:����Ķ˿ڣ�x=A��B...K��
  * @param  GPIO_PIN:����Ķ˿�λ��x=0...15��
  * @retval  ����״̬
  * @arg KEY_ON:��������
  * @arg KEY_OFF:����û����
 *********************************************/
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin) //���·���KEY_ON��û������KEY_OFF
{           
    /*����Ƿ��а�������*/
    if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
    {    
        /*�ȴ������ͷ�*/
        while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
        return  KEY_ON;  
    }
    else
        return KEY_OFF;
}
