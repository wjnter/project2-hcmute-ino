#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

int outputPin = A0;
float analogValue = 0;

const int btnFan = 16; //D0
const int btnBulb2 = 0; //D3
const int btnBulb1 = 2;   //D4

const int bulb1 = D5;
const int bulb2 = D6;
const int fan = D7;

bool statusBulb1 = false;
bool statusBulb2 = false;
bool statusFan = false;

void controlBulb1() {
  if (!digitalRead(btnBulb1)) {
    delay(30);
    if (!digitalRead(btnBulb1)) {
      statusBulb1 = !statusBulb1;
      Serial.print("Trang thai nut nhan 1: ");
      Serial.println(statusBulb1);
      while (!digitalRead(btnBulb1));
      if (statusBulb1) {
        Serial.print("Đèn 1 mở: "); Serial.println(statusBulb1);
        digitalWrite(bulb1, HIGH);
      } else {
        Serial.print("Đèn 1 mở: "); Serial.println(statusBulb1);
        digitalWrite(bulb1, LOW);
      }
    }
  }
}

void controlBulb2() {
  if (!digitalRead(btnBulb2)) {
    delay(30);
    if (!digitalRead(btnBulb2)) {
      statusBulb2 = !statusBulb2;
      Serial.print("Trang thai nut nhan 2: ");
      Serial.println(statusBulb2);
      while (!digitalRead(btnBulb2));
      if (statusBulb2) {
        Serial.print("Đèn 2 mở: "); Serial.println(statusBulb2);
        digitalWrite(bulb2, HIGH);
      } else {
        Serial.print("Đèn 2 mở: "); Serial.println(statusBulb2);
        digitalWrite(bulb2, LOW);
      }
    }
  }
}

void controlFan() {
  if (!digitalRead(btnFan)) {
    delay(30);
    if (!digitalRead(btnFan)) {
      statusFan = !statusFan;
//      Serial.print("Trang thai nut nhan 1: ");
      Serial.println(statusFan);
      while (!digitalRead(btnFan));
      if (statusFan) {
        digitalWrite(fan, HIGH);
      } else {
        digitalWrite(fan, LOW);
      }
    }
  }
}

void setup () 
{
  Serial.begin(9600);

  //Thiết lập cấu hình
  pinMode(btnBulb1, INPUT); 
  pinMode(btnBulb2, INPUT); 
  pinMode(btnFan, INPUT); 
  
  pinMode(bulb1, OUTPUT);
  pinMode(bulb2, OUTPUT);
  pinMode(fan, OUTPUT);

  digitalWrite(bulb1, LOW);
  digitalWrite(bulb2, LOW);
  digitalWrite(fan, LOW);
  
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
    //đặt 50 lần => delay gần 2s
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
      
      controlBulb1();
      controlBulb2();
    }

    analogValue = analogRead(outputPin);
    float millivolts = (analogValue/1023.0) * 2900; //3300 is the voltage provided by NodeMCU
    float celsius = millivolts/10;
    lcd.setCursor(0, 3);
    lcd.print("Nhiet do: ");
    lcd.println(celsius);
    Serial.println(celsius);
}
