#include "motor.h"

/*
  intialize motor class with inputs
    - motorID
    - gear ratio
    - aPin (encoder A channel)
      - Disclaimer: if you are not using either 2, 18, or 20 for aPin, you need to change motor::begin
    - bPin (encoder B channel)
    - pwmPin (E1 speed control)
    - dirPin (M1 direction control)
    - upperLimit in deg (for free ROM) [has to be positive]
    - lowerLimit in deg (for free ROM) [has to be negative]
    [optional]
      - spring constant (default = 10) 
      - damper ratio (default = 0.35)
*/

motor motor1(1, 10./3, 2, 3, 8, 9, 90, -90);
motor motor2(2, 1, 18, 19, 10, 11, 45, -45);
motor motor3(3, 10./3, 20, 21, 6, 7,   45, -45);


void setup() {
    // Begin serial monitor
    Serial.begin(9600);

    // Change PWM pin frequency to 20kHz
    /*
    TCCR1B &= ~7;
    TCCR1B |= 1;
    TCCR2B &= ~7;
    TCCR2B |= 1;
    TCCR4B &= ~7;
    TCCR4B |= 1;
    */

    // Initialize
    motor1.begin(motor1.aPin, motor1.bPin, motor1.pwmPin, motor1.dirPin);
    motor2.begin(motor2.aPin, motor2.bPin, motor2.pwmPin, motor2.dirPin);
    motor3.begin(motor3.aPin, motor3.bPin, motor3.pwmPin, motor3.dirPin);
}

void loop() {
    // Calculate initial shaft position
    motor1.calcPosition();
    motor2.calcPosition();
    motor3.calcPosition();

    Serial.print(motor1.position);
    Serial.print(" || ");
    Serial.print(motor2.position);
    Serial.print(" || ");
    Serial.println(motor3.position);
}