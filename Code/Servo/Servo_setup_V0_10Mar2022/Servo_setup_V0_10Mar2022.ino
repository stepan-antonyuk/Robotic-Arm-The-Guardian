//Written by Ahmet Burkay KIRNIK
//Measurement of Angle with MPU-6050(GY-521)

#include<Wire.h>
#include <Servo.h>

Servo myservo1;  // create servo object to control a servo

double x1; double y1; double z1;
double x2; double y2; double z2;


void setup() {

  myservo1.attach(6);  // attaches the servo on pin 10 to the servo object

  Serial.begin(115200);

}

void loop() {

  
  myservo1.write(0);
  Serial.print(myservo1.read());
  Serial.println("     ");
  delay(3000);
  myservo1.write(90);
  Serial.print(myservo1.read());
  Serial.println("     ");
  delay(3000);
  myservo1.write(180);
  Serial.print(myservo1.read());
  Serial.println("     ");
  delay(3000);
  

}
