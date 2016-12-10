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
String futureTimeMinute="";

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
  //Serial.println(now.second());
  String nowMinuteString = String(now.minute());

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
      String futureTimeMinute = inputString;
    }
    //debug
      Serial.println(futureTimeMinute);
    if(futureTimeMinute == nowMinuteString){         //in case of 'a' turn the LED on
      digitalWrite(13, HIGH);  
      myServo.write(open);
    }
    else if(inputString == "close"){   //incase of 'b' turn the LED off
      digitalWrite(13, LOW);
       myServo.write(close);
    }
    inputString = "";
  }
}
