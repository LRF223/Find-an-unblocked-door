#include "stm32f10x.h" 
#include "Tasks.h"
#include "Usart.h"
#include "Key.h" 
#include "Delay.h"
#include "Timer.h"

int main (void)
{	
	uint32_t Now_time,Last_time,Inerval_time;	//要用到当前时间、上次时间、时间差，先声明一下
	BSP_Init();																//硬件初始化一下下
	while(1)//无限循环下去，day by day
	{																
		if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON )//看看有没有人走过，把开关触发了
		{	
			while(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON );//等整个人走过了再记下现在时间
																																			 //不然在人碰到开关到离开开关这段时间里，它会一直不停地疯狂计时
			Now_time     = Count_1s;							//Count_1s每秒加一，相当于一个秒表，看到有一个人完全经过后，愉快地按下秒表，记一下当前时间
			Inerval_time = Now_time - Last_time;  //看看这个人和上个人的经过隔了多长时间
			Last_time    = Now_time;							//算完之后，把这次记下的当前时间，当成下一次要减去的时间
			
			if(Inerval_time<2)												USART2_printf("\r\n Blocked");		//如果如果两秒内门口经过两个人，那就好堵啦
			else if(2<=Inerval_time&&Inerval_time<=5) USART2_printf("\r\n Busy");				//2到5秒内，就没那么堵了
			else																			USART2_printf("\r\n Unblocked");	//我选择这个门
			USART2_printf("\r\n Inerval_time = %d",Inerval_time);												//打印时间差出来，我想看看
		}								
	}
}

