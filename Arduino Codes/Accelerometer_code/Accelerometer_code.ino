/*
ADXL335
note:vcc-->5v ,but ADXL335 Vs is 3.3V
The circuit:
   5V: VCC
analog 0: x-axis
analog 1: y-axis
analog 2: z-axis
*/
int LEDpin = 13;
float X,Y;
const int xpin = A10;                  // x-axis of the accelerometer
const int ypin = A9;                  // y-axis
const int zpin = A8;                  // z-axis (only on 3-axis models)
void setup()
{
 Serial.begin(9600);
 pinMode(LEDpin,OUTPUT);
}

void loop()
{
  int x = 0;int y = 0;int z = 0;
 x = analogRead(xpin);  //read from xpin
 delay(1); //
 y = analogRead(ypin);  //read from ypin
 delay(1);  
 z = analogRead(zpin);  //read from zpin
 float zero_G = 512.0; //ADC is 0~1023  the zero g output equal to Vs/2
                      //ADXL335 power supply by Vs 3.3V
 float scale = 102.3;  //ADXL335330 Sensitivity is 330mv/g
 X=((float)x - 331.5)/65*9.8;
Y=((float)y - 329.5)/68.5*9.8;                      //330 * 1024/3.3/1000  
Serial.print(x); 
Serial.print("\t");
Serial.print(y);
Serial.print("\t");
Serial.print(z);  
Serial.print("\t");
Serial.print(X); 
Serial.print("\t");
Serial.print(Y);
Serial.print("\n");
X=((float)x - 331.5)/65*9.8;
Y=((float)y - 329.5)/68.5*9.8;
//map(0.5,1,0,1024);
/*Serial.print(X);  //print x value on serial monitor
Serial.print("\t");
Serial.print(Y);  //print y value on serial monitor
Serial.print("\t");
Serial.print(((float)z - 340)/68*9.8);  //print z value on serial monitor
Serial.print("\n");*/
delay(100);  //wait for 1 second 

//if(X<(-0.5))
//{
//  digitalWrite(LEDpin,HIGH);
//  delay(500);
//  digitalWrite(LEDpin,LOW);
//  delay(500);
//}
//
//
//if(X>0.5)
//{
//  digitalWrite(LEDpin,HIGH);
//  delay(2000);
//  digitalWrite(LEDpin,LOW);
//  delay(2000);
//}
} 




