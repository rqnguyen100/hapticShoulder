#include <Arduino.h>
#include ".\display.h"

// Define screen size
const int SCREEN_WIDTH = 128; // OLD display width, in pixels
const int SCREEN_HEIGHT = 64; // OLED display height, in pixels

display::display() { // constructor
}

// Define SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void display::displayInit(){
    // Initialize OLED display with address 0x3C for 128x64
    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        while (true);
    }

    delay(100);
    oled.setTextSize(3);
    oled.setTextColor(WHITE);
}

void display::displayWrite(float position) {
    oled.clearDisplay();
    oled.setCursor(0, 10);
    oled.print(position);
    oled.display();
}
