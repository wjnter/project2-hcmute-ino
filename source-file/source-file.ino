#include <ESP8266WiFi.h>
#include <WebSocketClient.h>

boolean handshakeFailed=0;
String data= "";

char path[] = "/realtime-data";   //identifier of this device

const char* ssid     = "80 dqh lau 2.2";
const char* password = "80duongquangham";
//const char* ssid     = "Phong1.6";
//const char* password = "sonyeuthaokhonghoitiec";
char* host = "doan2.enscaled.sg";  //thay domain vao
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
    if (data.length() > 0) {
      Serial.println(data);
      data="";
//    webSocketClient.sendData(data);send sensor data to websocket server


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
