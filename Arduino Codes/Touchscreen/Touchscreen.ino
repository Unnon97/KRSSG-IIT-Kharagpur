//Define your screen resolution as per your Touch screen (Max: 1024)
int Xresolution=320; //128
int Yresolution=240; //64
int Y1=A0;
int Y2=A1;
int X2=A2;
int X1=A3;
const int trigPin=2;
const int  echoPin=4;
void setup()
{
   Serial.begin(9600);
}

void loop()
{
 
  int X=0,Y=0;
  long duration, inches, cm;

  //Change in X axis
   pinMode(Y1,INPUT);
   pinMode(Y2,INPUT);  
   digitalWrite(Y2,LOW);
   pinMode(X1,OUTPUT);
   digitalWrite(X1,HIGH);
   pinMode(X2,OUTPUT);
   digitalWrite(X2,LOW);
   X = (analogRead(Y1)); 
   
   pinMode(X1,INPUT);
   pinMode(X2,INPUT);
   digitalWrite(X2,LOW);
   pinMode(Y1,OUTPUT);
   digitalWrite(Y1,HIGH);
   pinMode(Y2,OUTPUT);
   digitalWrite(Y2,LOW);
   Y = (analogRead(X1)); 
   
   pinMode(trigPin, OUTPUT); 
   digitalWrite(trigPin, LOW); 
   delayMicroseconds(2); 
   digitalWrite(trigPin, HIGH); 
   delayMicroseconds(10); 
   digitalWrite(trigPin, LOW); 
 
   pinMode(echoPin, INPUT); 
   duration = pulseIn(echoPin, HIGH); 
 
  // convert the time into a distance  
  cm = msToCm(duration); 
 
  //Display X and Y and dist on Serial Monitor
   Serial.print("X = ");  
   Serial.print(X);
   Serial.print(" Y = ");
   Serial.println(Y);
   Serial.print("Dist = ");
   Serial.println(cm);
   delay(100);
}










































































































































 
 
 long msToCm(long microseconds) 
 { 
   // The speed of sound is 340 m/s or 29 microseconds per centimeter. 
   // The ping travels out and back, so to find the distance of the 
   // object we take half of the distance travelled. 
   return microseconds / 29 / 2; 
 } 

