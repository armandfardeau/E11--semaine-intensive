// include la librairie du servo
#include <Servo.h>
//include la librairie du rtc 
#include <Wire.h>
#include <RTClib.h>

//rename des modules
RTC_DS1307 RTC;
Servo myServo;

//Position ouverte = 90 degré
int open = 90;
//Position fermé = 10 degré
int close = 10;

unsigned int servo = 3;
char junk;
String inputString="";

void setup() {
  Wire.begin();
  RTC.begin();
  // regler la date et l'heure à la compilation, décommenter pour ajuster l'heure, commenter une fois reglé
  //RTC.adjust(DateTime(__DATE__, __TIME__));

  myServo.attach(servo);
  Serial.begin(115200);            // set the baud rate to 9600, same should be of your Serial Monitor
 pinMode(13, OUTPUT);
}

void loop()
{
  DateTime now = RTC.now();
  Serial.print(now.minute());
  Serial.println(now.second());
  if(Serial.available()){
  while(Serial.available())
    {
      uint8_t inputString = (uint8_t)Serial.readString(); //read the input
      //char inChar = (char)Serial.read(); //read the input
      //inputString += inChar;        //make a string of the characters coming on serial
    }
    Serial.println(inputString);
    while (Serial.available() > 0)  
    { junk = Serial.read() ; }      // clear the serial buffer
    if(now.minute() == inputString){         //in case of 'a' turn the LED on
      digitalWrite(13, HIGH);  
      myServo.write(open);
    }else if(inputString == "close"){   //incase of 'b' turn the LED off
      digitalWrite(13, LOW);
       myServo.write(close);
    }
    inputString = "";
  }
}
