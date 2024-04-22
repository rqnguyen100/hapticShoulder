#ifndef _MOTOR_H // header guard
#define _MOTOR_H

#include <Arduino.h>

class motor {
public:
    /*Attributes*/
    const int aPin;
    const int bPin;
    volatile bool aState;
    volatile bool bState;
    volatile double encoderCount;
    volatile double position;

    /*Instance Handler*/
    static motor * instances [2];
    static void encoderAPulseExt0();
    static void encoderAPulseExt1();

public:
    /*Functions*/
    motor(int aPin, int bPin, bool aState, bool bState, double encoderCount, double position);

    void begin(const byte aPin, const byte bPin);

    void encoderAPulse();

    void calcPosition();

private:
    /*Encoder Specs*/
    const int CPR = 500; // counts per revolution
    const int resolution = 2; // dependent on number of interrupt pins used
};

#endif
