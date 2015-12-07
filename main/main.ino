#include <Wire.h>
#include "RTClib.h"

#define Relay1 5
#define Relay2 6

RTC_DS1307 rtc;

char BTData;
bool BTRelay = false;
int timesleep = 23;
int timestart = 6;


void setup() {
  Serial1.begin(9600);

  pinMode(Relay1, OUTPUT);

  Serial1.println("Help");
  Serial1.println("Enter 1 - Relay ON");
  Serial1.println("Enter 0 - Relay OFF");
  Serial1.println("Enter T - Show Time");
}

void loop() {
  BTSerial();
  TimeToWork();
}

//Bluetooth
void BTSerial() {
  if (Serial1.available()) {
    BTData = Serial1.read();
    if (BTData == '1') {
      digitalWrite(Relay1, HIGH);
      BTRelay = false;
    }
    if (BTData == '0') {
      digitalWrite(Relay1, LOW);
      BTRelay = true;
    }
    if (BTData == 't') {
      ShowTime();
    }
  }
  Serial1.flush();
}

//Time
void TimeToWork() {
  //rtc.adjust(DateTime(2015,12,1,22,59,45));
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  DateTime now = rtc.now();
  if (now.hour() > timestart && now.hour() !=timesleep && !BTRelay ) {
    digitalWrite(Relay1, HIGH);
  }
  else  {
    digitalWrite(Relay1, LOW);
  }
}
void ShowTime(){
  DateTime now = rtc.now();
  Serial1.print(now.hour());
  Serial1.print(':');
  Serial1.print(now.minute());
  Serial1.print(':');
  Serial1.print(now.second());
  Serial1.print("  ");
  Serial1.print(now.day());
  Serial1.print('/');
  Serial1.print(now.month());
  Serial1.print('/');
  Serial1.print(now.year());
  Serial1.println();
}
