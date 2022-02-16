#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
GPIO_InitTypeDef GP;
USART_InitTypeDef U;
void usart1()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

	GP.GPIO_Mode= GPIO_Mode_AF;
	GP.GPIO_OType = GPIO_OType_PP;
	GP.GPIO_PuPd = GPIO_PuPd_UP;
	GP.GPIO_Pin = GPIO_Pin_11;
	GP.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GP);

	GP.GPIO_Mode= GPIO_Mode_OUT;
	GP.GPIO_OType = GPIO_OType_PP;
	GP.GPIO_PuPd = GPIO_PuPd_UP;
	GP.GPIO_Pin = GPIO_Pin_13;
	GP.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GP);

	U.USART_BaudRate = 9600 ;
	U.USART_WordLength = USART_WordLength_8b;
	U.USART_StopBits = USART_StopBits_1;
	U.USART_Parity = USART_Parity_No;
	U.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	U.USART_Mode = USART_Mode_Rx;
	USART_Init(USART3, &U);
	USART_Cmd(USART3, ENABLE);
}
int main(void)
{
	usart1();
    while(1)
    {
    	while(USART_GetFlagStatus(USART3,USART_FLAG_TC) != RESET )
    		{
    			GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
    			USART_ClearFlag(USART3,RESET);
    		}


    }
}
