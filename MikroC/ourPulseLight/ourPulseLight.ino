#include <Adafruit_NeoPixel.h>
#define PIXEL_COUNT 12
#define COLOR_COUNT 12
#define PIN 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIN);
const uint32_t colorMap[COLOR_COUNT] = {
  strip.Color(106, 162, 203),
  strip.Color(94, 11, 212),
  strip.Color(89, 178, 213),
  strip.Color(98, 170, 208),
  strip.Color(111, 153, 198),
  strip.Color(123, 8, 183),
  strip.Color(131, 111, 171),
  strip.Color(135, 100, 164),
  strip.Color(135, 97, 162),
  strip.Color(133, 103, 166),
  strip.Color(128, 120, 177),
  strip.Color(119, 141, 191),
};

float fadeInValue = 0.5;
float fadeOutValue = 0.5;
int fadeMax = 75;
int fadeMin = 10;
int dimming = 15;
int pulse = 3;
int i;

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.setBrightness(25);  // Lower brightness and save eyeballs!
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {



  while (i < pulse) {
    for (float fadeValue = fadeMin ; fadeValue <= fadeMax; fadeValue += fadeInValue) {
      // sets the value (range from 0 to 75):
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, colorMap[i]);

      }
      strip.setBrightness(fadeValue);
      strip.show(); // Initialize all pixels to 'off'
      // wait for 30 milliseconds to see the dimming effect
      delay(dimming);
    }
    // fade out from max to min in increments of 5 points:
    for (float fadeValue = fadeMax ; fadeValue >= fadeMin; fadeValue -= fadeOutValue) {
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, colorMap[i]);
      }
      // sets the value (range from 0 to 255):
      strip.setBrightness(fadeValue);
      strip.show(); // Initialize all pixels to 'off'
      // wait for 30 milliseconds to see the dimming effect
      delay(dimming);
    }
    i++;
  }
  strip.setBrightness(0);
  strip.show();
}


