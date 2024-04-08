#ifndef _MOTOR_H // header guard
#define _MOTOR_H

class motor{

    public:
        /*Variables*/
        static int encoderCount;
        float position = 0;

        static bool aState;
        static bool bState;

    public:
        /*Functions*/
        motor();

        void motorPinInit();
        void encoderPinInit();

        static void encoderAPulse();
        static void encoderBPulse();

        void calcPosition();

    private:
        /*Motor pins*/

        /*Encoder pins*/ 
        #define ENCODER_A_PIN 2 
        #define ENCODER_B_PIN 3

        /*Encoder Specs*/
        const int CPR = 500; // counts per revolution
        const int freq = 100; // hertz
};

#endif