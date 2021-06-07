#include "Rc.h"
#include "Usart.h"
#include "struct_all.h"

/********输入捕获状态***********/		
extern u8   TIM2CH1_CAPTURE_STA;	    				
extern u8   TIM2CH2_CAPTURE_STA;		    				
extern u8   TIM2CH3_CAPTURE_STA;			    				
extern u8   TIM2CH4_CAPTURE_STA;

/********输入捕获值*************/
extern u16	TIM2CH1_CAPTURE_VAL;	
extern u16	TIM2CH2_CAPTURE_VAL;	
extern u16	TIM2CH3_CAPTURE_VAL;	
extern u16	TIM2CH4_CAPTURE_VAL;	

//extern u8   TIM1CH1_CAPTURE_STA;	//输入捕获状态		    				
//extern u16	TIM1CH1_CAPTURE_VAL;	//输入捕获值
//extern u8   TIM1CH2_CAPTURE_STA;	//输入捕获状态		    				
//extern u16	TIM1CH2_CAPTURE_VAL;	//输入捕获值
//extern u8   TIM1CH3_CAPTURE_STA;	//输入捕获状态		    				
//extern u16	TIM1CH3_CAPTURE_VAL;	//输入捕获值


extern u32 CH1=0; 
extern u32 CH2=0; 
extern u32 CH3=0; 
extern u32 CH4=0; 
//extern u32 CH5=0; 
//extern u32 CH6=0; 
//extern u32 CH7=0; 

void Rc_Recive(void)
{	
	/**************通道一信号接收*******************/
	if(TIM2CH1_CAPTURE_STA&0X80)						//成功捕获到了一次上升沿
	{
    Rc.ROLL	=	TIM2CH1_CAPTURE_STA&0X3F;
		Rc.ROLL	*=	65536;										//溢出时间总和
		Rc.ROLL	+=	TIM2CH1_CAPTURE_VAL;			//得到总的高电平时间
    TIM2CH1_CAPTURE_STA = 0;        
  }	
	
	/**************通道二信号接收*******************/
	if(TIM2CH2_CAPTURE_STA&0X80)						//成功捕获到了一次上升沿
	{
    Rc.PITCH =  TIM2CH2_CAPTURE_STA&0X3F;
		Rc.PITCH *= 65536;										//溢出时间总和
		Rc.PITCH += TIM2CH2_CAPTURE_VAL;			//得到总的高电平时间
    TIM2CH2_CAPTURE_STA = 0;        
  }
	
	/**************通道三信号接收*******************/
	if(TIM2CH3_CAPTURE_STA&0X80)						//成功捕获到了一次上升沿
	{
    Rc.THROTTLE = TIM2CH3_CAPTURE_STA&0X3F;
		Rc.THROTTLE *= 65536;									//溢出时间总和
		Rc.THROTTLE += TIM2CH3_CAPTURE_VAL;		//得到总的高电平时间
    TIM2CH3_CAPTURE_STA = 0;     
  }
	
	/**************通道四信号接收*******************/
  if(TIM2CH4_CAPTURE_STA&0X80)						//成功捕获到了一次上升沿
	{
    Rc.YAW	=		TIM2CH4_CAPTURE_STA&0X3F;
		Rc.YAW	*=	65536;										//溢出时间总和
		Rc.YAW	+=	TIM2CH4_CAPTURE_VAL;			//得到总的高电平时间
    TIM2CH4_CAPTURE_STA = 0;        
  }		
	
//	/**************通道五信号接收*******************/
//  if(TIM1CH1_CAPTURE_STA&0X80)						//成功捕获到了一次上升沿
//	{
//    CH5	=		TIM1CH1_CAPTURE_STA&0X3F;
//		CH5	*=	65536;										//溢出时间总和
//		CH5	+=	TIM1CH1_CAPTURE_VAL;			//得到总的高电平时间
//    TIM1CH1_CAPTURE_STA = 0;        
//  }			

//	/**************通道六信号接收*******************/
//  if(TIM1CH2_CAPTURE_STA&0X80)						//成功捕获到了一次上升沿
//	{
//    CH6	=		TIM1CH2_CAPTURE_STA&0X3F;
//		CH6	*=	65536;										//溢出时间总和
//		CH6	+=	TIM1CH2_CAPTURE_VAL;			//得到总的高电平时间
//    TIM1CH2_CAPTURE_STA = 0;        
//  }		
//	
//	/**************通道七信号接收*******************/
//  if(TIM1CH3_CAPTURE_STA&0X80)						//成功捕获到了一次上升沿
//	{
//    CH7	=		TIM1CH3_CAPTURE_STA&0X3F;
//		CH7	*=	65536;										//溢出时间总和
//		CH7	+=	TIM1CH3_CAPTURE_VAL;			//得到总的高电平时间
//    TIM1CH3_CAPTURE_STA = 0;        
//  }			
	
//  USART1_printf("Rc.ROLL:%d	",Rc.ROLL); 
//	USART1_printf("Rc.PITCH:%d	",Rc.PITCH); 
//	USART1_printf("Rc.THROTTLE:%d	",Rc.THROTTLE); 	
//	USART1_printf("Rc.YAW:%d ",Rc.YAW); 
//	USART1_printf("RC.CH5:%d ",CH5); 	
//	USART1_printf("RC.CH6:%d ",CH6); 	
//	USART1_printf("RC.CH7:%d\r\n",CH7); 	
}
