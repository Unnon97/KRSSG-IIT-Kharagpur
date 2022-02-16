/*
 * GPIO.c
 *
 * Created: 2/12/2016 12:20:27 AM
 *  Author: Dheeraj
 */ 


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA=0xFF;
	while(1)
	{
		PORTA=0xFF;
		_delay_ms(1000);
		PORTA=0x00;
		_delay_ms(1000);
		/*for(int i=1;i<9;i++)
		{
			PORTB=1<<i;
			_delay_ms(1000);
		}*/
	}
}
