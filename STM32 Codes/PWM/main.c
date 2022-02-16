#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
GPIO_InitTypeDef GP;
int i,j;
TIM_TimeBaseInitTypeDef TI;
TIM_OCInitTypeDef P;
void GPIO()
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GP.GPIO_Pin=GPIO_Pin_12;
  GP.GPIO_Mode=GPIO_Mode_AF;
  GP.GPIO_OType=GPIO_OType_PP;
  GP.GPIO_Speed=GPIO_Speed_50MHz;
  GP.GPIO_PuPd=GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD,&GP);
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
void PWMwork(int k)
{
	P.TIM_OCMode = TIM_OCMode_PWM1;
	P.TIM_OutputState = TIM_OutputState_Enable;
	P.TIM_OCPolarity = TIM_OCPolarity_High;
	P.TIM_Pulse = k ;
	TIM_OC1Init(TIM4, &P);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
}

int main(void)
{
    GPIO();
    Tim();


    while(1)
    {
    	for(i=0;i<2000;i++)
    	{
    		PWMwork(i);

    		for(j=0;j<2000;j++);
    	}
    	for(i=2000;i>0;i--)
    	    	{
    			PWMwork(i);
    	    		for(j=0;j<2000;j++);
    	    	}
    }
}
