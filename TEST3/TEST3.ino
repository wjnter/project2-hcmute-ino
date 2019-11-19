const int outputTemp= A0;

const int btnBulb3 = D0;
const int btnBulb1 = D5;
const int btnBulb2 = D7;

const int bulb3 = D4;
const int bulb1 = D6;
const int bulb2 = D8;

int statusBulb1 = 0;
int statusBulb2 = 0;
int statusBulb3 = 0;

void controlBulb1() {
  if (!digitalRead(btnBulb1)) {
    delay(30);
    if (!digitalRead(btnBulb1)) {
      statusBulb1 = !statusBulb1;
      Serial.print("Trang thai nut nhan 1: ");
      Serial.println(statusBulb1);
      while (!digitalRead(btnBulb1));
    }
  }
  if (statusBulb1) {
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
    }
  }

  if (statusBulb2) {
    digitalWrite(bulb2, HIGH);
  } else {
    digitalWrite(bulb2, LOW);
  }
}
void setup() {

  Serial.begin(9600);
  
  pinMode(btnBulb1, INPUT); 
  pinMode(btnBulb2, INPUT); 
  pinMode(btnBulb2, INPUT); 
  
  pinMode(bulb1, OUTPUT);
  pinMode(bulb2, OUTPUT);
  pinMode(bulb3, OUTPUT);

  digitalWrite(bulb1, LOW);
  digitalWrite(bulb2, LOW);
  digitalWrite(bulb3, LOW);
}
void controlBulb3() {
  if (!digitalRead(btnBulb3)) {
    delay(30);
    if (!digitalRead(btnBulb3)) {
      statusBulb3 = !statusBulb3;
      Serial.print("Trang thai nut nhan 1: ");
      Serial.println(statusBulb3);
      while (!digitalRead(btnBulb3));
    }
  }
  if (statusBulb3) {
    digitalWrite(bulb3, HIGH);
  } else {
    digitalWrite(bulb3, LOW);
  }
}

void loop() {
 
  controlBulb1();
  controlBulb2();
  controlBulb3();

} 
