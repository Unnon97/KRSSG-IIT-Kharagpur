#include "stm32f4xx.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
GPIO_InitTypeDef GP;
I2C_InitTypeDef I;
#define SLAVE_ADDRESS 0x01
int i;
void gpio()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GP.GPIO_OType = GPIO_OType_OD;
	GP.GPIO_PuPd = GPIO_PuPd_UP;
	GP.GPIO_Mode = GPIO_Mode_AF;
	GP.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6;
	GP.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GP);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GP.GPIO_Mode= GPIO_Mode_OUT;
	GP.GPIO_OType = GPIO_OType_PP;
	GP.GPIO_PuPd = GPIO_PuPd_UP;
	GP.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
	GP.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GP);
}
void i2c()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	I.I2C_Ack= I2C_Ack_Enable;
	I.I2C_ClockSpeed= 100000;
	I.I2C_DutyCycle= I2C_DutyCycle_2;
	I.I2C_Mode= I2C_Mode_I2C;
	I.I2C_OwnAddress1=0x01;
	I.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
	I2C_Cmd(I2C1,ENABLE);
	I2C_Init(I2C1,&I);
}
void i2c_startrec(uint8_t Address,uint8_t direction)
{
	I2C_GenerateSTART(I2C2,ENABLE);

	I2C_Send7bitAddress(I2C2,Address,direction);

	if (direction == I2C_Direction_Receiver)
		while(!I2C_CheckEvent(I2C2,I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED));

}
uint8_t i2c_read_ack()
{
	I2C_AcknowledgeConfig(I2C2, ENABLE);
 	while( !I2C_CheckEvent(I2C2, I2C_EVENT_SLAVE_BYTE_RECEIVED) );
 	uint8_t data = I2C_ReceiveData(I2C2);
 	return data;
}
void i2c_stop(I2C_TypeDef* I2Cx)
{
 	I2C_GenerateSTOP(I2Cx, ENABLE);
}

int main(void)
{
	gpio();
	i2c();
	uint8_t rec_data=0;
    	/*i2c_startsend(SLAVE_ADDRESS, I2C_Direction_Transmitter);
    	i2c_write(0x20);
    	i2c_stop(I2C1);*/

    	i2c_startrec(SLAVE_ADDRESS,I2C_Direction_Receiver);
    	rec_data = i2c_read_ack();
    	i2c_stop(I2C2);
    	if(rec_data!=0)
    	{
        	GPIO_SetBits(GPIOD,GPIO_Pin_12);
        	for(i=0;i<1000;i++);
    	}
}
