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
    motor(int aPin, int bPin);

    void begin(const byte aPin, const byte bPin);

    void encoderAPulse();

    void calcPosition();

private:
    /*Encoder Specs*/
    const int CPR = 500; // counts per revolution

    /*
      aPin Rising = 1x Resolution (B does not have to be connected to interrupt pin)
      aPin Change = 2x Resolution (B does not have to be connected to interrupt pin)
      aPin and bPin Change = 4x Resolution (B has to be connected to interrupt pin)
    */
    const int resolution = 2; // dependent on number of interrupt pins used
};

#endif
