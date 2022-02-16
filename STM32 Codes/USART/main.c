#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
GPIO_InitTypeDef GP;
USART_InitTypeDef U;
void Usart1()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);

	GP.GPIO_Mode= GPIO_Mode_AF;
	GP.GPIO_OType = GPIO_OType_PP;
	GP.GPIO_PuPd = GPIO_PuPd_UP;
	GP.GPIO_Pin = GPIO_Pin_10;
	GP.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GP);

	U.USART_BaudRate = 9600 ;
	U.USART_WordLength = USART_WordLength_8b;
	U.USART_StopBits = USART_StopBits_1;
	U.USART_Parity = USART_Parity_No;
	U.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	U.USART_Mode = USART_Mode_Tx;
	USART_Init(USART3, &U);
	USART_Cmd(USART3, ENABLE);
}

int main(void)
{
	Usart1();
    while(1)
    {
    	USART_SendData(USART3,'A');
    }
}
