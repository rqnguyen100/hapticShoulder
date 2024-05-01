#include "motor.h"

/*
  intialize motor class with inputs
    - aPin (encoder A channel)
    - bPin (encoder B channel)
    - pwmPin (E1 speed control)
    - dirPin (M1 direction control)
    [optional]
      - spring constant (default = 10) 
      - damper ratio (default = 0.35)
*/
motor motor1(2, 3, 8, 9);
motor motor2(19, 18, 10, 11);
motor motor3(20, 21, 6, 7);

void setup() {
    // Begin serial monitors
    Serial.begin(115200);

    // Change PWM pin frequency to 20kHz
    TCCR1B &= ~7;
    TCCR1B |= 1;
    TCCR2B &= ~7;
    TCCR2B |= 1;
    TCCR4B &= ~7;
    TCCR4B |= 1;

    // Initialize
    // motor1.begin(motor1.aPin, motor1.bPin, motor1.pwmPin, motor1.dirPin);
    // motor2.begin(motor2.aPin, motor2.bPin, motor2.pwmPin, motor2.dirPin);
    motor3.begin(motor3.aPin, motor3.bPin, motor3.pwmPin, motor3.dirPin);
}

void loop() {
    // Calculate initial shaft position
    // motor1.calcPosition();
    // motor2.calcPosition();
    motor3.calcPosition();

    // Do Haptic Stuff
    // motor1.calcTorqueOutput();
    // motor2.calcTorqueOutput();
    motor3.calcTorqueOutput();
}