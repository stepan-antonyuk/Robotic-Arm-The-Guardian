//Written by Ahmet Burkay KIRNIK
//Measurement of Angle with MPU-6050(GY-521)

#include<Wire.h>
#include <Servo.h>

Servo myservoSH;  // create servo object to control a servo
Servo myservoEL;  // create servo object to control a servo

double smz = 0;
double smy = 0;

double pz0 = 666;
double py0 = 666;

const int MPU_addr=0x68; int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265; 
int maxVal=402;

double x; 
double y; 
double z;


void setup() { 

  myservoSH.attach(9);  // attaches the servo on pin 9 to the servo object
  myservoEL.attach(10);  // attaches the servo on pin 10 to the servo object
  
  Wire.begin(); 
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true); 
  
  Serial.begin(9600); 
  
} 

void loop() { 
  
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x3B); 
  Wire.endTransmission(false); 
  Wire.requestFrom(MPU_addr,14,true); 
  
  AcX=Wire.read()<<8|Wire.read(); 
  AcY=Wire.read()<<8|Wire.read(); 
  AcZ=Wire.read()<<8|Wire.read(); 
  
  int xAng = map(AcX,minVal,maxVal,-90,90); 
  int yAng = map(AcY,minVal,maxVal,-90,90); 
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI); 
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI); 
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

  if(pz0 == 666 and py0 == 666)
  {
      pz0 = z;
      py0 = y;
  }

  smz = z - pz0;
  smy = y - py0;

  myservoSH.write(smy);  
  myservoEL.write(smz);

  Serial.print("AngleX= "); Serial.println(x);

  Serial.print("AngleY= "); Serial.println(y);

  Serial.print("AngleZ= "); Serial.println(z); 

  Serial.print("Z0= "); Serial.println(pz0);

  Serial.print("Y0= "); Serial.println(py0);

  Serial.print("Z= "); Serial.println(smz);

  Serial.print("Y= "); Serial.println(smy);
  
  Serial.println("-----------------------------------------"); 
  
  delay(100); 
  
}
