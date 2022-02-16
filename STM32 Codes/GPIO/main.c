#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
int i;
GPIO_InitTypeDef GP;   	//GPIO structure to access each pin
void main()												//Function that chooses the pin operation method
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GP.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13;  //Enabling led pins
  GP.GPIO_Mode=GPIO_Mode_OUT;									//specifying the pin as output type
  GP.GPIO_OType=GPIO_OType_PP;									//
  GP.GPIO_Speed=GPIO_Speed_50MHz;							    //
  GP.GPIO_PuPd=GPIO_PuPd_NOPULL;						//
  GPIO_Init(GPIOE,&GP);											//Passes the structure settings to one of the pinout type

  while(1)
  {

	 // for(i=0;i<840000;i++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_13);
	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
	//GPIO_SetBits(GPIOD,GPIO_Pin_14);
  }
}
