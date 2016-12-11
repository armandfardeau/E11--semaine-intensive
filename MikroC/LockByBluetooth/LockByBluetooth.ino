// include la librairie du servo
#include <Servo.h>
//include la librairie du rtc 
#include <Wire.h>
#include <RTClib.h>

//include la librairie du neopixel
#include <Adafruit_NeoPixel.h>
#define PIN 10
#define STRIPSIZE 16
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIPSIZE, PIN, NEO_GRB + NEO_KHZ800);

//rename des modules
RTC_DS1307 RTC;
Servo myServo;

// servo var part
  unsigned int servo = 3;
  //Position ouverte = 90 degré
  int open = 90;
  //Position fermé = 10 degré
  int close = 10;

//var used in serial communication part
  char junk;
  String inputString="";
  String dateUser="";
  String boxTime = 0;

void setup() {
//RTC module begin
  Wire.begin();
  RTC.begin();
  // regler la date et l'heure à la compilation, décommenter pour ajuster l'heure, commenter une fois reglé
  //RTC.adjust(DateTime(__DATE__, __TIME__));
//RTC module end


// strip module begin
  strip.begin();
  strip.setBrightness(25);  // Lower brightness and save eyeballs!
  strip.show(); // Initialize all pixels to 'off'
// strip module end  

// servo module begin  
  myServo.attach(servo);
//servo module end

//bluetooth module begin
  //BT is connected to TX and RX, it use Serial communication. Baud rate muste be send to 115200
  Serial.begin(115200);            // set the baud rate to 9600, same should be of your Serial Monitor
//Bluetooth module end 

//led13 begin
  //used for debug
pinMode(13, OUTPUT);
// led13 module end
 
}

void loop()
{
  DateTime now = RTC.now();
  Serial.print(now.minute());
  //Serial.println(now.second());
  boxTime = String(now.minute());

  if(Serial.available()){
  while(Serial.available())
    {
      inputString = Serial.readString(); //read the input
      //char inChar = (char)Serial.read(); //read the input
      //inputString += inChar;        //make a string of the characters coming on serial
    }
    while (Serial.available() > 0)  
    { junk = Serial.read() ; }      // clear the serial buffer

   //if input string is not empty or is not "open or close" then it must be full of something, like the numbers we need
    if(inputString != "close"){
     //get value of input string and put it in futureTimeMinute to be used later
      String dateUser = inputString;
    }
    //debug
      Serial.println(futureTimeMinute);
    if(dateUser == nowMinuteString){         //in case of 'a' turn the LED on
      digitalWrite(13, HIGH);  
      myServo.write(open);
    }
    else if(inputString == "close"){   //incase of 'b' turn the LED off
      digitalWrite(13, LOW);
       myServo.write(close);
    }
    else if(inputString == "open"){   //incase of 'b' turn the LED off
      digitalWrite(13, LOW);
       myServo.write(open);
    }
    else if(inputString == "panic"){   //incase of 'b' turn the LED off
      digitalWrite(13, LOW);
       myServo.write(open);
    }
    inputString = "";
  }
}
