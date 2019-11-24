#include <ArduinoJson.h>
#include <String.h>

char json[] = "{\"id\":1,\"ten\":\"den1\",\"giatri\":0,\"thoigiandoc\":0,\"trangthai\":false,\"chedo\":false,\"thoigianmo\":\"16:24:00\",\"thoigiantat\":\"20:32:00\"}";
char* json_string[256];

char onHourTens[2];
char onHourUnits[2];
char offHourTens[2];
char offHourUnits[2];

void setup() {
  Serial.begin(9600);
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, json);
  
  const char* ten = doc["ten"];
  bool trangthai          = doc["trangthai"];
  bool chedo    = doc["chedo"];
  const char* thoigianmo = doc["thoigianmo"];
  const char* thoigiantat = doc["thoigiantat"];

  Serial.println(ten);
  Serial.println(trangthai);
  Serial.println(chedo);
//  strcat(openingHour, thoigianmo[0]);
//  strcat(openingHour, thoigianmo[1]);
////  Serial.print("Gio mo: "); Serial.print(thoigianmo[0]);Serial.println(thoigianmo[1]);
//  Serial.print("Gio mo: "); Serial.println(openingHour);
  Serial.println(thoigiantat);
  strcpy(result,thoigianmo); // copy string one into the result.
//  strcat(result,thoigianmo[1]); // append string two to the result
  Serial.println(result);
  
  DynamicJsonDocument doc1(1024);
  doc1["id"] = 1;
  doc1["ten"] = "den1";
  doc1["giatri"] = 0;
  doc1["thoigiandoc"] = 0;
  doc1["trangthai"]   = false;
  doc1["chedo"]   = false;
  doc1["thoigiantat"] = "16:24:00";
  doc1["thoigiantat"] = "20:32:00";

  serializeJson(doc1, Serial);
  
  // compute the required size
  const size_t CAPACITY = JSON_ARRAY_SIZE(3);
  
  // allocate the memory for the document
  StaticJsonDocument<CAPACITY> doc2;
  
  // create an empty array
  JsonArray array = doc2.to<JsonArray>();
  
  // add some values
  array.add("hello");
  array.add(42);
  array.add(3.14);
  
  // serialize the array and send the result to Serial
  serializeJson(doc2, Serial);
}

void loop() {
  // put your main code here, to run repeatedly:

}
