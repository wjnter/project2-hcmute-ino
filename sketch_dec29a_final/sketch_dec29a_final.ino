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

int onHourTens = 0;   int onHourUnits = 0;  int onHour = 0;
int offHourTens = 0;  int offHourUnits = 0; int offHour = 0;

int onMinuteTens = 0;   int onMinuteUnits = 0;  int onMinute = 0;
int offMinuteTens = 0;  int offMinuteUnits = 0; int offMinute = 0;

bool flag = true;
bool isArr = false;
bool isArrTheFirst = false;
bool chedo = true;
bool trangthai = false;
float giatri = 0;
String ten = "";

int outputPin = A0;
float analogValue = 0;
float millivolts = 0;
float celsius = 0;
float prevCelsius = 0;

const int btnFan = 13;  //D7
const int btnBulb2 = 0; //D3
const int btnBulb1 = 2; //D4
const int btnMode = 12;  //D6


const int bulb1 = D5;
const int bulb2 = D8;
const int fan = D0;

bool statusBulb1 = false;
bool prevStatusBulb1 = false;
bool statusBulb2 = false;
bool prevStatusBulb2 = false;
bool statusFan = false;
bool prevStatusFan = false;
bool statusMode = false; //mode false => manual, true => auto

boolean handshakeFailed=0;

//biến dữ liệu lấy về từ server - data
String data= "";
String thoigianmo = "00:00:00";
String thoigiantat = "00:00:01";
//biến dữ liệu gửi lên server - json
String json = "";

char path[] = "/realtime-data?username=dangtruongsinh&password=123";   //identifier of this device

const char* ssid     = "80 dqh lau 2.2";
const char* password = "80duongquangham";
//const char* ssid     = "D304-1_NoPassword";
//const char* password = "NoPassword";

//const char* ssid     = "vnpt-Phuong Du";
//const char* password = "06012010a";

char* host = "smart.j.layershift.co.uk";  //thay domain vao
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
      if (chedo) {
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
        jsonBulb1["thoigianmo"] = thoigianmo;
        jsonBulb1["thoigiantat"] = thoigiantat;

        serializeJson(jsonBulb1, Serial);
        serializeJson(jsonBulb1, json);
//        Send data to Server
        webSocketClient.sendData(json);
        json = "";
        
        while (!digitalRead(btnBulb1));
      }
    }
  }
}

void controlBulb2() {
  DynamicJsonDocument jsonBulb2(1024);
  
  if (!digitalRead(btnBulb2)) {
    delay(30);
    if (!digitalRead(btnBulb2)) {
      if (chedo) {
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
        jsonBulb2["thoigianmo"] = thoigianmo;
        jsonBulb2["thoigiantat"] = thoigiantat;

        serializeJson(jsonBulb2, Serial);
        serializeJson(jsonBulb2, json);
//        Send data to Server
        webSocketClient.sendData(json);
        json = "";

        while (!digitalRead(btnBulb2));
      }
    }
  }
}

void controlFan() {
  DynamicJsonDocument jsonFan(1024);
  if (!digitalRead(btnFan)) {
    delay(30);
    if (!digitalRead(btnFan)) {
      if (chedo) {
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
        jsonFan["thoigianmo"] = thoigianmo;
        jsonFan["thoigiantat"] = thoigiantat;


        serializeJson(jsonFan, Serial);
        serializeJson(jsonFan, json);
//        Send data to Server
        webSocketClient.sendData(json);
        json = "";
        
        while (!digitalRead(btnFan));
      }
    }
  }   
}


void changeMode() {
  StaticJsonDocument<1024> jsonMode;
  if (!digitalRead(btnMode)) {
    delay(30);
    if (!digitalRead(btnMode)) {
      statusMode = !statusMode;
      while (!digitalRead(btnMode));

      jsonMode["ten"] = "chedo";
      jsonMode["chedo"]   = statusMode;
      jsonMode["thoigianmo"] = thoigianmo;
      jsonMode["thoigiantat"] = thoigiantat;
  
      serializeJson(jsonMode, Serial);
      serializeJson(jsonMode, json);
  //        Send data to Server
      webSocketClient.sendData(json);
      json = "";

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
  digitalWrite(fan, HIGH);
  
  lcd.begin(20,4);   
  lcd.setCursor(0, 0);
  lcd.print("Setting up");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print("Che do: ");
  lcd.setCursor(8, 2);
  if (chedo) {
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
  
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//auto update from computer time
//    rtc.adjust(DateTime(2019, 12, 29, 21, 13, 0));// to set the time manualy 


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
  for (int i = 0; i < 150; i++) {
//    lcd.clear();
//    lcd.setCursor(0, 2);
//    lcd.print("Che do: ");
//    lcd.setCursor(8, 2);
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
      webSocketClient.getData(data);    
      if (data.length() > 0) {
        Serial.println("");
        Serial.println(data);
        StaticJsonDocument<1024> doc;
        // Parse the JSON input
        DeserializationError err = deserializeJson(doc, data);
        // Parse succeeded?
        if (err) {
        Serial.print(F("deserializeJson() returned "));
        Serial.println(err.c_str());
        return;
        }
        // Get the first element of the array
        JsonObject den1 = doc[0];
        JsonObject den2 = doc[1];
        JsonObject quat = doc[2];
        JsonObject nhietdo = doc[3];

        Serial.println("Đèn 1");
        // Đèn 1
        const char* tenDen1 = den1["ten"];
        long trangthaiDen1 = den1["trangthai"];
        statusBulb1 = trangthaiDen1;
        chedo = den1["chedo"];
        thoigianmo = den1["thoigianmo"].as<String>();
        thoigiantat = den1["thoigiantat"].as<String>();

        statusMode = chedo;
        lcd.setCursor(8, 2);
        if (chedo) {
          Serial.println("Chế độ tự động");
          lcd.print("AUTOMA");
        } else {
          Serial.println("Chế độ tự chỉnh"); 
          lcd.print("MANUAL");
        }
        Serial.print("trangthai: "); Serial.println(trangthaiDen1);
        Serial.print("chedo: "); Serial.println(chedo);
        Serial.print("thoigianmo: "); Serial.println(thoigianmo);
        Serial.print("thoigiantat: "); Serial.println(thoigiantat);

        Serial.println("Đèn 2");
        // Đèn 2
        const char* tenDen2 = den2["ten"];
        long trangthaiDen2 = den2["trangthai"];
        statusBulb2 = trangthaiDen2;
        
        Serial.print("trangthai: "); Serial.println(trangthaiDen2);
        
        Serial.println("Quạt");
        //Quạt
        const char* tenQuat = quat["ten"];
        long trangthaiQuat = quat["trangthai"];
        statusFan = trangthaiQuat;
            
        Serial.print("trangthai: "); Serial.println(trangthaiQuat);

        Serial.println("Nhiệt độ");
        // Nhiệt độ
        const char* tenNhietDo = nhietdo["ten"];
        float giatriNhietDo = nhietdo["giatri"];
        
        Serial.print("giatri: "); Serial.print(giatriNhietDo); Serial.println("do C");  

        lcd.setCursor(8, 2);
        // When reset
        if (flag) {
//          Điều khiển đèn 1
          if (trangthaiDen1) {
            Serial.print("Đèn 1 mở: "); Serial.println(trangthaiDen1);
            digitalWrite(bulb1, HIGH);
          } else {
            Serial.print("Đèn 1 mở: "); Serial.println(trangthaiDen1);
            digitalWrite(bulb1, LOW);
          }
//          Điều khiển đèn 2
          if (trangthaiDen2) {
            Serial.print("Đèn 2 mở: "); Serial.println(trangthaiDen2);
            digitalWrite(bulb2, HIGH);
          } else {
            Serial.print("Đèn 2 mở: "); Serial.println(trangthaiDen2);
            digitalWrite(bulb2, LOW);
          }
//          Điều khiển quạt
          if (trangthaiQuat) {
            Serial.print("Quạt mở: "); Serial.println(trangthaiQuat);
            digitalWrite(fan, LOW);
          } else {
            Serial.print("Quạt mở: "); Serial.println(trangthaiQuat);
            digitalWrite(fan, HIGH);
          }
          flag = false;
        } else {
          //        Chế độ CHỈNH TAY
          if (!chedo) {
            Serial.println("Chế độ tự chỉnh"); 
            lcd.print("MANUAL");
//          Điều khiển đèn 1
            
//            if (prevStatusBulb1 != statusBulb1) {
//              prevStatusBulb1 = statusBulb1;
//              if (statusBulb1) {
//                Serial.print("Đèn 1 mở: "); Serial.println(statusBulb1);
//                digitalWrite(bulb1, HIGH);
//              } else {
//                Serial.print("Đèn 1 mở: "); Serial.println(statusBulb1);
//                digitalWrite(bulb1, LOW);
//              }
//            }

                if (statusBulb1) {
                Serial.print("Đèn 1 mở: "); Serial.println(statusBulb1);
                digitalWrite(bulb1, HIGH);
              } else {
                Serial.print("Đèn 1 mở: "); Serial.println(statusBulb1);
                digitalWrite(bulb1, LOW);
              }

//          Điều khiển đèn 2

//            if (prevStatusBulb2 != statusBulb2) {
//              prevStatusBulb2 = statusBulb2;
//              if (statusBulb2) {
//                Serial.print("Đèn 2 mở: "); Serial.println(statusBulb2);
//                digitalWrite(bulb2, HIGH);
//              } else {
//                Serial.print("Đèn 2 mở: "); Serial.println(statusBulb2);
//                digitalWrite(bulb2, LOW);
//              }
//            }

              if (statusBulb2) {
                Serial.print("Đèn 2 mở: "); Serial.println(statusBulb2);
                digitalWrite(bulb2, HIGH);
              } else {
                Serial.print("Đèn 2 mở: "); Serial.println(statusBulb2);
                digitalWrite(bulb2, LOW);
              }
              
//          Điều khiển quạt

//            if (prevStatusFan != statusFan) {
//              prevStatusFan = statusFan;
//              if (statusFan) {
//                Serial.print("Quạt mở: "); Serial.println(statusFan);
//                digitalWrite(fan, HIGH);
//              } else {
//                Serial.print("Quạt mở: "); Serial.println(statusFan);
//                digitalWrite(fan, LOW);
//              }
//            }
//            Serial.println("alo alo");
//            Serial.println(giatriNhietDo, 2);

            if (statusFan) {
                Serial.print("Quạt mở: "); Serial.println(statusFan);
                digitalWrite(fan, LOW);
              } else {
                Serial.print("Quạt mở: "); Serial.println(statusFan);
                digitalWrite(fan, HIGH);
              }
              
//          Chế độ TỰ ĐỘNG
          } else {
            Serial.println("Chế độ tự động ..");
            lcd.print("AUTOMA");
            //Chuyển thời gian về Integer
            onHourTens = thoigianmo[0] - 48;
            onHourUnits = thoigianmo[1] - 48;
            onMinuteTens = thoigianmo[3] - 48;
            onMinuteUnits = thoigianmo[4] - 48;
            offHourTens = thoigiantat[0] - 48;
            offHourUnits = thoigiantat[1] - 48;
            offMinuteTens = thoigiantat[3] - 48;
            offMinuteUnits = thoigiantat[4] - 48;                    
            
            onHour = onHourTens*10 + onHourUnits;
            onMinute = onMinuteTens*10 + onMinuteUnits;
            offHour = offHourTens*10 + offHourUnits;
            offMinute = offMinuteTens*10 + offMinuteUnits;
            
            Serial.print("So sánh thời gian mở: ");
            if ((now.hour() > onHour) && (now.hour() < offHour)) {
              Serial.print("Đèn 1 mở: ");
              digitalWrite(bulb1, HIGH);
              Serial.print("Đèn 2 mở: ");
              digitalWrite(bulb2, HIGH);
            } else 
            if ((now.hour() == onHour) || (now.hour() == offHour)) {
              if (now.minute() >= onMinute) {
                if (now.minute() < offMinute) {
                  Serial.print("Đèn 1 mở: ");
                  digitalWrite(bulb1, HIGH);
                  Serial.print("Đèn 2 mở: ");
                  digitalWrite(bulb2, HIGH);
                }
              }
            } else {
              Serial.print("Nothing onHour");
            }
            if ((now.hour() < onHour) || (now.hour() > offHour)) {
              Serial.print("Đèn 1 đóng: ");
                digitalWrite(bulb1, LOW);
                Serial.print("Đèn 2 đóng: ");
                digitalWrite(bulb2, LOW);
            } else 
            if ((now.hour() == onHour) || (now.hour() == offHour)) {
              if ((now.minute() < onMinute) || (now.minute() >= offMinute)) {
                Serial.print("Đèn 1 đóng: ");
                  digitalWrite(bulb1, LOW);
                  Serial.print("Đèn 2 đóng: ");
                  digitalWrite(bulb2, LOW);
              }
            } else {
              Serial.println("Nothing offHour");
            }
          }
        }
        
        data = "";
      }
      delay(5);
    } else {
      wsconnect();
    }
  }
  analogValue = analogRead(outputPin);
  millivolts = (analogValue/1023.0) * 3300; //3300 is the voltage provided by NodeMCU
  celsius = millivolts/10;
//          Hiển thị nhiệt độ
  lcd.setCursor(0, 3);
  lcd.print("Nhiet do: ");
  lcd.print(celsius);

  
  DynamicJsonDocument jsonTemp(1024);
  jsonTemp["id"] = 1;
  jsonTemp["ten"] = "cbnhietdo";
  jsonTemp["giatri"] = celsius;
  jsonTemp["thoigiandoc"] = 0;
  jsonTemp["trangthai"]   = false;
  jsonTemp["chedo"]   = chedo;
  jsonTemp["thoigianmo"] = thoigianmo;
  jsonTemp["thoigiantat"] = thoigiantat;

  serializeJson(jsonTemp, Serial);
  serializeJson(jsonTemp, json);
//        Send data to Server
  webSocketClient.sendData(json);
  json = "";
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
