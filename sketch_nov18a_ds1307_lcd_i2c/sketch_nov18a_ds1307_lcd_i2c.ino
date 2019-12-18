#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
int onHour = 23;
int onMinute = 56;
int offHour = 23;
int offMinute = 57;

void setup () 
{
  Serial.begin(9600);
  lcd.begin(20,4);   
  lcd.setCursor(0, 0);
  lcd.print("Setting up");
  delay(1000);
  lcd.clear();
  if (! rtc.begin()) 
  {
    lcd.print("Couldn't find RTC"); 
    while (1);
  }

  if (! rtc.isrunning()) 
  {
    lcd.print("RTC is NOT running!");
  }
  
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//auto update from computer time
//    rtc.adjust(DateTime(2019, 11, 18, 22, 54, 0));// to set the time manualy 
}

void loop () 
{
//    DateTime now = rtc.now();
    for (int i = 0; i < 50; i++) {
      DateTime now = rtc.now();
    
      lcd.setCursor(4, 1);
      if(now.hour()<=9)
      {
        lcd.print("0");
        lcd.print(now.hour());
      }
      else {
       lcd.print(now.hour()); 
      }
      lcd.print(':');
      if(now.minute()<=9)
      {
        lcd.print("0");
        lcd.print(now.minute());
      }
      else {
       lcd.print(now.minute()); 
      }
      lcd.print(':');
      if(now.second()<=9)
      {
        lcd.print("0");
        lcd.print(now.second());
      }
      else {
       lcd.print(now.second()); 
       Serial.println(now.second());
      }
      lcd.print("   ");
  
      lcd.setCursor(1, 0);
      lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
      lcd.print(",");
      if(now.day()<=9)
      {
        lcd.print("0");
        lcd.print(now.day());
      }
      else {
       lcd.print(now.day()); 
      }
      lcd.print('/');
      if(now.month()<=9)
      {
        lcd.print("0");
        lcd.print(now.month());
      }
      else {
       lcd.print(now.month()); 
      }
      lcd.print('/');
      if(now.year()<=9)
      {
        lcd.print("0");
        lcd.print(now.year());  
      }
      else {
       lcd.print(now.year()); 
      }
      delay(1);

      
      if ((now.hour() > onHour) && (now.hour() < offHour)) {
        Serial.println("Opening bulb 1");
      } else 
      if ((now.hour() == onHour) || (now.hour() == offHour)) {
        if (now.minute() >= onMinute) {
          if (now.minute() < offMinute) {
            Serial.println("Opening bulb 2");
          }
        }
      } else {
        Serial.print("Nothing onHour");
      }
      
      if ((now.hour() < onHour) || (now.hour() > offHour)) {
        Serial.println("Turning off bulb 1");
      } else 
      if ((now.hour() == onHour) || (now.hour() == offHour)) {
        if ((now.minute() < onMinute) || (now.minute() >= offMinute)) {
          Serial.println("Turning off bulb 2");
        }
      } else {
        Serial.println("Nothing offHour");
      }

      
    }

    
    
    
}
