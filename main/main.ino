#include "motor.h"

/*
  intialize motor class with inputs (aPin, bPin, pwmPin, dirPin, spring_constant, damper_ratio)
*/
motor motor1(2, 3, 8, 9, 10, 0.35);
motor motor2(19, 18, 10, 11, 10, 0.35);

void setup() {
    // Begin serial monitors
    Serial.begin(115200);

    // Initialize
    motor1.begin(motor1.aPin, motor1.bPin, motor1.pwmPin, motor1.dirPin);
    motor2.begin(motor2.aPin, motor2.bPin, motor2.pwmPin, motor2.dirPin);
}

void loop() {
    // Calculate shaft position
    motor1.calcPosition();
    motor2.calcPosition();

    // Do Haptic Stuff
    // smotor1.calcTorqueOutput();
    motor2.calcTorqueOutput();
}