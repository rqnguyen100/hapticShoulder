#include "motor.h"

/*
  intialize motor class with inputs
    - motorID
    - gear ratio
      - Disclaimer: must be float if not an integer
    - aPin (encoder A channel)
      - Disclaimer: must verify begin() switch statement is consistent with pins
    - bPin (encoder B channel)
    - pwmPin (E1 speed control)
    - dirPin (M1 direction control)
    - upperLimit in deg (for free ROM) [has to be positive]
    - lowerLimit in deg (for free ROM) [has to be negative]
    [optional]
      - spring constant (default = 10) 
      - damper ratio (default = 0.35)
*/

motor motor1(1, 10./3,  2,  3, 9, 10, 10, -10);
motor motor2(2, 10./3, 19, 15, 7, 42, 20, -20);
motor motor3(3, 1, 18, 14, 6, 43, 30, -30);


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

    motor1.calcTorqueOutput();
    motor2.calcTorqueOutput();
    motor3.calcTorqueOutput();
}