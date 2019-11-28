#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
String json = "[{\"id\":1,\"ten\":\"den1\",\"giatri\":0,\"thoigiandoc\":0,\"trangthai\":true,\"chedo\":false,\"thoigianmo\":\"16:24:00\",\"thoigiantat\":\"20:32:00\"},{\"id\":2,\"ten\":\"den2\",\"giatri\":0,\"thoigiandoc\":0,\"trangthai\":true,\"chedo\":false,\"thoigianmo\":\"16:24:00\",\"thoigiantat\":\"20:32:00\"},{\"id\":3,\"ten\":\"quat\",\"giatri\":0,\"thoigiandoc\":0,\"trangthai\":true,\"chedo\":false,\"thoigianmo\":\"16:24:00\",\"thoigiantat\":\"20:32:00\"},{\"id\":1,\"ten\":\"cbnhietdo\",\"giatri\":30,\"thoigiandoc\":2,\"trangthai\":0,\"chedo\":0,\"thoigianmo\":0,\"thoigiantat\":0}]";
String data = "{\"id\":1,\"ten\":\"den1\",\"giatri\":0,\"thoigiandoc\":0,\"trangthai\":true,\"chedo\":false,\"thoigianmo\":\"18:24:00\",\"thoigiantat\":\"21:58:00\"}";

String thoigianmo = "hello";
String thoigiantat = "end it";
void setup() {
  Serial.begin(9600);
  Serial.println(thoigianmo);
  Serial.println(thoigiantat);
  thoigianmo = "";
  thoigiantat = "";
  
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, data);
//  JsonObject obj = doc.as<JsonObject>();
  
  
  String ten = doc["ten"];
  bool trangthai = doc["trangthai"];
  bool chedo = doc["chedo"];
  float giatri = doc["giatri"];
//  String thoigianmo = doc["thoigianmo"];
//  String thoigiantat = doc["thoigiantat"];

  thoigianmo = doc["thoigianmo"].as<String>();
  thoigiantat = doc["thoigiantat"].as<String>();
  Serial.print("Tên: "); Serial.println(ten);
  Serial.print("Trạng thái: "); Serial.println(trangthai);
  Serial.print("Chế độ: "); Serial.println(chedo);
  Serial.print("Giá trị: "); Serial.println(giatri);
  Serial.print("Thời gian mở: "); Serial.println(thoigianmo);
  Serial.print("Thời gian tắt: "); Serial.println(thoigiantat);


}


void loop() {
  // put your main code here, to run repeatedly:

}


//const int btnFan = 13;  //D7
//const int btnBulb2 = 0; //D3
//const int btnBulb1 = 2; //D4
//const int btnMode = 12;  //D0
//
//
//const int bulb1 = D5;
//const int bulb2 = D8;
//const int fan = D0;
//deserialize Array

//  // Compute the required size
////  const int capacity = JSON_ARRAY_SIZE(4) + 4*JSON_OBJECT_SIZE(8);
//  //Đm tính trên web thì ra 915 nhưng thực tế có 576
//  // Allocate the JsonDocument
////  Serial.print("capacity: "); Serial.println(capacity);
//  StaticJsonDocument<1024> doc;
//  // Parse the JSON input
//  DeserializationError err = deserializeJson(doc, json);
//  // Parse succeeded?
//  if (err) {
//  Serial.print(F("deserializeJson() returned "));
//  Serial.println(err.c_str());
//  return;
//  }
//  // Get the first element of the array
//  JsonObject den1 = doc[0];
//  JsonObject den2 = doc[1];
//  JsonObject quat = doc[2];
//  JsonObject nhietdo = doc[3];
//
//  Serial.println("Đèn 1");
//  // Đèn 1
//  const char* tenDen1 = den1["ten"];
//  long trangthaiDen1 = den1["trangthai"];
//  int chedo = den1["chedo"];
//  String thoigianmo = den1["thoigianmo"];
//  String thoigiantat = den1["thoigiantat"];
//  
//  Serial.print("ten: "); Serial.println(tenDen1);
//  Serial.print("trangthai: "); Serial.println(trangthaiDen1);
//  Serial.print("chedo: "); Serial.println(chedo);
//  Serial.print("thoigianmo: "); Serial.println(thoigianmo);
//  Serial.print("thoigiantat: "); Serial.println(thoigiantat);
//
//  Serial.println("Đèn 2");
//   // Đèn 2
//  const char* tenDen2 = den2["ten"];
//  long trangthaiDen2 = den2["trangthai"];
////  int chedo = den1["chedo"];
////  float giatriDen2 = den2["giatri"];
////  String thoigianmo = den2["thoigianmo"];
////  String thoigiantat = den2["thoigiantat"];
//  
//  Serial.print("ten: "); Serial.println(tenDen2);
//  Serial.print("trangthai: "); Serial.println(trangthaiDen2);
////  Serial.print("chedo: "); Serial.println(chedo);
////  Serial.print("thoigianmo: "); Serial.println(thoigianmo);
////  Serial.print("thoigiantat: "); Serial.println(thoigiantat);
//
//  Serial.println("Quạt");
//  const char* tenQuat = quat["ten"];
//  long trangthaiQuat = quat["trangthai"];
////  int chedo = quat["chedo"];
////  float giatriDen1 = quat["giatri"];
////  String thoigianmo = quat["thoigianmo"];
////  String thoigiantat = quat["thoigiantat"];
//  
//  Serial.print("ten: "); Serial.println(tenQuat);
//  Serial.print("trangthai: "); Serial.println(trangthaiQuat);
////  Serial.print("chedo: "); Serial.println(chedo);
////  Serial.print("giatri: "); Serial.println(giatriDen1);
////  Serial.print("thoigianmo: "); Serial.println(thoigianmo);
////  Serial.print("thoigiantat: "); Serial.println(thoigiantat);
//
//  Serial.println("Nhiệt độ");
//   // Nhiệt độ
//  const char* tenNhietDo = nhietdo["ten"];
////  long trangthaiDen1 = nhietdo["trangthai"];
////  int chedo = nhietdo["chedo"];
//  float giatriNhietDo = nhietdo["giatri"];
////  String thoigianmo = den1["thoigianmo"];
////  String thoigiantat = den1["thoigiantat"];
//  
//  Serial.print("ten: "); Serial.println(tenNhietDo);
////  Serial.print("trangthai: "); Serial.println(trangthaiDen1);
////  Serial.print("chedo: "); Serial.println(chedo);
//  Serial.print("giatri: "); Serial.print(giatriNhietDo); Serial.println("do C");
////  Serial.print("thoigianmo: "); Serial.println(thoigianmo);
////  Serial.print("thoigiantat: "); Serial.println(thoigiantat);
//
//
//  if (trangthaiDen1) {
//    Serial.print("Đèn 1 mở: "); Serial.println(trangthaiDen1);
//    digitalWrite(bulb1, HIGH);
//  } else {
//    Serial.print("Đèn 1 mở: "); Serial.println(trangthaiDen1);
//    digitalWrite(bulb1, LOW);
//  }
//  if (trangthaiDen2) {
//    Serial.print("Đèn 2 mở: "); Serial.println(trangthaiDen2);
//    digitalWrite(bulb2, HIGH);
//  } else {
//    Serial.print("Đèn 2 mở: "); Serial.println(trangthaiDen2);
//    digitalWrite(bulb2, LOW);
//  }
//  if (trangthaiQuat) {
//    Serial.print("Quạt mở: "); Serial.println(trangthaiQuat);
//    digitalWrite(fan, HIGH);
//  } else {
//    Serial.print("Quạt mở: "); Serial.println(trangthaiQuat);
//    digitalWrite(fan, LOW);
//  }
//  
//  lcd.setCursor(0, 0);
//  lcd.print("Nhietdo: "); lcd.print(giatriNhietDo);
