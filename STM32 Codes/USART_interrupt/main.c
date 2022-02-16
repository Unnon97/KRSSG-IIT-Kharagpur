#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx_usart.h>
#include "misc.h"
#define pld 26
#define chnl 5
#define TRUE 1
#define FALSE 0
volatile int velocity[5] = {0};
volatile int dribbler = 0;
int bot_id;
int i=0;
int flag=0;
int BotData[8]={0},count=0,c=0,duty,pulse_l,temp,x,pwm;
int binaryNumber[8]={0};
int temp=0;
int j=8;

void init_kicker()
{
	GPIO_InitTypeDef  GPIO_InitStructure;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
}
void init_botid()
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

 	bot_id = ((GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)*8) + (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)*4) + (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)*2) + GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5));
 	if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)){
 		GPIO_SetBits(GPIOE,GPIO_Pin_0);
 	}
 	if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)){
 	 	GPIO_SetBits(GPIOE,GPIO_Pin_1);
 	}


}

void GPIOLED_TEST()
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}
void GPIOB_Motors()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1| GPIO_Pin_0 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void GPIOE_Motors()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_7|GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}
void setFWDbit(int motorID, int value)
{
	switch (motorID){
		case 1:
			if(value==1){
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
			}else if(value==0){
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);
			}break;
		case 2:
			if(value==1){
				GPIO_SetBits(GPIOE, GPIO_Pin_7);
			}else if(value==0){
				GPIO_ResetBits(GPIOE, GPIO_Pin_7);
			}break;
		case 3:
			if(value==1){
				GPIO_SetBits(GPIOE, GPIO_Pin_9);
			}else if(value==0){
				GPIO_ResetBits(GPIOE, GPIO_Pin_9);
			}break;
		case 4:
			if(value==1){
				GPIO_SetBits(GPIOE, GPIO_Pin_11);
			}else if(value==0){
				GPIO_ResetBits(GPIOE, GPIO_Pin_11);
			}break;
		case 5:
			if(value==1){
				GPIO_SetBits(GPIOE, GPIO_Pin_13);
			}else if(value==0){
				GPIO_ResetBits(GPIOE, GPIO_Pin_13);
			}break;
	}
}
void setBKDbit(int motorID, int value)
{
	switch (motorID){
		case 1:
			if(value==1){
				GPIO_SetBits(GPIOB, GPIO_Pin_1);
			}else if(value==0){
				GPIO_ResetBits(GPIOB, GPIO_Pin_1);
			}break;
		case 2:
			if(value==1){
				GPIO_SetBits(GPIOE, GPIO_Pin_8);
			}else if(value==0){
				GPIO_ResetBits(GPIOE, GPIO_Pin_8);
			}break;
		case 3:
			if(value==1){
				GPIO_SetBits(GPIOE, GPIO_Pin_10);
			}else if(value==0){
				GPIO_ResetBits(GPIOE, GPIO_Pin_10);
			}break;
		case 4:
			if(value==1){
				GPIO_SetBits(GPIOE, GPIO_Pin_12);
			}else if(value==0){
				GPIO_ResetBits(GPIOE, GPIO_Pin_12);
			}break;
		case 5:
			if(value==1){
				GPIO_SetBits(GPIOE, GPIO_Pin_14);
			}else if(value==0){
				GPIO_ResetBits(GPIOE, GPIO_Pin_14);
			}break;
	}
}

void pwmToWheels_init()
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
		/* Time base configuration */
		TIM_TimeBaseStructure.TIM_Period = 127;
		TIM_TimeBaseStructure.TIM_Prescaler = 131;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
		TIM_OC1Init(TIM4, &TIM_OCInitStructure);
		TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
		/* PWM1 Mode configuration: Channel2 */
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0;
		TIM_OC2Init(TIM4, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
		/* PWM1 Mode configuration: Channel3 */
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0;
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
		/* PWM1 Mode configuration: Channel4 */
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0;
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
		TIM_ARRPreloadConfig(TIM4, ENABLE);
		/* TIM4 enable counter */
		TIM_Cmd(TIM4, ENABLE);
}
void pwmToWheels_set(int channel, int duty_cycle)
{
	switch (channel){
		case 1: TIM4->CCR1 = duty_cycle; break;
		case 2: TIM4->CCR2 = duty_cycle; break;
		case 3: TIM4->CCR3 = duty_cycle; break;
		case 4: TIM4->CCR4 = duty_cycle; break;
	}
}
void pwmToDribbler_init()
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_TIM2);
		/* Time base configuration */
		TIM_TimeBaseStructure.TIM_Period = 255;
		TIM_TimeBaseStructure.TIM_Prescaler = 66;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
		TIM_OC1Init(TIM2, &TIM_OCInitStructure);
		TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
		/* PWM1 Mode configuration: Channel3 */
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0;
		TIM_OC3Init(TIM2, &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
		TIM_ARRPreloadConfig(TIM2, ENABLE);
		/* TIM2 enable counter */
		TIM_Cmd(TIM2, ENABLE);
}
void pwmToDribbler_set(int duty_cycle)
{
	TIM2->CCR3 = duty_cycle;
}


void usart()
{
	GPIO_InitTypeDef gpio_usart;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	gpio_usart.GPIO_Mode=GPIO_Mode_AF;
	gpio_usart.GPIO_OType=GPIO_OType_PP;
	gpio_usart.GPIO_Pin=GPIO_Pin_11;    //usart 4 pC11 is a RX
	gpio_usart.GPIO_PuPd=GPIO_PuPd_UP;
	gpio_usart.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&gpio_usart);
	//GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART4);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	USART_InitTypeDef usart;
	usart.USART_BaudRate=9600;
	usart.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	usart.USART_Mode=USART_Mode_Rx;
	usart.USART_Parity=USART_Parity_No;
	usart.USART_StopBits=USART_StopBits_1;
	usart.USART_WordLength=USART_WordLength_8b;

	USART_Init(UART4, &usart);
	USART_Cmd(UART4, ENABLE);

}
int delay=0;
void kicker(){
	GPIO_SetBits(GPIOD,GPIO_Pin_0);
	GPIO_SetBits(GPIOE,GPIO_Pin_1);
	for(delay=0;delay<10000;delay+=1){}
	GPIO_ResetBits(GPIOE,GPIO_Pin_1);
	GPIO_ResetBits(GPIOD,GPIO_Pin_0);
}

void dribblerrun(){
		pwmToDribbler_set(128);
		setBKDbit(5,1);
		setFWDbit(5,0);

}
int main(void)
	{
		init_kicker();

		GPIOB_Motors();
		GPIOE_Motors();
		GPIOLED_TEST();
	    init_botid();
		usart();
		pwmToWheels_init();
		pwmToDribbler_init();
		while(1)
		{
			while(count<8){
			 {if(c>7) c=0;
			 else{
		     	if(USART_GetFlagStatus(UART4,USART_FLAG_RXNE)!=RESET){
		     	temp=USART_ReceiveData(UART4);
		     	BotData[c]=temp;
		     	count++;
		     	USART_ClearFlag(UART4,USART_FLAG_RXNE);
		     	c++;
		     	j=0;
		     	}}}
			}
		     	//if(BotData[0]==255){GPIO_SetBits(GPIOD,GPIO_Pin_14);}
		     	//USART_SendData(USART1,'A');
			count=0;

			if((BotData[0]==1)&&(BotData[1]==1)){
				if(BotData[6]==1){kicker();}
				if(BotData[7]==1){dribblerrun();}
				else{
					pwmToDribbler_set(20);
					setBKDbit(5,1);
					setFWDbit(5,0);
				}
			if(BotData[2]<=127 && BotData[2]>=0){
				if(BotData[2]==0){
					setFWDbit(1,0);
					setBKDbit(1,1);
					pwmToWheels_set(1,10);
				}
				else{
					pwm = 13+(BotData[2]*100)/126;
					setFWDbit(1,0);
					setBKDbit(1,1);
					pwmToWheels_set(1,pwm);}
			}


						else{
							if(BotData[2]==255){
								setFWDbit(1,1);
								setBKDbit(1,0);
								pwmToWheels_set(1,10);
							}
							else{
							BotData[2]=255-BotData[2];
							pwm = 13+(BotData[2]*100)/126;
							setFWDbit(1,1);
							setBKDbit(1,0);
							pwmToWheels_set(1,pwm);
							}
						}



			if(BotData[3]<=127||BotData[3]>=0){

				if(BotData[3]==0){
					setFWDbit(2,0);
					setBKDbit(2,1);
					pwmToWheels_set(2,10);
				}
				else{
				pwm = 13+(BotData[3]*100)/126;
				setFWDbit(2,0);
				setBKDbit(2,1);
				pwmToWheels_set(2,pwm);}

			}
			else{
				if(BotData[3]==255){
					setFWDbit(2,1);
					setBKDbit(2,0);
					pwmToWheels_set(2,10);
				}
				else{
				BotData[3]=255-BotData[3];
				pwm = 13+(BotData[3]*100)/126;
				setFWDbit(2,1);
				setBKDbit(2,0);
				pwmToWheels_set(2,pwm);}

			}

			if(BotData[4]<=127||BotData[4]>=0){

							if(BotData[4]==0){
								setFWDbit(3,0);
								setBKDbit(3,1);
								pwmToWheels_set(3,10);
							}
							else{
							pwm = 13+(BotData[4]*100)/126;
							setFWDbit(3,0);
							setBKDbit(3,1);
							pwmToWheels_set(3,pwm);}

			}
						else{
							if(BotData[4]==255){
								setFWDbit(3,1);
								setBKDbit(3,0);
								pwmToWheels_set(3,10);
							}
							else{
							BotData[4]=255-BotData[4];
							pwm = 13+(BotData[4]*100)/126;
							setFWDbit(3,1);
							setBKDbit(3,0);
							pwmToWheels_set(3,pwm);}

						}

			if(BotData[5]<=127||BotData[5]>=0){

							if(BotData[5]==0){
								setFWDbit(4,0);
								setBKDbit(4,1);
								pwmToWheels_set(4,10);
							}
							else{
							pwm = 13+(BotData[5]*100)/126;
							setFWDbit(4,0);
							setBKDbit(4,1);
							pwmToWheels_set(4,pwm);
							}
						}
						else{
							if(BotData[5]==255){
								setFWDbit(4,0);
								setBKDbit(4,1);
								pwmToWheels_set(4,10);
							}
							else{
							BotData[5]=255-BotData[5];
							pwm = 13+(BotData[5]*100)/126;
							setFWDbit(4,1);
							setBKDbit(4,0);
							pwmToWheels_set(4,pwm);
							}
						}

			}

		}
}
