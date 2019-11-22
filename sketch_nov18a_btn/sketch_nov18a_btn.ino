#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>

#include <WebSocketClient.h>

const char* ssid     = "80 dqh lau 2.2";
const char* password = "80duongquangham";
  
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);  

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

void controlBulb1() {
  if (!digitalRead(btnBulb1)) {
    delay(30);
    if (!digitalRead(btnBulb1)) {
      if (statusMode) {
        Serial.println("Không thể điều khiển ở chế độ tự động");
        while (!digitalRead(btnBulb1));
      } else {
        statusBulb1 = !statusBulb1;
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
}

void controlBulb2() {
  if (!digitalRead(btnBulb2)) {
    delay(30);
    if (!digitalRead(btnBulb2)) {
      if (statusMode) {
        Serial.println("Không thể điều khiển ở chế độ tự động");
        while (!digitalRead(btnBulb2));
      } else {
        statusBulb2 = !statusBulb2;
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
}

void controlFan() {
  if (!digitalRead(btnFan)) {
    delay(30);
    if (!digitalRead(btnFan)) {
      if (statusMode) {
        Serial.println("Không thể điều khiển ở chế độ tự động");
        while (!digitalRead(btnFan));
      } else {
        statusFan = !statusFan;
        while (!digitalRead(btnFan));
        if (statusFan) {
          Serial.print("Quạt mở: "); Serial.println(statusFan);
        } else {
          Serial.print("Quạt mở: "); Serial.println(statusFan);
        }
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
      } else {
        Serial.println("Chế độ tự chỉnh"); 
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
  pinMode(btnMode, INPUT);
  
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
  controlBulb1();
  controlBulb2();
  controlFan();
  changeMode();
}
