#include <Servo.h>

#include <ESP8266WiFi.h>
#include <WebSocketClient.h>
#include <ArduinoJson.h>

boolean handshakeFailed=0;

String data= "";
String json = "";
String thoigianmo = "00:00:00";
String thoigiantat = "00:00:01";

bool flag = 0;
char path[] = "/realtime-data?username=dangtruongsinh&password=123";   //identifier of this device

const char* ssid     = "80 dqh lau 2.2";
const char* password = "80duongquangham";

//const char* ssid     = "D304-1_NoPassword";
//const char* password = "NoPassword";

char* host = "smarthome.j.layershift.co.uk";  //thay domain vao
const int espport=8080;
  
WebSocketClient webSocketClient;
unsigned long previousMillis = 0;
unsigned long currentMillis;
unsigned long interval=300; //interval for sending data to the websocket server in ms

// Use WiFiClient class to create TCP connections
WiFiClient client;


void setup() {
  Serial.begin(9600);
//    pinMode(readPin, INPUT);     // Initialize the LED_BUILTIN pin as an output

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
  if (client.connected()) {
currentMillis=millis(); 
    webSocketClient.getData(data);    
//    Serial.println("Dang cho doi data ve.. ");
    if (data.length() > 0) {
      Serial.println("Gui data 1");
      Serial.println(data);
      data="";
//    webSocketClient.sendData(data);send sensor data to websocket server
      Serial.println("Sending temp");
        if (!flag) {
        DynamicJsonDocument jsonTemp(1024);
//        jsonTemp["id"] = 1;
        jsonTemp["ten"] = "chedo";
//        jsonTemp["giatri"] = 21;
//        jsonTemp["thoigiandoc"] = 0;
//        jsonTemp["trangthai"]   = false;
        jsonTemp["chedo"]   = false;
        jsonTemp["thoigianmo"] = thoigianmo;
        jsonTemp["thoigiantat"] = thoigiantat;
    
        serializeJson(jsonTemp, Serial);
        serializeJson(jsonTemp, json);
    //        Send data to Server
        webSocketClient.sendData(json);
        json = "";
        flag = true;
        Serial.println("Sent data");
      }   

  }

  delay(5);
  }
  else{
    wsconnect();
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
      Serial.println("Gui data 2");
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
