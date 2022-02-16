/*
 * PWM.c
 *
 * Created: 2/23/2016 12:48:45 PM
 *  Author: Dheeraj
 */ 


#include <avr/io.h>
#include <util/delay.h>

void main()
{
	int brightness;
	TCCR0 |= (1<<WGM00)|(1<<COM01)|(1<<WGM01)|(1<<CS00);
	DDRB = 0x04;
	while(1)
	{
		for (brightness = 0; brightness < 255; ++brightness)
		{
			OCR0 = brightness;
			_delay_ms(50);
		}
	
		for (brightness = 255; brightness > 0; --brightness)
		{
			OCR0 = brightness;
			_delay_ms(50);
		}
		
	}
}
