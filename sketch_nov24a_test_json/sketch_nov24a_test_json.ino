#include <ArduinoJson.h>
#include <String.h>

char json[] = "{\"id\":1,\"ten\":\"den1\",\"giatri\":0,\"thoigiandoc\":0,\"trangthai\":false,\"chedo\":false,\"thoigianmo\":\"16:24:00\",\"thoigiantat\":\"20:32:00\"}";
char* json_string[256];

String ten = "";
bool trangthai          = false;
bool chedo    = false;
String thoigianmo = "";
String thoigiantat = "";

int onHourTens = 0;   int onHourUnits = 0;  int onHour = 0;
int offHourTens = 0;  int offHourUnits = 0; int offHour = 0;

int onMinuteTens = 0;   int onMinuteUnits = 0;  int onMinute = 0;
int offMinuteTens = 0;  int offMinuteUnits = 0; int offMinute = 0;

void setup() {
  Serial.begin(9600);
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, json);
  
  ten = doc["ten"].as<String>();
  trangthai          = doc["trangthai"];
  chedo    = doc["chedo"];
  thoigianmo = doc["thoigianmo"].as<String>();
  thoigiantat = doc["thoigiantat"].as<String>();

  Serial.print("Gio: "); Serial.print(thoigianmo[0]); Serial.println(thoigianmo[1]);
  onHourTens = thoigianmo[0] - 48;
  onHourUnits = thoigianmo[1] - 48;
  onMinuteTens = thoigianmo[3] - 48;
  onMinuteUnits = thoigianmo[4] - 48;
  
  onHour = onHourTens*10 + onHourUnits;
  onMinute = onMinuteTens*10 + onMinuteUnits;
  Serial.print("Gio kieu int: "); Serial.println(onHour); 
  Serial.print("Phut kieu int: "); Serial.println(onMinute);
  
  Serial.println(ten);
  Serial.println(trangthai);
  Serial.println(chedo);
  Serial.println(thoigianmo);
  Serial.println(thoigiantat);
 
}

void loop() {
  // put your main code here, to run repeatedly:

}

 
//  DynamicJsonDocument doc1(1024);
//  doc1["id"] = 1;
//  doc1["ten"] = "den1";
//  doc1["giatri"] = 0;
//  doc1["thoigiandoc"] = 0;
//  doc1["trangthai"]   = false;
//  doc1["chedo"]   = false;
//  doc1["thoigiantat"] = "16:24:00";
//  doc1["thoigiantat"] = "20:32:00";
//
//  serializeJson(doc1, Serial);
//  
//  // compute the required size
//  const size_t CAPACITY = JSON_ARRAY_SIZE(3);
//  
//  // allocate the memory for the document
//  StaticJsonDocument<CAPACITY> doc2;
//  
//  // create an empty array
//  JsonArray array = doc2.to<JsonArray>();
//  
//  // add some values
//  array.add("hello");
//  array.add(42);
//  array.add(3.14);
//  
//  // serialize the array and send the result to Serial
//  serializeJson(doc2, Serial);
