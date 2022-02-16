#include <avr/io.h>  
#define MOTOR_SPEED 110/2
int LEDPIN = 13;          // Heartbeat led
int MOTOR_DIR = 12;       // Non PWM pin for direction control
int MOTOR_PWM = 11;       // PWM controlled pin.
int int_counter = 0;

void setup() 
{  
Serial.begin(9600);
CLKPR=0;
 // Set the pins to output.
pinMode(LEDPIN, OUTPUT);
pinMode(MOTOR_DIR, OUTPUT);
pinMode(MOTOR_PWM, OUTPUT);
  // And set these to a initial value to make sure.
 digitalWrite(MOTOR_DIR, LOW);
 digitalWrite(MOTOR_PWM, LOW);
 // Use phase correct PWM Mode and set Output Compare mode
 // Eventual PWM fequency will be ~30kHz, this is done to
 // - minimize noise
  // - minimize heat (suturation of motor --> L293=RIP)
 TCCR2A = (0<<WGM21) | (1<<WGM20) | (0<<COM2A1) | (0<<COM2A0) | (0<<COM2B1) | (0<<COM2B0);
 TCCR2B = (0<<WGM22) | (0<<CS22) | (0<<CS21) | (1<<CS20) | (0<<FOC2A) | (0<<FOC2B);
 //Timer2 Overflow Interrupt Enable for the heartbeat
 TIMSK2 |= (1<<TOIE2) | (0<<OCIE2A);
 //sei();  // Not needed at this moment.
}  


void motor_stop()
{
 // Disconnect the PWM
TCCR2A &= ~((1<<COM2A1) | (1<<COM2A0));
  // put is all back to a safe 'LOW'
digitalWrite(MOTOR_DIR, LOW);
digitalWrite(MOTOR_PWM, LOW);  
}


void motor_right() 
{
 // Set the pulse width
OCR2A=MOTOR_SPEED;
 // Set the directional bit to the correct value
digitalWrite(MOTOR_DIR, LOW);
 // Set output to PWM (inverted of motor_left function)
TCCR2A |= ((1<<COM2A1) | (0<<COM2A0));
}


void motor_left() 
{
  // Set the pulse width
 OCR2A=MOTOR_SPEED;
  // Set the directional bit to the correct value
 digitalWrite(MOTOR_DIR, HIGH);
 // Set output to PWM
 TCCR2A |= ((1<<COM2A1) | (1<<COM2A0));
}


void loop()
{  
motor_left();
delay(1000);
motor_stop();

motor_right();
delay(1000);
motor_stop();
}

