#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
GPIO_InitTypeDef GP;
I2C_InitTypeDef I;
#define SLA_ADD 0x01
#define MAS_ADD 0x00
int i;
void gpio()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GP.GPIO_OType = GPIO_OType_PP;
	GP.GPIO_PuPd = GPIO_PuPd_UP;
	GP.GPIO_Mode = GPIO_Mode_AF;
	GP.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6;
	GP.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GP);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GP.GPIO_OType = GPIO_OType_OD;
	GP.GPIO_PuPd = GPIO_PuPd_UP;
	GP.GPIO_Mode = GPIO_Mode_AF;
	GP.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GP.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GP);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C2);


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GP.GPIO_Mode= GPIO_Mode_OUT;
	GP.GPIO_OType = GPIO_OType_PP;
	GP.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GP.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GP.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GP);
}
void i2c()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	I2C_Cmd(I2C1,ENABLE);
	I.I2C_Ack= I2C_Ack_Disable;
	I.I2C_ClockSpeed= 100000;
	I.I2C_DutyCycle= I2C_DutyCycle_2;
	I.I2C_Mode= I2C_Mode_I2C;
	I.I2C_OwnAddress1=0x00;
	I.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1,&I);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	I.I2C_Ack= I2C_Ack_Enable;
	I.I2C_ClockSpeed= 100000;
	I.I2C_DutyCycle= I2C_DutyCycle_2;
	I.I2C_Mode= I2C_Mode_I2C;
	I.I2C_OwnAddress1=0x01;
	I.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
	I2C_Cmd(I2C2,ENABLE);
	I2C_Init(I2C2,&I);
}

void i2c_stop(I2C_TypeDef* I2Cx)
{
 	I2C_GenerateSTOP(I2Cx, ENABLE);
 	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));
}

int main(void)
{
	gpio();
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1 , ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1 , DISABLE);
	i2c();
	uint8_t rec_data=0x00;
	while(1)
	{
		I2C_GenerateSTART(I2C1,ENABLE);
		while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_SB));
		//while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));

		I2C_Send7bitAddress(I2C1,SLA_ADD<<1,I2C_Direction_Transmitter);
		GPIO_SetBits(GPIOD,GPIO_Pin_12);
		//I2C_SendData(I2C1, (SLA_ADD << 1) | 0);
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
		GPIO_SetBits(GPIOD,GPIO_Pin_13);
		I2C_SendData(I2C1,0x20);
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
		GPIO_SetBits(GPIOD,GPIO_Pin_14);
		i2c_stop(I2C1);

		//SLA_ADD=SLA_ADD<<1;
		I2C_AcknowledgeConfig(I2C2, ENABLE);
		while (I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
		I2C_GenerateSTART(I2C2,ENABLE);
		while (!I2C_GetFlagStatus(I2C1,I2C_FLAG_SB));


		I2C_Send7bitAddress(I2C2,SLA_ADD,I2C_Direction_Receiver);

		//I2C_SendData(I2C2, (SLA_ADD << 1) | 1);
		while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

		while( !I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) );
		uint8_t data = I2C_ReceiveData(I2C2);
		if(data==0x20)
		GPIO_SetBits(GPIOD,GPIO_Pin_14);
		rec_data=data;
		i2c_stop(I2C2);
		if(rec_data==0x01)
			GPIO_SetBits(GPIOD,GPIO_Pin_15);
	}
}
