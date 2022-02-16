/*
 * ADC_motor.c
 *
 * Created: 12/5/2016 3:59:22 PM
 *  Author: Dheeraj
 */ 


#include <avr/io.h>


 main()
{
	DDRC=0b11111111;
	DDRB=0xFF;
	TCCR0|=(1<<WGM01)|(1<<WGM00)|(1<<CS00)|(1<<COM01);
	ADMUX |= 1<<ADLAR;
	ADCSRA|=1<<ADEN|1<<ADPS0|1<<ADPS2;
    while(1)
   {
		ADCSRA|=1<<ADSC;
		PORTC=0x01;
		OCR0=ADCH;
		//while (ADCSRA&(1<<ADSC));
    }
}