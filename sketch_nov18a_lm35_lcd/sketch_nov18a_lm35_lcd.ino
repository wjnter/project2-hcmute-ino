#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>

#include <WebSocketClient.h>

const char* ssid     = "80 dqh lau 2.2";
const char* password = "80duongquangham";
  
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);  

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

void setup() {
  Serial.begin(9600);
  //SETUPBTN
  pinMode(btnBulb1, INPUT); 
  pinMode(btnBulb2, INPUT); 
  pinMode(btnFan, INPUT); 
  
  pinMode(bulb1, OUTPUT);
  pinMode(bulb2, OUTPUT);
  pinMode(fan, OUTPUT);

  digitalWrite(bulb1, LOW);
  digitalWrite(bulb2, LOW);
  digitalWrite(fan, LOW);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  lcd.begin(20, 4); 
  lcd.setCursor(0, 0); lcd.print("TEST BTN + LED");
}

void loop() {
  
  for (int i = 0; i < 500; i++) {
    controlBulb1();
    controlBulb2();
    delay(1);
  }

  analogValue = analogRead(outputPin);
  float millivolts = (analogValue/1023.0) * 3000; //3300 is the voltage provided by NodeMCU
  float celsius = millivolts/10;
  lcd.setCursor(0, 0);
  lcd.print("in DegreeC:  ");
  lcd.println(celsius);
  Serial.println(celsius);
}
//#include <ESP8266WiFi.h>
//#include <LiquidCrystal_I2C.h>
//
//#include <WebSocketClient.h>
//
//const char* ssid     = "80 dqh lau 2.2";
//const char* password = "80duongquangham";
//
//int outputPin = A0;
//float analogValue = 0;
//LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);  
//
//void setup() {
//  Serial.begin(9600);
//  lcd.begin(20, 4); 
//}
//
//void loop() {
//  analogValue = analogRead(outputPin);
//  float millivolts = (analogValue/1023.0) * 3300; //3300 is the voltage provided by NodeMCU
//  float celsius = millivolts/10;
//  lcd.setCursor(0, 0);
//  lcd.print("in DegreeC:  ");
//  lcd.println(celsius);
//  Serial.println(celsius);
//  
//  delay(1000);
//}
