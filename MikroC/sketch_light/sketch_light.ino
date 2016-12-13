#include <Adafruit_NeoPixel.h>

#define PIN 6
#define STRIPSIZE 12


// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIPSIZE, PIN, NEO_GRB + NEO_KHZ800);

const uint32_t colorMap[STRIPSIZE] = {
  strip.Color(106, 162, 203),
  strip.Color(94, 175, 211),
  strip.Color(89, 178, 213),
  strip.Color(100, 170, 208),
  strip.Color(112, 153, 198),
  strip.Color(123, 130, 183),
  strip.Color(131, 111, 171),
  strip.Color(135, 100, 164),
  strip.Color(135, 97, 162),
  strip.Color(133, 103, 166),
  strip.Color(129, 119, 176),
  strip.Color(119, 141, 191),
};

unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 1000;           // interval at which to blink (milliseconds)

float timeLeft = 60;
float T_timeLeft = timeLeft;
int pixelNbr = 0;
float pixelNbrInUse = 0;
float activeTime;

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(25);  // Lower brightness and save eyeballs!
  strip.show(); // Initialize all pixels to 'off'


}

void loop() {


  unsigned long currentMillis = millis();
  if (pixelNbr <= 12 && timeLeft >= 0 ) {
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      if (pixelNbr == 12) {
        strip.setBrightness(0);
        strip.show();
      }
      else if (T_timeLeft - timeLeft >= activeTime) {
        Serial.println("boucle strip");
        strip.setPixelColor(pixelNbr, colorMap[pixelNbr]);
        strip.show();

        pixelNbr += 1;

        pixelNbrInUse += 1.0;




      }
      // Some example procedures showing how to display to the pixels:
      timeLeft--;
      activeTime = (pixelNbrInUse / 12) * T_timeLeft;
      Serial.println(T_timeLeft - timeLeft);
      Serial.println(activeTime);

    }
  }
}










