#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "semihosting.h"
#include "tm_stm32f4_i2c.h"
#include "stm32f4xx_tim.h"
#include "misc.h"
#include "stdio.h"
#include <math.h>
#define PI 3.14159265
#define ap 0.955
NVIC_InitTypeDef N;
TIM_TimeBaseInitTypeDef T;
static int count = 0 ;
int8_t AXH=0;	uint8_t AXL=0;  int16_t AX=0;
int8_t AYH=0;	uint8_t AYL=0;	int16_t AY=0;
int8_t AZH=0;	uint8_t AZL=0;	int16_t AZ=0;
int8_t GxH=0;	uint8_t GxL=0;	int16_t Gx=0;
int8_t GyH=0;	uint8_t GyL=0;	int16_t Gy=0;
int8_t GzH=0;	uint8_t GzL=0;	int16_t Gz=0;
int Axangle=0,Ayangle=0,Azangle=0;	int gyroXrate=0,gyroYrate=0,gyroZrate=0;
int gyroXangle=0,gyroYangle=0,gyroZangle=0;
int compAngleX=0,compAngleY=0,compAngleZ=0;
int t=0;
void tim()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	T.TIM_Prescaler = 17-1;
	T.TIM_Period = 1000000-1;
	T.TIM_ClockDivision = TIM_CKD_DIV1;
	T.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &T);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);

	N.NVIC_IRQChannel=TIM2_IRQn;
	N.NVIC_IRQChannelPreemptionPriority = 1;
	N.NVIC_IRQChannelSubPriority = 1;
	N.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&N);
}
void TIM2_IRQHandler()
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{

		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
		count+=1000;
		AXH = (int8_t)TM_I2C_Read( 0x68<<1, 0x3B );
		AXL = TM_I2C_Read( 0x68<<1, 0x3C );
		AX = (AXH*256 + AXL)/1638;

		AYH = (int8_t)TM_I2C_Read( 0x68<<1, 0x3D);
		AYL = TM_I2C_Read( 0x68<<1, 0x3E );
		AY = (AYH*256 + AYL)/1638;

		AZH = (int8_t)TM_I2C_Read( 0x68<<1, 0x3F );
		AZL = TM_I2C_Read( 0x68<<1, 0x40 );
		AZ = (AZH*256 + AZL)/1638;

		GxH = (int8_t)TM_I2C_Read(0x68<<1,0x43);
		GxL= TM_I2C_Read(0x68<<1,0x44);
		Gx=(GxH*256 + GxL);

		GyH = (int8_t)TM_I2C_Read(0x68<<1,0x45);
		GyL= TM_I2C_Read(0x68<<1,0x46);
		Gy=(GyH*256 + GyL);

		GzH = (int8_t)TM_I2C_Read(0x68<<1,0x47);
		GzL= TM_I2C_Read(0x68<<1,0x48);
		Gz=(GzH*256 + GzL);

		Axangle = atan(AY/AZ)*180/PI;
		Ayangle = atan(AX/AZ)*180/PI;
		Azangle = atan(AX/AY)*180/PI;
		gyroXrate = Gx / 16.5;
		gyroYrate = Gy / 16.5;
		gyroZrate = Gz / 16.5;

		gyroXangle = gyroXrate * (count-t)/1000;
		gyroYangle = gyroYrate * (count-t)/1000;
		gyroZangle = gyroZrate * (count-t)/1000;
		gyroXangle=gyroXangle%360;
		gyroYangle=gyroYangle%360;
		gyroZangle=gyroZangle%360;

		compAngleX = ap * (compAngleX + gyroXangle) + (1-ap) * Axangle;
		compAngleY = ap * (compAngleY + gyroYangle) + (1-ap) * Ayangle;
		compAngleZ = ap * (compAngleZ + gyroZangle) + (1-ap) * Azangle;
		compAngleX = compAngleX%360;
		compAngleY = compAngleY%360;
		compAngleZ = compAngleZ%360;

		printf("ACCEL  x=%d,  y=%d,  z=%d\n", AX, AY, AZ);
		printf("GYRO  x=%d,  y=%d,  z=%d\n", Gx, Gy, Gz);
		printf("ANGLE  x=%d,  y=%d,  z=%d\n", Axangle, Ayangle, Azangle);
		printf("GYRORATE  x=%d,  y=%d,  z=%d\n", gyroXrate, gyroYrate, gyroZrate);
		printf("GYROANGLE  x=%d,  y=%d,  z=%d\n", gyroXangle, gyroYangle, gyroZangle);
		printf("Computed ANGLE  x=%d,  y=%d,  z=%d\n", compAngleX, compAngleY, compAngleZ);
		printf("COUNT: %d\n",count);
		printf("T: %d\n\n",t);

		t=count;

	}
}
int main(void)
{
	TM_I2C_Init(TM_I2C_CLOCK_STANDARD);
	TM_I2C_Write(0x68<<1, 0x6B, 0);
	tim();
    while(1)
    {
    	/*TIM_SetCounter(TIM2,0);

    	AXH = (int8_t)TM_I2C_Read( 0x68<<1, 0x3B );
		AXL = TM_I2C_Read( 0x68<<1, 0x3C );
		AX = (AXH*256 + AXL)/1638;

		AYH = (int8_t)TM_I2C_Read( 0x68<<1, 0x3D);
		AYL = TM_I2C_Read( 0x68<<1, 0x3E );
		AY = (AYH*256 + AYL)/1638;

		AZH = (int8_t)TM_I2C_Read( 0x68<<1, 0x3F );
		AZL = TM_I2C_Read( 0x68<<1, 0x40 );
		AZ = (AZH*256 + AZL)/1638;

		GxH = (int8_t)TM_I2C_Read(0x68<<1,0x43);
		GxL= TM_I2C_Read(0x68<<1,0x44);
		Gx=(GxH*256 + GxL);

		GyH = (int8_t)TM_I2C_Read(0x68<<1,0x45);
		GyL= TM_I2C_Read(0x68<<1,0x46);
		Gy=(GyH*256 + GyL);

		GzH = (int8_t)TM_I2C_Read(0x68<<1,0x47);
		GzL= TM_I2C_Read(0x68<<1,0x48);
		Gz=(GzH*256 + GzL);

		Axangle = atan(AY/AZ)*180/PI;
		Ayangle = atan(AX/AZ)*180/PI;
		Azangle = atan(AX/AY)*180/PI;
		gyroXrate = Gx / 16.5;
		gyroYrate = Gy / 16.5;
		gyroZrate = Gz / 16.5;

		gyroXangle += gyroXrate * (count-t)/1000;
		gyroYangle += gyroYrate * (count-t)/1000;
		gyroZangle += gyroZrate * (count-t)/1000;
		gyroXangle=gyroXangle%360;
		gyroYangle=gyroYangle%360;
		gyroZangle=gyroZangle%360;

		compAngleX = ap * (compAngleX + gyroXangle) + (1-ap) * Axangle;
		compAngleY = ap * (compAngleY + gyroYangle) + (1-ap) * Ayangle;
		compAngleZ = ap * (compAngleZ + gyroZangle) + (1-ap) * Azangle;
		compAngleX = compAngleX%360;
		compAngleY = compAngleY%360;
		compAngleZ = compAngleZ%360;

		printf("ACCEL  x=%d,  y=%d,  z=%d\n", AX, AY, AZ);
		printf("GYRO  x=%d,  y=%d,  z=%d\n", Gx, Gy, Gz);
		printf("ANGLE  x=%d,  y=%d,  z=%d\n", Axangle, Ayangle, Azangle);
		printf("GYRORATE  x=%d,  y=%d,  z=%d\n", gyroXrate, gyroYrate, gyroZrate);
		printf("GYROANGLE  x=%d,  y=%d,  z=%d\n", gyroXangle, gyroYangle, gyroZangle);
		printf("Computed ANGLE  x=%d,  y=%d,  z=%d\n", compAngleX, compAngleY, compAngleZ);
		printf("COUNT: %d\n",count);
		printf("T: %d\n\n",t);

		t=count;
		*/
    }
}
