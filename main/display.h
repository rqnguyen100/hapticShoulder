#ifndef _DISPLAY_H // header guard
#define _DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class display{

  public:
      display();

      void displayWrite(float);

  private:
    Adafruit_SSD1306 oled;

};

#endif