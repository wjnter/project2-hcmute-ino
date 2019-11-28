#include <ArduinoJson.h>
//String json = "[{\"id\":1,\"ten\":\"den1\",\"giatri\":0,\"thoigiandoc\":0,\"trangthai\":true,\"chedo\":false,\"thoigianmo\":\"16:24:00\",\"thoigiantat\":\"20:32:00\"},{\"id\":2,\"ten\":\"den2\",\"giatri\":0,\"thoigiandoc\":0,\"trangthai\":true,\"chedo\":false,\"thoigianmo\":\"16:24:00\",\"thoigiantat\":\"20:32:00\"},{\"id\":3,\"ten\":\"quat\",\"giatri\":0,\"thoigiandoc\":0,\"trangthai\":true,\"chedo\":false,\"thoigianmo\":\"16:24:00\",\"thoigiantat\":\"20:32:00\"},{\"id\":1,\"ten\":\"cbnhietdo\",\"giatri\":30,\"thoigiandoc\":2,\"trangthai\":0,\"chedo\":0,\"thoigianmo\":0,\"thoigiantat\":0}]";
String json = "{\"id\":1,\"ten\":\"den1\",\"giatri\":0,\"thoigiandoc\":0,\"trangthai\":true,\"chedo\":false,\"thoigianmo\":\"18:24:00\",\"thoigiantat\":\"21:58:00\"}";

String thoigianmo = "";
String thoigiantat = "";
bool isArr = false;
void setup() {
  Serial.begin(9600);
//  // put your setup code here, to run once:
//  StaticJsonDocument<200> doc1;
//  deserializeJson(doc1, "[{\"hello\":\"world\"}, {\"hello\":\"world\"} ]");
//  JsonObject object = doc1.as<JsonObject>();
//  Serial.println(object.isNull()); // false
  StaticJsonDocument<1024> doc;
  deserializeJson(doc, json);

  
  JsonObject object = doc.as<JsonObject>();
  isArr = object.isNull();

  if (isArr) {
    
    // Parse the JSON input
    DeserializationError err = deserializeJson(doc, json);
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
    int chedo = den1["chedo"];
    thoigianmo = den1["thoigianmo"].as<String>();
    thoigiantat = den1["thoigiantat"].as<String>();
    
    Serial.print("ten: "); Serial.println(tenDen1);
    Serial.print("trangthai: "); Serial.println(trangthaiDen1);
    Serial.print("chedo: "); Serial.println(chedo);
    Serial.print("thoigianmo: "); Serial.println(thoigianmo);
    Serial.print("thoigiantat: "); Serial.println(thoigiantat);
  
    Serial.println("Đèn 2");
     // Đèn 2
    const char* tenDen2 = den2["ten"];
    long trangthaiDen2 = den2["trangthai"];
    
    Serial.print("ten: "); Serial.println(tenDen2);
    Serial.print("trangthai: "); Serial.println(trangthaiDen2);
  
    Serial.println("Quạt");
    const char* tenQuat = quat["ten"];
    long trangthaiQuat = quat["trangthai"];
    
    Serial.print("ten: "); Serial.println(tenQuat);
    Serial.print("trangthai: "); Serial.println(trangthaiQuat);
  
    Serial.println("Nhiệt độ");
     // Nhiệt độ
    const char* tenNhietDo = nhietdo["ten"];
    float giatriNhietDo = nhietdo["giatri"];
    
    Serial.print("ten: "); Serial.println(tenNhietDo);
    Serial.print("giatri: "); Serial.print(giatriNhietDo); Serial.println("do C");
  } else {
//    DynamicJsonDocument doc(1024);
//    deserializeJson(doc, json);
    String ten = doc["ten"];
    bool trangthai = doc["trangthai"];
    bool chedo = doc["chedo"];
    float giatri = doc["giatri"];
    thoigianmo = doc["thoigianmo"].as<String>();
    thoigiantat = doc["thoigiantat"].as<String>();

    Serial.print("Tên: "); Serial.println(ten);
    Serial.print("Trạng thái: "); Serial.println(trangthai);
    Serial.print("Chế độ: "); Serial.println(chedo);
    Serial.print("Giá trị: "); Serial.println(giatri);
    Serial.print("Thời gian mở: "); Serial.println(thoigianmo);
    Serial.print("Thời gian tắt: "); Serial.println(thoigiantat);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
