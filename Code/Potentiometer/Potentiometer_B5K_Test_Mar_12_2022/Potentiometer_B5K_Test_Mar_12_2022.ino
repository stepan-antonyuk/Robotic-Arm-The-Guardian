#include <Servo.h>

Servo myservoTest;  // create servo object to control a servo

// the setup routine runs once when you press reset:
void setup() {

  myservoTest.attach(6);  // attaches the servo on pin 9 to the servo object
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);

  int degreeGuess = map(sensorValue, 140, 840, 0, 180);
  Serial.println(degreeGuess);

  Serial.println("______________________________________");

  myservoTest.write(degreeGuess);
  
  delay(1);        // delay in between reads for stability
}

