/*
 * Duty_cycle.c
 *
 * Created: 2/24/2016 9:34:45 PM
 *  Author: Dheeraj
 */ 


#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	DDRB=0xff;
	TCCR0A=TCCR0A|1<<WGM00|1<<WGM01|1<<WGM02|1<<COM0A1;
	TCCR0B=TCCR0B|1<<CS00|1<<CS01;
    while(1)
    {
     for (OCR0A=0;OCR0A<255;OCR0A+=51)
     {
	   _delay_ms(2000);	 
     }
	 /*for (OCR0A=255;OCR0A>0;OCR0A-=51)
	 {
		 _delay_ms(2000);
	 }*/
    }
return 0;
}