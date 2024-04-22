#include "motor.h"

motor motor1(2, 4);
motor motor2(3, 5);

void setup() {
    // Begin serial monitors
    Serial.begin(115200);

    // Initialize
    motor1.begin(motor1.aPin, motor1.bPin);
    motor2.begin(motor2.aPin, motor2.bPin);
}

void loop() {
    // Calculate shaft position
    motor1.calcPosition();
    motor2.calcPosition();

    // Print Data
    Serial.print(motor1.position);
    Serial.print(" || ");
    Serial.println(motor2.position);
    delay(10);
}