#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "stm32f4xx_tim.h"
GPIO_InitTypeDef GP;
NVIC_InitTypeDef NV;
TIM_TimeBaseInitTypeDef TI;
TIM_OCInitTypeDef P;
void gpio()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GP.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GP.GPIO_Mode=GPIO_Mode_AF;
	GP.GPIO_OType=GPIO_OType_PP;
	GP.GPIO_Speed=GPIO_Speed_50MHz;
	GP.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&GP);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GP.GPIO_Pin=GPIO_Pin_14|GPIO_Pin_15;
	GP.GPIO_Mode=GPIO_Mode_OUT;
	GP.GPIO_OType=GPIO_OType_PP;
	GP.GPIO_Speed=GPIO_Speed_50MHz;
	GP.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&GP);
}
void Tim()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TI.TIM_Prescaler = 42-1;
	TI.TIM_Period= 2000-1;
	TI.TIM_CounterMode = TIM_CounterMode_Up;
	TI.TIM_ClockDivision = TIM_CKD_DIV1;
	TI.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TI);
	TIM_Cmd(TIM4, ENABLE);
}
void PWMwork()
{

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	P.TIM_OCMode = TIM_OCMode_PWM1;
	P.TIM_OutputState = TIM_OutputState_Enable;
	P.TIM_OCPolarity = TIM_OCPolarity_High;
	P.TIM_Pulse = 0 ;
	TIM_OC1Init(TIM4, &P);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	GPIO_SetBits(GPIOB,GPIO_Pin_15);
	P.TIM_OCMode = TIM_OCMode_PWM1;
	P.TIM_OutputState = TIM_OutputState_Enable;
	P.TIM_OCPolarity = TIM_OCPolarity_High;
	P.TIM_Pulse = 1000 ;
	TIM_OC1Init(TIM4, &P);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
}

int main(void)
{
	gpio();
	Tim();
	while(1)
    {
		PWMwork();
    }
}
