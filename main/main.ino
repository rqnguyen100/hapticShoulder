#include "motor.h"

/*
  intialize motor class with inputs
    - motorID
    - gear ratio
      - Disclaimer: must be float
    - aPin (encoder A channel)
      - Disclaimer: must verify begin() switch statement is consistent with pins
    - bPin (encoder B channel)
    - invAPin (encoder inverse A channel)
    - invBPin (encoder inverse B channel)
    - pwmPin (E1 speed control)
    - dirPin (M1 direction control)
    - upperLimit in deg (for free ROM) [has to be positive]
    - lowerLimit in deg (for free ROM) [has to be negative]
    [optional]
      - spring constant (default = 10) 
      - damper ratio (default = 0.35)
*/

motor motor1(1, 1, 2, 6, 4, 5, 9, 8, 90, -90);
// motor motor2(2, 1, 18, 5, 7, 42, 20, -20);
// motor motor3(3, 1, 19, 6, 6, 43, 30, -30);


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
    motor1.begin(motor1.aPin, motor1.bPin, motor1.invAPin, motor1.invBPin, motor1.pwmPin, motor1.dirPin);
    // motor2.begin(motor2.aPin, motor2.bPin, motor2.pwmPin, motor2.dirPin);
    // motor3.begin(motor3.aPin, motor3.bPin, motor3.pwmPin, motor3.dirPin);
}

void loop() {
    // Calculate initial shaft position
    motor1.calcPosition();
    // motor2.calcPosition();
    // motor3.calcPosition();

    // Do haptics
    motor1.calcTorqueOutput();
    
    // motor2.calcTorqueOutput();
    // motor3.calcTorqueOutput();

    // print position for logging purposes
    Serial.println(motor1.position);
    delay(10);
}