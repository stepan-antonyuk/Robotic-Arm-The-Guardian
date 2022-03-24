//Written by Ahmet Burkay KIRNIK
//Measurement of Angle with MPU-6050(GY-521)

#include<Wire.h>
#include <Servo.h>

Servo myservoSH;  // create servo object to control a servo
Servo myservoEL;  // create servo object to control a servo

const int MPU_addr1 = 0x68; int16_t AcX1, AcY1, AcZ1, Tmp1, Gyx1, GyY1, GyZ1;
const int MPU_addr2 = 0x69; int16_t AcX2, AcY2, AcZ2, Tmp2, Gyx2, GyY2, GyZ2;

int minVal = 265; int maxVal = 402;

double x1; double y1; double z1;
double x2; double y2; double z2;


void setup() {

  myservoSH.attach(9);  // attaches the servo on pin 9 to the servo object
  myservoEL.attach(10);  // attaches the servo on pin 10 to the servo object

  Wire.begin();
  Wire.beginTransmission(MPU_addr1);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Wire.begin();
  Wire.beginTransmission(MPU_addr2);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.begin(115200);

}

void loop() {

  Set_up_AC1();
  Set_up_AC2();

  if(x2 >= 180 and x2 < 270) {
    x2 = 180;  
  }
  else if(x2 >= 270) {
    x2 = 0;
  }

  if(x1 >= 180 and x1 < 270) {
    x1 = 180;  
  }
  else if(x1 >= 270) {
    x1 = 0;
  }

  Serial.print("BAngleX1= "); Serial.println(x1);

  x1 = map(x1, 0, 180, 17, 180);

  myservoSH.write(x1);
//  myservoEL.write(x2);
//  myservoSH.write(17);
//  delay(5000);
//  myservoSH.write(90);
//  delay(5000);
//  myservoSH.write(180);
//  delay(5000);
  

  //Serial.print("AngleX= "); Serial.println(x);

  //Serial.print("AngleY= "); Serial.println(y);

  Serial.print("AAngleX1= "); Serial.println(x1);
//  Serial.print("AngleY1= "); Serial.println(y1);
  
  //Serial.print("AngleZ2= "); Serial.println(x2);
  Serial.println("-----------------------------------------");

  delay(100);

}

void Set_up_AC1() {

  Wire.beginTransmission(MPU_addr1);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr1, 14, true);

  AcX1 = Wire.read() << 8 | Wire.read();
  AcY1 = Wire.read() << 8 | Wire.read();
  AcZ1 = Wire.read() << 8 | Wire.read();

  int xAng1 = map(AcX1, minVal, maxVal, -90, 90);
  int yAng1 = map(AcY1, minVal, maxVal, -90, 90);
  int zAng1 = map(AcZ1, minVal, maxVal, -90, 90);

  x1 = RAD_TO_DEG * (atan2(-yAng1, -zAng1) + PI);
  y1 = RAD_TO_DEG * (atan2(-xAng1, -zAng1) + PI);
  z1 = RAD_TO_DEG * (atan2(-yAng1, -xAng1) + PI);

}

void Set_up_AC2() {

  Wire.beginTransmission(MPU_addr2);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr2, 14, true);

  AcX2 = Wire.read() << 8 | Wire.read();
  AcY2 = Wire.read() << 8 | Wire.read();
  AcZ2 = Wire.read() << 8 | Wire.read();

  int xAng2 = map(AcX2, minVal, maxVal, -90, 90);
  int yAng2 = map(AcY2, minVal, maxVal, -90, 90);
  int zAng2 = map(AcZ2, minVal, maxVal, -90, 90);

  x2 = RAD_TO_DEG * (atan2(-yAng2, -zAng2) + PI);
  y2 = RAD_TO_DEG * (atan2(-xAng2, -zAng2) + PI);
  z2 = RAD_TO_DEG * (atan2(-yAng2, -xAng2) + PI);

}
