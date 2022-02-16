#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
GPIO_InitTypeDef GP;
NVIC_InitTypeDef N;
TIM_TimeBaseInitTypeDef T;
void gpio1()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GP.GPIO_Pin=GPIO_Pin_13;
	GP.GPIO_Mode=GPIO_Mode_OUT;
	GP.GPIO_OType=GPIO_OType_PP;
	GP.GPIO_Speed=GPIO_Speed_100MHz;
	GP.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD,&GP);

}
void tim()
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			//describes the port they are connected to
	T.TIM_Prescaler = 84000;
	T.TIM_Period = 1000-1;
	T.TIM_ClockDivision = TIM_CKD_DIV1;
	T.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &T);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);

}
void TIM2_IRQHandler()
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{

		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
	}
}
void nvic1()
{
	N.NVIC_IRQChannel=TIM2_IRQn;
	N.NVIC_IRQChannelPreemptionPriority = 1;
	N.NVIC_IRQChannelSubPriority = 1;
	N.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&N);
}

int main(void)
{
	nvic1();
	tim();
	gpio1();
	 TIM_SetCounter(TIM2,0);
	while(1);
}
