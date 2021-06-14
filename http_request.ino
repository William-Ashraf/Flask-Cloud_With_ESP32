#include <WiFi.h>
#include <HTTPClient.h>
#include "DHTinit.h"
#include "servo.h"

volatile int pirCount=0; //to count number of detected motions 
int ledPin = 2;                // LED 
int pirPin = 4;                 // PIR Out pin 
volatile int gasPin = 36;//gas out
volatile int wifiLed = 17; //wifi indicator 
int alarmPin = 23 ;
volatile byte pirStat = LOW;// PIR status
String servState="";

volatile int interruptCounter;
int totalInterruptCounter;
hw_timer_t * timer = NULL;
DHT dht(DHTPin,DHTTYPE);


void IRAM_ATTR isr0() 
{
pirStat=digitalRead(pirPin);
digitalWrite(ledPin,pirStat);
Serial.printf("motion is detected\n");
pirCount++;

}

void IRAM_ATTR onTimer()
{
  Serial.printf("hi from timer\n");
  if(analogRead(gasPin)<=2200)
  {
  Serial.printf("your house is safe\n");
  digitalWrite(alarmPin,LOW);
  }
  else
  {
  digitalWrite(alarmPin,HIGH);
  }
}



void setup() 
{
Serial.begin(115200);
pinMode(ledPin, OUTPUT);
pinMode(alarmPin, OUTPUT);  
pinMode(pirPin, INPUT); 
attachInterrupt(pirPin,isr0,CHANGE);
ConnectWifi("Adwm","32@adfo@5915859",wifiLed);
timer = timerBegin(0, 80, true);
timerAttachInterrupt(timer, &onTimer, true);
timerAlarmWrite(timer, 3000000, true);
/*timerAlarmEnable(timer);*/
DHTinit();
servoInit();
}

void loop()
{
 httpPost("http://gradprojcomm.pythonanywhere.com/motion",String(pirCount));
 httpPost("http://gradprojcomm.pythonanywhere.com/gas",String(analogRead(gasPin)));
 httpPost("http://gradprojcomm.pythonanywhere.com/humidity",String(dht.readHumidity()));
 httpPost("http://gradprojcomm.pythonanywhere.com/temp",String(dht.readTemperature()));
 /*servoAngle(httpGet("http://gradprojcomm.pythonanywhere.com/servo"));*/
 servState=httpGet("http://gradprojcomm.pythonanywhere.com/face");
 Serial.println(servState);
  if(servState=="b\'CloseTheWindow\'")
  {Serial.printf("hello  0");
   servoAngle(0);
  }
  else if(servState=="b\'OpenTheWindow\'")
  {Serial.printf("hello  180");
   servoAngle(180);
  }
  else if(servState=="b\'TurnOnTheLight\'")
  {Serial.printf("light on");
   digitalWrite(wifiLed,HIGH);
  }
  else if(servState=="b\'TurnOffTheLight\'")
  {Serial.printf("light off");
   digitalWrite(wifiLed,LOW);
  }
}
