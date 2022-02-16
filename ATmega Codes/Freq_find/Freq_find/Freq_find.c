/*
 * Freq_find.c
 *
 * Created: 2/24/2016 9:56:17 PM
 *  Author: Dheeraj
 */ 


#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
int cnt=0;
int main(void)
{
	TCCR0A|=1<<CS00|1<<CS00|1<<CS02;
	TIMSK0|=1<<TOIE0;
	sei();
	TCNT0=0;
	while (1)
	{
	}	
	cli();
}
ISR(TIMER0_OVF_vect)
{
	cnt++;
}