#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

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
}
//
//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
//#include "RTClib.h"
//
//RTC_DS1307 rtc;
//char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
//
//void setup ()
//{
// Serial.begin(9600);
// if (! rtc.begin())
// {
//   Serial.print("Couldn't find RTC");
//   while (1);
// }
//
//  if (! rtc.isrunning())
// {
//   Serial.print("RTC is NOT running!");
//   Serial.println();
// }
//   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//   //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
//}
//
//void loop ()
//{
//   DateTime now = rtc.now();
//   if(now.hour()<=9)
//   {
//     Serial.print("0");
//     Serial.print(now.hour());
//   }
//   else {
//    Serial.print(now.hour());
//   }
//   Serial.print(':');
//   if(now.minute()<=9)
//   {
//     Serial.print("0");
//     Serial.print(now.minute());
//   }
//   else {
//    Serial.print(now.minute());
//   }
//   Serial.print(':');
//   if(now.second()<=9)
//   {
//     Serial.print("0");
//     Serial.print(now.second());
//   }
//   else {
//    Serial.print(now.second());
//   }
//   Serial.println();
//
//   Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
//   Serial.print(",");
//   if(now.day()<=9)
//   {
//     Serial.print("0");
//     Serial.print(now.day());
//   }
//   else {
//    Serial.print(now.day());
//   }
//   Serial.print('/');
//   if(now.month()<=9)
//   {
//     Serial.print("0");
//     Serial.print(now.month());
//   }
//   else {
//    Serial.print(now.month());
//   }
//   Serial.print('/');
//   if(now.year()<=9)
//   {
//     Serial.print("0");
//     Serial.print(now.year());
//   }
//   else {
//    Serial.print(now.year());
//   } 
//   Serial.println();
//   delay(1000);
//}
