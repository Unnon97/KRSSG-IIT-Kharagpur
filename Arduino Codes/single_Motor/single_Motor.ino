int MA1 = 50;
int MA2 = 51;
int En = 7;
int led=13;
char data=0;
void setup() {
  pinMode(MA1,OUTPUT);
  pinMode(MA2,OUTPUT);
  pinMode(En,OUTPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  if(Serial.available())
  {
    data=Serial.read();
    if(data == 'G')
    {
      Serial.write(data);
      analogWrite(En, 240);
      digitalWrite(MA1, HIGH);
      digitalWrite(MA2, LOW);
    }
    else if(data == 'O')
    {
      digitalWrite(MA1, LOW);
      digitalWrite(MA2, LOW);
    }
  }
  
 
}
