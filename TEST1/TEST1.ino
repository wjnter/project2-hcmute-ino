#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define WIFI_SSID "Phong 10"
#define WIFI_PASSWORD "12345789"

#define FIREBASE_HOST "hieu-9fb91.firebaseio.com"
#define FIREBASE_AUTH ""

#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11
#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE);

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

float h;
float t;

const int btnBulb3 = D0;
const int btnBulb1 = D5;
const int btnBulb2 = D7;

const int bulb3 = D4;
const int bulb1 = D6;
const int bulb2 = D8;

int statusBulb1 = 0;
int statusBulb2 = 0;
int statusBulb3 = 0;

String LED_STATUS1 ="";
String LED_STATUS2 ="";
String LED_STATUS3 ="";

void controlBulb1() {
  if (!digitalRead(btnBulb1)) {
    delay(30);
    if (!digitalRead(btnBulb1)) {
      statusBulb1 = !statusBulb1;
      Serial.print("Trang thai nut nhan 1: ");
      Serial.println(statusBulb1);
      while (!digitalRead(btnBulb1));
      if ( LED_STATUS1 == "ON")
      {Firebase.setString("LED_STATUS1", "OFF");}
      else {Firebase.setString("LED_STATUS1", "ON");}
    }
  }
  if (statusBulb1 == 1 || LED_STATUS1 =="ON") {
    digitalWrite(bulb1, HIGH);
  } else {
    digitalWrite(bulb1, LOW);
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
      if ( LED_STATUS2 == "ON")
      {Firebase.setString("LED_STATUS2", "OFF");}
      else {Firebase.setString("LED_STATUS2", "ON");}
    }
  }
  if (statusBulb2 == 1 || LED_STATUS2 =="ON") {
    digitalWrite(bulb2, HIGH);
  } else {
    digitalWrite(bulb2, LOW);
  }
}
void controlBulb3() {
  if (!digitalRead(btnBulb3)) {
    delay(30);
    if (!digitalRead(btnBulb3)) {
      statusBulb3 = !statusBulb3;
      Serial.print("Trang thai nut nhan 1: ");
      Serial.println(statusBulb3);
      while (!digitalRead(btnBulb3));
      if ( LED_STATUS3 == "ON")
      {Firebase.setString("LED_STATUS3", "OFF");}
      else {Firebase.setString("LED_STATUS3", "ON");}
    }
  }
  if (statusBulb3 == 1 || LED_STATUS3 =="ON") {
    digitalWrite(bulb3, HIGH);
  } else {
    digitalWrite(bulb3, LOW);
  }
}
void dht11()
{
    h = dht.readHumidity();
    t = dht.readTemperature();         
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
    delay(800);
    Firebase.setFloat("Nhiệt độ", t);
    Firebase.setFloat("Độ ẩm", h);
    
 }
  void displaydht11()
 {
      lcd.setCursor(2, 0); lcd.print(h);
      lcd.setCursor(10, 0);lcd.print(t);
 }
 void displaybtn()
 {
    if(statusBulb1 == 1 || LED_STATUS1 =="ON")
   {
    lcd.setCursor(1, 1); lcd.print("ON ");
   }
   else 
   {
    lcd.setCursor(1, 1); lcd.print("OFF");
   }
   
   if(statusBulb2 == 1 || LED_STATUS2 == "ON")
   {
    lcd.setCursor(6, 1); lcd.print("ON ");
   }
   else 
   {
    lcd.setCursor(6, 1); lcd.print("OFF");
   }

   if(statusBulb3 == 1 || LED_STATUS3 == "ON")
   {
    lcd.setCursor(11, 1); lcd.print("ON ");
   }
   else 
   {
    lcd.setCursor(11, 1); lcd.print("OFF");
   }
    
  }
void setup() {
  Serial.begin(9600);
  //SETUPBTN
  pinMode(btnBulb1, INPUT); 
  pinMode(btnBulb2, INPUT); 
  pinMode(btnBulb2, INPUT); 
  
  pinMode(bulb1, OUTPUT);
  pinMode(bulb2, OUTPUT);
  pinMode(bulb3, OUTPUT);

  digitalWrite(bulb1, LOW);
  digitalWrite(bulb2, LOW);
  digitalWrite(bulb3, LOW);
  //SETUPBTN
  
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //TTBUTTON ON FIREBASE//
  Firebase.setString("LED_STATUS1", "OFF");
  Firebase.setString("LED_STATUS2", "OFF");
  Firebase.setString("LED_STATUS3", "OFF");

  //setup LCD
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0, 0); lcd.print("H:");
  lcd.setCursor(7, 0);lcd.print("%");
  lcd.setCursor(8, 0);  lcd.print("t:");
  lcd.setCursor(15, 0); lcd.print("C");
  lcd.setCursor(0, 1);lcd.print("1");
  lcd.setCursor(5, 1);lcd.print("2");
  lcd.setCursor(10, 1);lcd.print("3");
  //SETUP LCD
}
void loop() {
  LED_STATUS1 = Firebase.getString("LED_STATUS1");
  LED_STATUS2 = Firebase.getString("LED_STATUS2");                                      // get ld status input from firebase
  LED_STATUS3 = Firebase.getString("LED_STATUS3");  
  // get ld status input from firebase
  dht11();
  // get ld status input from firebase
  controlBulb1();
  controlBulb2();
  controlBulb3();
  displaydht11();
  displaybtn();

}
