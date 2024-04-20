#include "motor.h"

motor motor1(2, 4, 0, 0, 0, 0);
motor motor2(3, 5, 0, 0, 0, 0);

void setup() {
    // Begin serial monitors
    Serial.begin(9600);

    // Initialize
    motor1.encoderPinInit();
    motor2.encoderPinInit();
}

void loop() {
    // Calculate shaft position
    motor1.calcPosition();
    Serial.println(motor1.position);

    delay(100);

    motor2.calcPosition();
    Serial.println(motor2.position);

    delay(100);
}