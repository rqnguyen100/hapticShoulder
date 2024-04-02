#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define Pins
#define aPin 2 // interrupt pin
#define bPin 3 // interrupt pin

// Define screen size
#define SCREEN_WIDTH 128 // OLD display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Define SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Encoder Properties
const int CPR = 500; // counts per revolution
const int freq = 100; // hertz

// State Variables
bool aState = 1;
bool bState = 1;

// Relevant Outputs
static int encoderCount = 0;
static float position = 0;

void setup() {
  // Begin serial monitors
  Serial.begin(9600);

  // Initialize pin mode
  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);
  
  /*
    aPin Rising = 1x Resolution
    aPin Change = 2x Resolution
    aPin and bPin Change = 4x Resolution
  */
  attachInterrupt(digitalPinToInterrupt(aPin), encoderAPulse, CHANGE);
  attachInterrupt(digitalPinToInterrupt(bPin), encoderBPulse, CHANGE);

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
  while (true);
  }

  delay(freq);
  oled.setTextSize(3);
  oled.setTextColor(WHITE);
}

void loop() {
  // Calculate shaft position
  position = encoderCount * (360. / (CPR * 4));
  oled.clearDisplay();
  oled.setCursor(0,10);
  oled.print(position);
  oled.display();
  delay(freq);
}

void encoderAPulse() {
  // Read channels
  aState = digitalRead(aPin);
  bState = digitalRead(bPin);

  // Determine direction based on A and B state
  if (aState){
    if (bState){
      encoderCount--;
    }
    else {
      encoderCount++;
    }
  }
  else {
    if (bState){
      encoderCount++;
    }
    else {
      encoderCount--;
    }
  }
}

void encoderBPulse() {
  // Read channels
  aState = digitalRead(aPin);
  bState = digitalRead(bPin);

  // Determine direction based on A and B state
  if (bState){
    if (aState){
      encoderCount++;
    }
    else {
      encoderCount--;
    }
  }
  else {
    if (aState){
      encoderCount--;
    }
    else {
      encoderCount++;
    }
  }
}