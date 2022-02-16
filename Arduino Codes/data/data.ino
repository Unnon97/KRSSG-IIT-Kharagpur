#include "I2Cdev.h"
#include "MPU6050.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;

// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
//#define OUTPUT_READABLE_ACCELGYRO

// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
#define OUTPUT_BINARY_ACCELGYRO


#define LED_PIN 13
bool blinkState = false;

int acc_ex = A8;  int acc_ey = A9;  int acc_ez = A10;                                     //Elbow Accelero
int acc_sx = A13; int acc_sy = A12; int acc_sz = A11;                                     //Shoulder Accelero
int flex1 = A0; int flex2 = A1; int flex3 = A2; int flex4 = A3; int flex5 = A4;           //Flex Sensors

void setup() {
                                                                                          // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    Serial.begin(38400);
    accelgyro.initialize();
                                                                                                  // use the code below to change accel/gyro offset values
                                                                                                  /*
                                                                                                  Serial.println("Updating internal sensor offsets...");
                                                                                                  // -76	-2359	1688	0	0	0
                                                                                                  Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
                                                                                                  Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
                                                                                                  Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
                                                                                                  Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
                                                                                                  Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
                                                                                                  Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
                                                                                                  Serial.print("\n");
                                                                                                  accelgyro.setXGyroOffset(220);
                                                                                                  accelgyro.setYGyroOffset(76);
                                                                                                  accelgyro.setZGyroOffset(-85);
                                                                                                  Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
                                                                                                  Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
                                                                                                  Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
                                                                                                  Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
                                                                                                  Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
                                                                                                  Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
                                                                                                  Serial.print("\n");
                                                                                                  */
                                                                                              
                                                                                                  // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
    pinMode(acc_ex, INPUT);    pinMode(acc_ey, INPUT);    pinMode(acc_ez, INPUT);
    pinMode(acc_sx, INPUT);    pinMode(acc_sy, INPUT);    pinMode(acc_sz,INPUT);

    pinMode(flex1,INPUT); pinMode(flex2,INPUT); pinMode(flex3,INPUT); pinMode(flex4,INPUT); pinMode(flex5,INPUT);
    
    
}

void loop() {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    ae_x = analogRead(acc_ex); ae_y = analogRead(acc_ey); ae_z = analogRead(acc_ez);
    as_x = analogRead(acc_sx); as_y = analogRead(acc_sy); as_z = analogRead(acc_sz);

    #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
        Serial.print("a/g:\t");
        Serial.print(ax); Serial.print(",");
        Serial.print(ay); Serial.print(",");
        Serial.print(az); Serial.print(",");
        Serial.print(gx); Serial.print(",");
        Serial.print(gy); Serial.print(",");
        Serial.print(gz); Serial.print(",");
    #endif
     
        Serial.print(f1); Serial.print(",");
        Serial.print(f2); Serial.print(",");
        Serial.print(f3); Serial.print(",");
        Serial.print(f4); Serial.print(",");
        Serial.print(f5); Serial.print(",");

        Serial.print(ae_x); Serial.print(",");
        Serial.print(ae_y); Serial.print(",");
        Serial.print(ae_z); Serial.print(",");

        Serial.print(as_x); Serial.print(",");
        Serial.print(as_y); Serial.print(",");
        Serial.println(as_z);        

    #ifdef OUTPUT_BINARY_ACCELGYRO
        Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
        Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
        Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
        Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
        Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
        Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
    #endif

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}
