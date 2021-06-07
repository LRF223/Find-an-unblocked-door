#include "stm32f10x.h" 
#include "Tasks.h"
#include "Usart.h"
#include "Key.h" 
#include "Delay.h"
#include "Timer.h"

int main (void)
{	
	uint32_t Now_time,Last_time,Inerval_time;	//Ҫ�õ���ǰʱ�䡢�ϴ�ʱ�䡢ʱ��������һ��
	BSP_Init();																//Ӳ����ʼ��һ����
	while(1)//����ѭ����ȥ��day by day
	{																
		if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON )//������û�����߹����ѿ��ش�����
		{	
			while(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON );//���������߹����ټ�������ʱ��
																																			 //��Ȼ�����������ص��뿪�������ʱ�������һֱ��ͣ�ط���ʱ
			Now_time     = Count_1s;							//Count_1sÿ���һ���൱��һ�����������һ������ȫ���������ذ��������һ�µ�ǰʱ��
			Inerval_time = Now_time - Last_time;  //��������˺��ϸ��˵ľ������˶೤ʱ��
			Last_time    = Now_time;							//����֮�󣬰���μ��µĵ�ǰʱ�䣬������һ��Ҫ��ȥ��ʱ��
			
			if(Inerval_time<2)												USART2_printf("\r\n Blocked");		//�������������ſھ��������ˣ��Ǿͺö���
			else if(2<=Inerval_time&&Inerval_time<=5) USART2_printf("\r\n Busy");				//2��5���ڣ���û��ô����
			else																			USART2_printf("\r\n Unblocked");	//��ѡ�������
			USART2_printf("\r\n Inerval_time = %d",Inerval_time);												//��ӡʱ�����������뿴��
		}								
	}
}

