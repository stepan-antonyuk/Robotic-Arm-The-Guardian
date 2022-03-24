#include "MPU9250.h"

MPU9250 mpu;
const int CS0 = 4;


void setup() {

    pinMode(CS0, OUTPUT);
    //digitalWrite(CS0, LOW);
  
    Serial.begin(115200);
    Wire.begin();
    delay(2000);

    if (!mpu.setup(0x69)) {  // change to your own address
        while (1) {
            Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
            delay(100);
        }
    }
    //digitalWrite(CS0, HIGH);
}

void loop() {
    //digitalWrite(CS0, LOW);
    if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 25) {
            print_roll_pitch_yaw();
            prev_ms = millis();
        }
    }
    //digitalWrite(CS0, HIGH);
}

void print_roll_pitch_yaw() {
    Serial.print("Yaw, Pitch, Roll: ");
    Serial.print(mpu.getYaw(), 2);
    Serial.print(", ");
    Serial.print(mpu.getPitch(), 2);
    Serial.print(", ");
    Serial.println(mpu.getRoll(), 2);
}
