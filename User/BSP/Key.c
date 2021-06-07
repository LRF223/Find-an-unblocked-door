#include "Key.h" 

/************************************
  * 配置按键用到的IO口
*************************************/
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; //定义GPIO的初始化枚举结构	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);       
  GPIO_InitStructure.GPIO_Pin = KEY1_PIN; //选择端口号（0~15或all）                        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //选择IO接口工作方式 //上拉电阻       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置IO接口速度（2/10/50MHz）    
	GPIO_Init(KEY1_GPIO_PORT ,&GPIO_InitStructure);			
}

/*********************************************
  * @brief      检测是否有按键按下     
  * @param  GPIOx:具体的端口（x=A，B...K）
  * @param  GPIO_PIN:具体的端口位（x=0...15）
  * @retval  按键状态
  * @arg KEY_ON:按键按下
  * @arg KEY_OFF:按键没按下
 *********************************************/
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin) //按下返回KEY_ON，没按返回KEY_OFF
{           
    /*检测是否有按键按下*/
    if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
    {    
        /*等待按键释放*/
        while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
        return  KEY_ON;  
    }
    else
        return KEY_OFF;
}
