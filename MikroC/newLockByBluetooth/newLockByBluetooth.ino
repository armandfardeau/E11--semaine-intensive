// include la librairie du servo
#include <Servo.h>

//include la librairie du neopixel
#include <Adafruit_NeoPixel.h>
#define PIXEL_COUNT 12
#define COLOR_COUNT 12
#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIN);
const uint32_t colorMap[COLOR_COUNT] = {
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

float fadeInValue = 0.5;
float fadeOutValue = 0.5;
int fadeMax = 75;
int fadeMin = 10;
int dimming = 15;
int pulse = 6;
int i;

//rename des modules
Servo myServo;

// servo var part
unsigned int servo = 3;
//Position ouverte = 90 degré
int open = 90;
//Position fermé = 10 degré
int close = 10;
//boolean boxclosed
bool boxClosed;

//var used in serial communication part
char junk;
String inputString = "";

unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 1000;           // interval at which to blink (milliseconds)

float timeLeft = 3600;
float T_timeLeft = timeLeft;
int pixelNbr = 0;
float pixelNbrInUse = 0;
float activeTime;

bool timeSet = false;
bool T_timeLeftIsDefined = false;

void animationFinale() {
  strip.show();
  for (uint16_t i = 0; i < 5; i++) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 0);
      strip.show();
      delay(100);
    }
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, colorMap[i]);
      strip.show();
      delay(100);
    }
  }

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
  boxClosed = false;
  myServo.attach(servo);
  myServo.write(open);
  delay(1000);
  myServo.detach();


}
void setup() {
  // put your setup code here, to run once:
  // strip module begin
  strip.begin();
  strip.setBrightness(25);  // Lower brightness and save eyeballs!
  strip.show(); // Initialize all pixels to 'off'
  // strip module end

  // servo module begin
  myServo.attach(servo);
  myServo.write(open);
  delay(1000);
  myServo.detach();
  //servo module end

  //bluetooth module begin
  //BT is connected to TX and RX, it use Serial communication. Baud rate muste be send to 115200
  Serial.begin(115200);            // set the baud rate to 9600, same should be of your Serial Monitor
  //Bluetooth module end
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    while (Serial.available())
    {
      inputString = Serial.readString(); //read the input
      //char inChar = (char)Serial.read(); //read the input
      //inputString += inChar;        //make a string of the characters coming on serial
    }


    if (inputString == "close") { //incase of 'close' close the box
      boxClosed = true;
      myServo.attach(servo);
      myServo.write(close);
      delay(1000);
      myServo.detach();
    }
    else if (inputString == "open") { //incase of 'open' open the box
      boxClosed = false;
      myServo.attach(servo);
      myServo.write(open);
      delay(1000);
      myServo.detach();
    }
    else if (inputString == "panic") {
      if (boxClosed == true) {
        animationFinale();
      }
    }
    //if input is not empty then it must be full of something, like the numbers we need
    else {
      timeLeft = inputString.toFloat();
      timeSet = true;

    }
    while (Serial.available() > 0)
    {
      junk = Serial.read() ;  // clear the serial buffer
    }
    inputString = "";
  }
  else if (timeLeft <= 0) {
    if (boxClosed == true) {
      animationFinale();
    }
  }
  else {
    unsigned long currentMillis = millis();
    if (timeSet) {
      if (T_timeLeftIsDefined == false) {
        T_timeLeft = timeLeft;
        T_timeLeftIsDefined = true;
      }
      if (pixelNbr <= 12 && timeLeft >= 0 ) {
        if (currentMillis - previousMillis >= interval) {
          // save the last time you blinked the LED
          previousMillis = currentMillis;

          if (T_timeLeft - timeLeft >= activeTime) {
            strip.setPixelColor(pixelNbr, colorMap[pixelNbr]);
            strip.show();
            pixelNbr += 1;
            pixelNbrInUse += 1.0;
          }
          // Some example procedures showing how to display to the pixels:
          timeLeft--;
          activeTime = (pixelNbrInUse / 12) * T_timeLeft;

        }
      }
    }
  }
}
