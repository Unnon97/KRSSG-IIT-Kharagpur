#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
GPIO_InitTypeDef GP;
EXTI_InitTypeDef EX;
NVIC_InitTypeDef NV;
void GPIO1()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GP.GPIO_Pin=GPIO_Pin_12;
	GP.GPIO_Mode=GPIO_Mode_OUT;
	GP.GPIO_OType=GPIO_OType_PP;
	GP.GPIO_Speed=GPIO_Speed_50MHz;
	GP.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD,&GP);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	GP.GPIO_Pin=GPIO_Pin_0;
	GP.GPIO_Mode=GPIO_Mode_IN;
	GP.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GP);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	EX.EXTI_Line = EXTI_Line0;
	EX.EXTI_Mode = EXTI_Mode_Interrupt;
	EX.EXTI_Trigger = EXTI_Trigger_Rising;
	EX.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EX);

	NV.NVIC_IRQChannel = EXTI0_IRQn;
    NV.NVIC_IRQChannelPreemptionPriority = 0;
	NV.NVIC_IRQChannelSubPriority = 1;
	NV.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NV);
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
	    EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

int main(void)
{
	GPIO1();
	while(1)
	{

	}
}
