#include <Wire.h>
HardwareSerial serial(1);

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  setupMPU();
}

void loop() {
  // put your main code here, to run repeatedly:
  recordAccelRegisters();
  recordGyroRegisters();
  printData();
  delay(100);
}


void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000);//I2C address of the MPU
  Wire.write(0x3B);//accessing the register for accel reading
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); //request accel registers (3B - 40)
  while (Wire.available() < 6);
  accelX = Wire.read() << 8 | Wire.read(); //store firt 2 bytesrecordGyroRegisters
  accelY = Wire.read() << 8 | Wire.read(); //store middle 2 bytes
  accelZ = Wire.read() << 8 | Wire.read(); //store last 2 bytes
  processAccelData();
}

void processAccelData() 
{
  gForceX = accelX / 16384.0;
  Serial.print(gForceX);
  gForceY = accelY / 16384.0;
  gForceZ = accelZ / 16384.0;
}

void recordGyroRegisters() 
{
  Wire.beginTransmission(0b1101000);
  Wire.write(0x43);//starting register for Gyro readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); //request Gyro registers (43 - 48)
  while (Wire.available() < 6);
  gyroX = Wire.read() << 8 | Wire.read(); //store firt 2 bytes
  gyroY = Wire.read() << 8 | Wire.read(); //store middle 2 bytes
  gyroZ = Wire.read() << 8 | Wire.read(); //store last 2 bytes
  processGyroData();
}

void processGyroData() 
{
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0;
  rotZ = gyroZ / 131.0;
}

void printData() {
  Serial.print("\n\nGyro (deg)");
  Serial.print("\nX=");
  Serial.print(rotX);
  Serial.print("\nY=");
  Serial.print(rotY);
  Serial.print("\nZ=");
  Serial.print(rotZ);
  Serial.print("\n\nAccel (g)");
  Serial.print("\nX=");
  Serial.print(gForceX);
  Serial.print("\nY=");
  Serial.print(gForceY);
  Serial.print("\nZ=");
  Serial.print(gForceZ);

  delay(2000);
}
