/*
 * USART.c
 *
 * Created: 2/26/2016 8:09:55 PM
 *  Author: Dheeraj
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

#define BAUD 9600
#include <util/setbaud.h>
#include <util/delay.h>
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)         

volatile char val;

void ini()
{
	UBRR0H=UBRRH_VALUE;
	UBRR0L=UBRRL_VALUE;
	UCSR0B|=1<<TXEN0|1<<RXEN0;
	UCSR0C|=1<<UCSZ00|1<<USBS0;
}	

void Send_data(uint8_t val)
{
	while((UCSR0A & (1<<UDRE0))==0);
	UDR0=val;
}

int main(void)
{
	ini();
	val='A';
	while (1)
	{
		Send_data(val);
		_delay_ms(1000);
	}
}