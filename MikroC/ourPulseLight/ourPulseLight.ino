#include <Adafruit_NeoPixel.h>
#define PIXEL_COUNT 12
#define COLOR_COUNT 12
#define PIN 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIN);
const uint32_t colorMap[COLOR_COUNT] = {
  strip.Color(64, 0, 0),
  strip.Color(64, 0, 0),
  strip.Color(64, 0, 0),
  strip.Color(64, 0, 0),
  strip.Color(64, 0, 0),
  strip.Color(64, 0, 0),
  strip.Color(64, 0, 0),
  strip.Color(64, 0, 0),
  strip.Color(64, 0, 0),
  strip.Color(64, 0, 0),
  strip.Color(64, 0, 0),
  strip.Color(64, 0, 0),
};

int pulse = 24;
int brightness[3] = {0,100, 5}; // max/min brightness

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.setBrightness(25);  // Lower brightness and save eyeballs!
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {





  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, colorMap[i]);
  }
  for (int i = 0; i <= pulse; i++ && pulse != 0) {
    if (pulse % 2 == 0) {
      strip.setPixelColor(i, colorMap[i]);
      strip.setBrightness(brightness[1]);
      strip.show();
      Serial.println("modulo 2");
    }
    else if (pulse != 0) {
      strip.setBrightness(brightness[2]);
      strip.show();
      Serial.println("!modulo 2");
    }
    else {
      strip.setBrightness(brightness[0]);
      strip.show();
    }
  }
  delay(2000);
  Serial.println(pulse);
  pulse--;
}


