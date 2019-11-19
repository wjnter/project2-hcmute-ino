int const button = d4;
int led = 14;
void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT);  //Cài đặt chân D11 ở trạng thái đọc dữ liệu
  pinMode(led,OUTPUT); // Cài đặt chân D2 dưới dạng OUTPUT
}

void loop() {
  int buttonStatus = digitalRead(button);    //Đọc trạng thái button
  if (buttonStatus == HIGH) { // Nếu mà button bị nhấn
    digitalWrite(led,HIGH); // Đèn led sáng
    Serial.println("Nhan");
  } else { // ngược lại
    digitalWrite(led,LOW);
    Serial.println("Tha");
  }
}
