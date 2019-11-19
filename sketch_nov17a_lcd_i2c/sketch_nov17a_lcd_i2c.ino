#include <ESP8266WiFi.h>
#include <WebSocketClient.h>
const char* ssid     = "80 dqh lau 2.2";
const char* password = "80duongquangham";
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

int const den1 = D5;
int const den2 = D6;

void setup() {
  Serial.begin(9600);
//    pinMode(readPin, INPUT);     // Initialize the LED_BUILTIN pin as an output

  delay(10);

  // We start by connecting to a WiFi network
  pinMode(den1, OUTPUT); 
  pinMode(den2, OUTPUT); 
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
  lcd.backlight();
  lcd.setCursor(0, 0); lcd.print("H:");
  lcd.setCursor(7, 0);lcd.print("%");
  lcd.setCursor(8, 0);  lcd.print("t:");
  lcd.setCursor(15, 0); lcd.print("C");
  lcd.setCursor(0, 1);lcd.print("1");
  lcd.setCursor(5, 1);lcd.print("2");
  lcd.setCursor(10, 1);lcd.print("3123123");
  
//  wifi_set_sleep_type(LIGHT_SLEEP_T);
}
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(den1, HIGH);
  digitalWrite(den2, HIGH);
  delay(500);
  digitalWrite(den1, LOW);
  digitalWrite(den2, LOW);
  delay(500);
}
