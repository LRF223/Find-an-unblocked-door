#ifndef MPU6050_H_
#define MPU6050_H_
#include "stm32f10x.h"

/******************************************************************************
							�궨��
*******************************************************************************/ 
#define SCL_Pin 	GPIO_Pin_10
#define SDA_Pin 	GPIO_Pin_11

/******************************************************************************
							ȫ�ֱ�������
*******************************************************************************/ 	
extern uint8_t	GYRO_Offset;	
extern uint8_t	ACC_Offset;
extern uint32_t I2C_Erro;
				
/******************************************************************************
							ȫ�ֺ�������
*******************************************************************************/ 
uint8_t InitMPU6050(void);
uint8_t MPU6050_SequenceRead(void);
uint8_t MPU6050_Init(void);
void I2C_MPU6050_Init(void);
void MPU6050_SingleRead(void);
void MPU6050_Compose(void);
void MPU6050_Printf(void);
void Do_ACC_Offset(void);
void Do_GYRO_Offset(void);

/******************************************************************************
							����MPU6050�Ĵ�����ַ
*******************************************************************************/ 
#define	SMPLRT_DIV		0x19	
#define	CONFIG2			0x1A	
#define	GYRO_CONFIG		0x1B	
#define	ACCEL_CONFIG	0x1C	
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//��Դ����������ֵ��0x00(��������)
#define	WHO_AM_I		0x75	//IIC��ַ�Ĵ����ĵ�ַ(Ĭ����ֵ0x68��ֻ��!!!)

//����������IIC�����еĴӵ�ַ
//I2C������ַ��7bit������8bit����ģ��I2C��8bit���͵�ַ�������0xD0������AD0���Žӵأ�
#define	MPU6050Address	0xD0



#endif
