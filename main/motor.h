#ifndef _MOTOR_H // header guard
#define _MOTOR_H

#include <Arduino.h>

class motor {
public:
    /*Attributes*/
    int aPin;
    int bPin;
    volatile bool aState;
    volatile bool bState;
    volatile double encoderCount;
    double position;

public:
    /*Functions*/
    motor(int aPin, int bPin, bool aState, bool bState, double encoderCount, double position);

    void encoderPinInit();

    void calcPosition();

private:
    /*Encoder Specs*/
    const int CPR = 500; // counts per revolution

    // Static member function for ISR
    static void encoderAPulseISR();

    // Static member function for handling A pulse
    static void encoderAPulse(motor* instance);
};

#endif
