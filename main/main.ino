#include "motor.h"

/*
  intialize motor class with inputs
    - motorID
    - aPin (encoder A channel)
    - bPin (encoder B channel)
    - pwmPin (E1 speed control)
    - dirPin (M1 direction control)
    - upperLimit in deg (for free ROM) [has to be positive]
    - lowerLimit in deg (for free ROM) [has to be negative]
    [optional]
      - spring constant (default = 10) 
      - damper ratio (default = 0.35)
*/
motor motor1(1, 2, 3, 10, 9, 90, -90, 5);
// motor motor2(2, 19, 18, 10, 11, 30, -30);
// motor motor3(3, 20, 21, 6, 7, 30, -30);

void setup() {
    // Begin serial monitor
    Serial.begin(9600);

    // Change PWM pin frequency to 20kHz
    // TCCR1B &= ~7;
    // TCCR1B |= 1;
    // TCCR2B &= ~7;
    // TCCR2B |= 1;
    // TCCR4B &= ~7;
    // TCCR4B |= 1;

    // Initialize
    motor1.begin(motor1.aPin, motor1.bPin, motor1.pwmPin, motor1.dirPin);
    // motor2.begin(motor2.aPin, motor2.bPin, motor2.pwmPin, motor2.dirPin);
    // motor3.begin(motor3.aPin, motor3.bPin, motor3.pwmPin, motor3.dirPin);
}

void loop() {
    // Calculate initial shaft position
    motor1.calcPosition();
    // motor2.calcPosition();
    // motor3.calcPosition();

    motor1.calcTorqueOutput();
    // motor2.calcTorqueOutput();
}