#include "motor.h"
#include <Wire.h>
#include "I2C_Anything.h"

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
motor motor2(2, 19, 18, 10, 11, 30, -30);
// motor motor3(3, 20, 21, 6, 7, 30, -30);

const int SLAVE_ADDRESS = 9;
volatile double motor1_pos; 
volatile double motor2_pos; 
// volatile double motor3_pos; 

unsigned long timestamp;

void setup() {
    // Begin serial monitor
    Wire.begin();
    // pinMode(LED_BUILTIN,OUTPUT);

    // Change PWM pin frequency to 20kHz
    // TCCR1B &= ~7;
    // TCCR1B |= 1;
    // TCCR2B &= ~7;
    // TCCR2B |= 1;
    // TCCR4B &= ~7;
    // TCCR4B |= 1;

    // Initialize
    motor1.begin(motor1.aPin, motor1.bPin);
    motor2.begin(motor2.aPin, motor2.bPin);
    // motor3.begin(motor3.aPin, motor3.bPin);
}

void loop() {
    // Calculate initial shaft position
    motor1.calcPosition();
    motor2.calcPosition();
    // motor3.calcPosition();

    timestamp = millis();

    motor1_pos = motor1.position;
    motor2_pos = motor2.position;
    // motor3_pos = motor3.position;
    
    Wire.beginTransmission(SLAVE_ADDRESS);
    I2C_writeAnything(motor1_pos);
    I2C_writeAnything(motor2_pos);
    // I2C_writeAnything(motor3_pos);
    I2C_writeAnything(timestamp);
    Wire.endTransmission();

    delay(1000);

}