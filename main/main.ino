#include <Wire.h>
#include "RTClib.h"

#define Relay1 5
#define Relay2 6

RTC_DS1307 rtc;

char BluetoothData;
int timesleep = 23;
int timestart = 6;


void setup() {
  Serial1.begin(9600);
  Serial.begin(9600); //DELETE
  Serial1.println("Help");
  Serial1.println("Enter 1 - Relay ON");
  Serial1.println("Enter 0 - Relay OFF");
  pinMode(Relay1, OUTPUT);
}

void loop() {
  BTSerial();
  Time();
}

//Bluetooth
void BTSerial() {
  if (Serial1.available()) {
    BluetoothData = Serial1.read();
    if (BluetoothData == '1') {
      digitalWrite(Relay1, HIGH);
    }
    if (BluetoothData == '0') {
      digitalWrite(Relay1, LOW);
    }
  }
  Serial1.flush();
}

//Time
void Time() {

  //rtc.adjust(DateTime(2015,12,1,22,59,45));

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  DateTime now = rtc.now();
  if (now.hour() > timestart && now.hour() !=timesleep) {
    digitalWrite(Relay1, HIGH);
    Serial.println("WORK");

  }
  else  {
    digitalWrite(Relay1, LOW);
    Serial.println("SLEEP");
  }


  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second());
  Serial.print("  ");
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.println();
  delay(1000);

}
