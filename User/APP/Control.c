#include "sys.h"
#include "Control.h"
#include "struct_all.h"
#include "Rc.h"
#include "delay.h"
#include "Usart.h"
#include "Maths.h"

uint8_t Rc_Lock=0;//1上锁；0解锁

/******************************************************************************
函数原型：	void RC_Limit(struct _Rc *rc)
功    能：	限制遥控指令范围
*******************************************************************************/ 
void RC_Limit(struct _Rc *rc)
{
	rc->THROTTLE = (rc->THROTTLE<=1000)?1000:rc->THROTTLE; 
	rc->THROTTLE = (rc->THROTTLE>=2000)?2000:rc->THROTTLE; 
	rc->PITCH = (rc->PITCH<=1000)?1000:rc->PITCH; 
	rc->PITCH = (rc->PITCH>=2000)?2000:rc->PITCH; 
	rc->ROLL = (rc->ROLL<=1000)?1000:rc->ROLL; 
	rc->ROLL = (rc->ROLL>=2000)?2000:rc->ROLL; 
	rc->YAW  = (rc->YAW<=1000)?1000:rc->YAW; 
	rc->YAW  = (rc->YAW>=2000)?2000:rc->YAW; 
	rc->AUX1 = (rc->AUX1<=1000)?1000:rc->AUX1; 
	rc->AUX1 = (rc->AUX1>=2000)?2000:rc->AUX1; 
	rc->AUX2 = (rc->AUX2<=1000)?1000:rc->AUX2; 
	rc->AUX2 = (rc->AUX2>=2000)?2000:rc->AUX2; 
	rc->AUX3 = (rc->AUX3<=1000)?1000:rc->AUX3; 
	rc->AUX3 = (rc->AUX3>=2000)?2000:rc->AUX3; 
}
	
/******************************************************************************
函数原型：	void RC_LOCK(void)
功    能：	遥控手势指令及解锁处理（以下注释针对美国手，遥控默认的就是美国手）
*******************************************************************************/ 
void RC_LOCK(void)
{	
	Rc_Lock = 0;
	static uint8_t count0,count1,count2;
	if(Rc.THROTTLE<1300 )//&& Rc.YAW>1700 && Rc.PITCH>1400 && Rc.PITCH<1600)
		count0++;
	else
		count0 = 0;
	
	if(count0>15 && Rc_Lock==1)
	{
		Rc_Lock = 0;//左手油门手的摇杆打向右下角，右手摇杆不动，解锁
	}
////////////////////////////////////////////////	
	if(Rc.THROTTLE<1300 && Rc.YAW<1300 && Rc.PITCH>1400 && Rc.PITCH<1600)
		count1++;
	else
		count1 = 0;
	
	if(count1>150 && Rc_Lock==0)
	{
		Rc_Lock = 1;//左手油门手的摇杆打向左下角，右手摇杆不动，上锁
	}
////////////////////////////////////////////////	
	if(Rc.THROTTLE<1300 && Rc.YAW<1300 && Rc.PITCH<1300)
		count2++;
	else
		count2 = 0;
	
	if(count2>100 )//&& Rc_Lock)//上锁状态才能校正
	{
		count2=0;
		Do_GYRO_Offset();//左手油门手的摇杆打向左下角，右手摇杆俯仰方向拉到最底，校正陀螺仪
		Do_ACC_Offset(); //左手油门手的摇杆打向左下角，右手摇杆俯仰方向拉到最底，校正加速度计	
	}
}

#define angle_max 	 		10.0f	
#define angle_integral_max 	1000.0f	
/******************************************************************************
函数原型：	void Control_Angle(struct _out_angle *angle,struct _Rc *rc)
功    能：	PID控制器(外环)
*******************************************************************************/ 
void Control_Angle(struct _out_angle *angle,struct _Rc *rc)
{
	static struct _out_angle control_angle;
	static struct _out_angle last_angle;
//////////////////////////////////////////////////////////////////
//			以下为角度环
//////////////////////////////////////////////////////////////////
///////////遥控死区限定///////////////////////////////////////////
	if(rc->ROLL>1490 && rc->ROLL<1510)	
		rc->ROLL=1500;
	if(rc->PITCH>1490 && rc->PITCH<1510)	
		rc->PITCH=1500;
///////////微调死区限定///////////////////////////////////////////
//	if(rc->AUX1>1495 && rc->AUX1<1505)	
		rc->AUX1=1500;
//	if(rc->AUX2>1495 && rc->AUX2<1505)	
		rc->AUX2=1500;
//////////////////////////////////////////////////////////////////
	control_angle.roll  = angle->roll  - (rc->ROLL  -1500)/13.0f + (rc->AUX2 -1500)/100.0f;
	control_angle.pitch = angle->pitch - (rc->PITCH -1500)/13.0f - (rc->AUX1 -1500)/100.0f;
//////////////////////////////////////////////////////////////////
	if(control_angle.roll >  angle_max)			//Roll角度限幅
		roll.integral +=  angle_max;
	if(control_angle.roll < -angle_max)
		roll.integral += -angle_max;
	else
		roll.integral += control_angle.roll;
	
	if(roll.integral >  angle_integral_max)	//Roll角度限幅
	   roll.integral =  angle_integral_max;
	if(roll.integral < -angle_integral_max)
	   roll.integral = -angle_integral_max;
//////////////////////////////////////////////////////////////////
	if(control_angle.pitch >  angle_max)		//Pitch角度限幅
	   pitch.integral +=  angle_max;
	if(control_angle.pitch < -angle_max)
	   pitch.integral += -angle_max;
	else
		 pitch.integral += control_angle.pitch;

	if(pitch.integral >  angle_integral_max)//Pitch角度限幅
	   pitch.integral =  angle_integral_max;
	if(pitch.integral < -angle_integral_max)
	   pitch.integral = -angle_integral_max;
//////////////////////////////////////////////////////////////////
	if(rc->THROTTLE<1200)//油门较小时，积分清零
	{
		roll.integral  = 0;
		pitch.integral = 0;
	}
//////////////////////////////////////////////////////////////////
	roll.output  = roll.kp*control_angle.roll		+ roll.ki*roll.integral 	+	roll.kd*(control_angle.roll 	- last_angle.roll );
	pitch.output = pitch.kp*control_angle.pitch + pitch.ki*pitch.integral + pitch.kd*(control_angle.pitch - last_angle.pitch);
//////////////////////////////////////////////////////////////////
	last_angle.roll =control_angle.roll;
	last_angle.pitch=control_angle.pitch;
}

#define gyro_max 	 		50.0f	
#define gyro_integral_max 	5000.0f
/******************************************************************************
函数原型：	void Control_Gyro(struct _SI_float *gyro,struct _Rc *rc,uint8_t Lock)
功    能：	PID控制器(内环)
*******************************************************************************/ 
void Control_Gyro(struct _SI_float *gyro,struct _Rc *rc,uint8_t Lock)
{
	static struct _out_angle control_gyro;
	static struct _out_angle last_gyro;
	int16_t throttle1,throttle2,throttle3,throttle4;
//////////////////////////////////////////////////////////////////
//			以下为角速度环
//////////////////////////////////////////////////////////////////
	if(rc->YAW>1400 && rc->YAW<1600)			//遥控死区限定
		rc->YAW=1500;
//	if(rc->AUX3>1495 && rc->AUX3<1505)	//微调死区限定
		rc->AUX3=1500;
//////////////////////////////////////////////////////////////////
	control_gyro.roll  = -roll.output - gyro->y*Radian_to_Angle;
	control_gyro.pitch = pitch.output - gyro->x*Radian_to_Angle;
//	if(rc->AUX4 & Lock_Mode)
//		control_gyro.yaw   = - gyro->z*Radian_to_Angle - (rc->AUX3 -1500)/100.0f;//锁尾模式
//	else
		control_gyro.yaw   = -(rc->YAW-1500)/2.0f - gyro->z*Radian_to_Angle + (rc->AUX3 -1500)/50.0f;//非锁尾模式
//////////////////////////////////////////////////////////////////
	if(control_gyro.roll >  gyro_max)		//GYRO_ROLL限幅
		gyro_roll.integral +=  gyro_max;
	if(control_gyro.roll < -gyro_max)
		gyro_roll.integral += -gyro_max;
	else
		gyro_roll.integral += control_gyro.roll;
	
	if(gyro_roll.integral >  gyro_integral_max)
	   gyro_roll.integral =  gyro_integral_max;
	if(gyro_roll.integral < -gyro_integral_max)
	   gyro_roll.integral = -gyro_integral_max;
//////////////////////////////////////////////////////////////////
	if(control_gyro.pitch >  gyro_max)	//GYRO_PITCH限幅
		gyro_pitch.integral +=  gyro_max;
	if(control_gyro.pitch < -gyro_max)
		gyro_pitch.integral += -gyro_max;
	else
		gyro_pitch.integral += control_gyro.pitch;
	
	if(gyro_pitch.integral >  gyro_integral_max)
	   gyro_pitch.integral =  gyro_integral_max;
	if(gyro_pitch.integral < -gyro_integral_max)
	   gyro_pitch.integral = -gyro_integral_max;
//////////////////////////////////////////////////////////////////
//	if(control_gyro.yaw >  gyro_max)//GYRO_YAW
//		gyro_yaw.integral +=  gyro_max;
//	if(control_gyro.yaw < -gyro_max)
//		gyro_yaw.integral += -gyro_max;
//	else
		gyro_yaw.integral += control_gyro.yaw;
	
	if(gyro_yaw.integral >  gyro_integral_max)//GYRO_YAW限幅
	   gyro_yaw.integral =  gyro_integral_max;
	if(gyro_yaw.integral < -gyro_integral_max)
	   gyro_yaw.integral = -gyro_integral_max;
//////////////////////////////////////////////////////////////////
	if(rc->THROTTLE<1200)//油门较小时，积分清零
	{
		gyro_yaw.integral  = 0;
	}
//////////////////////////////////////////////////////////////////
	gyro_roll.output  = gyro_roll.kp*control_gyro.roll   + gyro_roll.ki*gyro_roll.integral   + gyro_roll.kd*(control_gyro.roll - last_gyro.roll );
	gyro_pitch.output = gyro_pitch.kp*control_gyro.pitch + gyro_pitch.ki*gyro_pitch.integral + gyro_pitch.kd*(control_gyro.pitch - last_gyro.pitch);
	gyro_yaw.output   = gyro_yaw.kp*control_gyro.yaw     + gyro_yaw.ki*gyro_yaw.integral     + gyro_yaw.kd*(control_gyro.yaw - last_gyro.yaw  );
//////////////////////////////////////////////////////////////////
	last_gyro.roll =control_gyro.roll;
	last_gyro.pitch=control_gyro.pitch;
	last_gyro.yaw  =control_gyro.yaw;
//////////////////////////////////////////////////////////////////
	if(rc->THROTTLE>1200 && Lock==0)
	{
		throttle1 = rc->THROTTLE - 50 + gyro_pitch.output + gyro_roll.output - gyro_yaw.output;
		throttle2 = rc->THROTTLE - 50 + gyro_pitch.output - gyro_roll.output + gyro_yaw.output;
		throttle3 = rc->THROTTLE - 50 - gyro_pitch.output + gyro_roll.output + gyro_yaw.output;
		throttle4 = rc->THROTTLE - 50 - gyro_pitch.output - gyro_roll.output - gyro_yaw.output;
	}
	else
	{
		throttle1=0;
		throttle2=0;
		throttle3=0;
		throttle4=0;
	}
	Motor_Out(throttle1,throttle2,throttle3,throttle4);
}







/***************************************************/
extern u32 M1_Output = 0; 
extern u32 M2_Output = 0; 
extern u32 M3_Output = 0; 
extern u32 M4_Output = 0; 



void Manual_Fly_Mode(void)
{
	M1_Output = M2_Output = M3_Output = M4_Output = CH3;
	
/////////////////////////////////下面的程序会使单片机跑飞	
//	CH1 -= 1500;
//	CH2 -= 1500;
//	/*********************
//					CH1
//	**********************/
////	if(-5 <= CH1 <= 5)//死区设定
////	{
////		M1_Output = M2_Output = M3_Output = M4_Output = CH3;
////	}
//	if(CH1 > 5)//横滚杆打右
//	{
//		M1_Output = M4_Output = (CH3 - CH1);
//		M3_Output = M2_Output = (CH3 + CH1);	
////		USART1_printf("right"); 
//	}
//	if(CH1 < -5)//横滚杆打左
//	{
//		M1_Output = M4_Output = (CH3 - CH1);
//		M3_Output = M2_Output = (CH3 + CH1);	
////		USART1_printf("left"); 
//	}
////	USART1_printf("CH1_Output:%d	",CH1); 
//	/*********************
//					CH2
//	**********************/
////	if(-5 <= CH2 <= 5)//死区设定
////	{
////		M1_Output = M2_Output = M3_Output = M4_Output = CH3;
////	}
//	if(CH2 > 5)//俯仰杆打上
//	{
//		M1_Output = M3_Output = (CH3 - CH2);
//		M4_Output = M2_Output = (CH3 + CH2);	
////		USART1_printf("up"); 
//	}
//	if(CH2 < -5)//俯仰杆打下
//	{
//		M1_Output = M3_Output = (CH3 - CH2);
//		M4_Output = M2_Output = (CH3 + CH2);	
////		USART1_printf("dowm"); 
//	}
//	
//	if(CH3<900)//失控保护
//	{
//		TIM_SetCompare1(TIM4, 0);		
//		TIM_SetCompare2(TIM4, 0);
//		TIM_SetCompare3(TIM4, 0);
//		TIM_SetCompare4(TIM4, 0);	
//	}
//	
//	TIM_SetCompare1(TIM4, M1_Output);
//	TIM_SetCompare2(TIM4, M2_Output);
//	TIM_SetCompare3(TIM4, M3_Output);
//	TIM_SetCompare4(TIM4, M4_Output);
	
//	USART1_printf("\r\n M1_Output=%d	",M1_Output);
//	USART1_printf("M2_Output=%d	",M2_Output);
//	USART1_printf("M3_Output=%d	",M3_Output);	
//	USART1_printf("M4_Output=%d	",M4_Output);
//	delay_ms(50);
}



