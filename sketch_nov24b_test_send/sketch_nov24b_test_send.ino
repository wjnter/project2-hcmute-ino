#include <ESP8266WiFi.h>
#include <WebSocketClient.h>
#include <ArduinoJson.h>
#include <String.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"


RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

char onHourTens[2];
char onHourUnits[2];
char offHourTens[2];
char offHourUnits[2];

int outputPin = A0;
float analogValue = 0;

const int btnFan = 13;  //D7
const int btnBulb2 = 0; //D3
const int btnBulb1 = 2; //D4
const int btnMode = 12;  //D0


const int bulb1 = D5;
const int bulb2 = D8;
const int fan = D0;

bool statusBulb1 = false;
bool statusBulb2 = false;
bool statusFan = false;
bool statusMode = false; //mode false => manual, true => auto

boolean handshakeFailed=0;
String data= "";

//String json = "{\"id\":1,\"ten\":\"den1\",\"giatri\":0,\"thoigiandoc\":0,\"trangthai\":true,\"chedo\":false,\"thoigianmo\":\"16:24:00\",\"thoigiantat\":\"20:32:00\"}";
//char json[] = "{\"id\":1,\"ten\":\"den1\",\"giatri\":0,\"thoigiandoc\":0,\"trangthai\":true,\"chedo\":false,\"thoigianmo\":\"16:24:00\",\"thoigiantat\":\"20:32:00\"}";
String json = "";

char path[] = "/realtime-data";   //identifier of this device

//const char* ssid     = "80 dqh lau 2.2";
//const char* password = "80duongquangham";

const char* ssid     = "Wjnter";
const char* password = "Nguyenpt99";

char* host = "doan21.j.layershift.co.uk";  //thay domain vao
const int espport=8080;
  
WebSocketClient webSocketClient;
unsigned long previousMillis = 0;
unsigned long currentMillis;
unsigned long interval=300; //interval for sending data to the websocket server in ms

// Use WiFiClient class to create TCP connections
WiFiClient client;


void controlBulb1() {
  DynamicJsonDocument jsonBulb1(1024);
  
  if (!digitalRead(btnBulb1)) {
    delay(30);
    if (!digitalRead(btnBulb1)) {
      if (statusMode) {
        Serial.println("Không thể điều khiển ở chế độ tự động");
        while (!digitalRead(btnBulb1));
      } else {
        statusBulb1 = !statusBulb1;
        
        jsonBulb1["id"] = 1;
        jsonBulb1["ten"] = "den1";
        jsonBulb1["giatri"] = 0;
        jsonBulb1["thoigiandoc"] = 0;
        jsonBulb1["trangthai"]   = statusBulb1;
        jsonBulb1["chedo"]   = false;
        jsonBulb1["thoigianmo"] = "00:24:00";
        jsonBulb1["thoigiantat"] = "20:32:00";

        serializeJson(jsonBulb1, Serial);
        serializeJson(jsonBulb1, json);
//        Send data to Server
        webSocketClient.sendData(json);
        json = "";
        
        while (!digitalRead(btnBulb1));
//        if (statusBulb1) {
//          Serial.print("Đèn 1 mở: "); Serial.println(statusBulb1);
//          digitalWrite(bulb1, HIGH);
//        } else {
//          Serial.print("Đèn 1 mở: "); Serial.println(statusBulb1);
//          digitalWrite(bulb1, LOW);
//        }
      }
    }
  }
}

void controlBulb2() {
  DynamicJsonDocument jsonBulb2(1024);
  
  if (!digitalRead(btnBulb2)) {
    delay(30);
    if (!digitalRead(btnBulb2)) {
      if (statusMode) {
        Serial.println("Không thể điều khiển ở chế độ tự động");
        while (!digitalRead(btnBulb2));
      } else {
        statusBulb2 = !statusBulb2;
        
        jsonBulb2["id"] = 2;
        jsonBulb2["ten"] = "den2";
        jsonBulb2["giatri"] = 0;
        jsonBulb2["thoigiandoc"] = 0;
        jsonBulb2["trangthai"]   = statusBulb2;
        jsonBulb2["chedo"]   = false;
        jsonBulb2["thoigianmo"] = "00:24:00";
        jsonBulb2["thoigiantat"] = "20:32:00";

        serializeJson(jsonBulb2, Serial);
        serializeJson(jsonBulb2, json);
//        Send data to Server
        webSocketClient.sendData(json);
        json = "";

        while (!digitalRead(btnBulb2));
//        if (statusBulb2) {
//          Serial.print("Đèn 2 mở: "); Serial.println(statusBulb2);
//          digitalWrite(bulb2, HIGH);
//        } else {
//          Serial.print("Đèn 2 mở: "); Serial.println(statusBulb2);
//          digitalWrite(bulb2, LOW);
//        }
      }
    }
  }
}

void controlFan() {
  DynamicJsonDocument jsonFan(1024);
  if (!digitalRead(btnFan)) {
    delay(30);
    if (!digitalRead(btnFan)) {
      if (statusMode) {
        Serial.println("Không thể điều khiển ở chế độ tự động");
        while (!digitalRead(btnFan));
      } else {
        statusFan = !statusFan;
        jsonFan["id"] = 3;
        jsonFan["ten"] = "quat";
        jsonFan["giatri"] = 0;
        jsonFan["thoigiandoc"] = 0;
        jsonFan["trangthai"]   = statusFan;
        jsonFan["chedo"]   = false;
        jsonFan["thoigianmo"] = "00:24:00";
        jsonFan["thoigiantat"] = "20:32:00";

        serializeJson(jsonFan, Serial);
        serializeJson(jsonFan, json);
//        Send data to Server
        webSocketClient.sendData(json);
        json = "";
        
        while (!digitalRead(btnFan));
//        if (statusFan) {
//          Serial.print("Quạt mở: "); Serial.println(statusFan);
//        } else {
//          Serial.print("Quạt mở: "); Serial.println(statusFan);
//        }
      }
    }
  }   
}


void changeMode() {
  if (!digitalRead(btnMode)) {
    delay(30);
    if (!digitalRead(btnMode)) {
      statusMode = !statusMode;
      while (!digitalRead(btnMode));
      if (statusMode) {
        Serial.println("Chế độ tự động");
        lcd.setCursor(8, 2);
        lcd.print("AUTOMA");
      } else {
        Serial.println("Chế độ tự chỉnh"); 
        lcd.setCursor(8, 2);
        lcd.print("MANUAL");
      }
    }
  }
}

void setup() {
  Serial.begin(9600);
//    pinMode(readPin, INPUT);     // Initialize the LED_BUILTIN pin as an output
  //Thiết lập cấu hình
  pinMode(btnBulb1, INPUT); 
  pinMode(btnBulb2, INPUT); 
  pinMode(btnFan, INPUT); 
  pinMode(btnMode, INPUT);
  
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
  lcd.setCursor(0, 2);
  lcd.print("Che do: ");
  lcd.setCursor(8, 2);
  if (statusMode) {
    Serial.println("Chế độ tự động");
    lcd.print("AUTOMA");
  } else {
    Serial.println("Chế độ tự chỉnh"); 
    lcd.print("MANUAL");
  }
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


  delay(10);

  // We start by connecting to a WiFi network

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

  delay(1000);
  
wsconnect();
//  wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void loop() {

//đặt 50 lần => delay gần 2s
    for (int i = 0; i < 50; i++) {
      DateTime now = rtc.now();
    
      lcd.setCursor(6, 1);
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
  
      lcd.setCursor(3, 0);
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
      controlFan();
      changeMode();

      if (client.connected()) {
        currentMillis=millis(); 
        webSocketClient.getData(data);    
        if (data.length() > 0) {
          Serial.println(data);
          
          DynamicJsonDocument doc(1024);
          deserializeJson(doc, data);
          
          String ten = doc["ten"];
          bool trangthai          = doc["trangthai"];
          bool chedo    = doc["chedo"];
          String thoigianmo = doc["thoigianmo"];
          String thoigiantat = doc["thoigiantat"];

          sprintf(onHourTens, "%d", now.hour()/10);
          sprintf(onHourUnits, "%d", now.hour()%10);

          sprintf(offHourTens, "%d", now.hour()/10);
          sprintf(offHourUnits, "%d", now.hour()%10);

          Serial.print("So sanh gio mo: ");
          if (*onHourTens == thoigianmo[0] && *onHourUnits == thoigianmo[1]) {
            Serial.println("Trung khop ne");
          } else {
            Serial.println("Khong trung roi, huhu");
          }
          Serial.print("So sanh gio tat: ");
          if (*offHourTens == thoigiantat[0] && *offHourUnits == thoigiantat[1]) {
            Serial.println("Trung khop ne");
          } else {
            Serial.println("Khong trung roi, huhu");
          }
//        Chế độ CHỈNH TAY
          if (!chedo) {
            
//          Điều khiển đèn 1
            if (ten == "den1") {
              if (trangthai) {
                Serial.print("Đèn 1 mở: "); Serial.println(trangthai);
                digitalWrite(bulb1, HIGH);
              } else {
                Serial.print("Đèn 1 mở: "); Serial.println(trangthai);
                digitalWrite(bulb1, LOW);
              }
            } else
            
  //          Điều khiển đèn 2
            if (ten == "den2") {
              if (trangthai) {
                Serial.print("Đèn 2 mở: "); Serial.println(trangthai);
                digitalWrite(bulb2, HIGH);
              } else {
                Serial.print("Đèn 2 mở: "); Serial.println(trangthai);
                digitalWrite(bulb2, LOW);
              }
            } else
            
  //          Điều khiển quạt
            if (ten == "quat") {
              if (trangthai) {
                Serial.print("Quạt mở: "); Serial.println(trangthai);
                digitalWrite(fan, HIGH);
              } else {
                Serial.print("Quạt mở: "); Serial.println(trangthai);
                digitalWrite(fan, LOW);
              }
            }
//        Chế độ TỰ ĐỘNG
          } else {
            
          }


          
          data="";
        }   
        delay(5);
        } else {
          wsconnect();
        }
    }
}
//*********************************************************************************************************************
//***************function definitions**********************************************************************************
void wsconnect(){
  // Connect to the websocket server
  if (client.connect(host, espport)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
      delay(1000);  
   
   if(handshakeFailed){
    handshakeFailed=0;
    ESP.restart();
    }
    handshakeFailed=1;
  }

  // Handshake with the server
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
    webSocketClient.getData(data);
     if (data.length() > 0) {
      Serial.println(data);
      data="";
    }
  } 
  else {
    Serial.println("Handshake failed.");
  }   
   delay(4000);  
   
   if(handshakeFailed){
    handshakeFailed=0;
    
    ESP.restart();
    }
    handshakeFailed=1;
}
