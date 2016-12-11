#include <Adafruit_NeoPixel.h>
#include "EasingLibrary.h"
#include "BackEase.h"

BackEase back;

#define PIN 10
#define STRIPSIZE 16

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIPSIZE, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  strip.begin();
  strip.setBrightness(25);  // Lower brightness and save eyeballs!
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  //colorWipe(strip.Color(64, 0, 0), 100); // Red
  //colorWipe(strip.Color(0, 64, 0), 100); // Green
  //colorWipe(strip.Color(0, 0, 64), timeLeft); // Blue
  pulseLight(strip.Color(0, 0, 64),1); //color / length
}

void pulseLight(int color, int animationLength){
AllPixel(color);
delay(2000);
strip.setBrightness(50);
}
void AllPixel(int c){
  strip.setPixelColor(0, c);
  strip.setPixelColor(1, c);
  strip.setPixelColor(2, c);
  strip.setPixelColor(3, c);
  strip.setPixelColor(4, c);
  strip.setPixelColor(5, c);
  strip.setPixelColor(6, c);
  strip.setPixelColor(7, c);
  strip.setPixelColor(8, c);
  strip.setPixelColor(9, c);
  strip.setPixelColor(10, c);
  strip.setPixelColor(11, c);
}


