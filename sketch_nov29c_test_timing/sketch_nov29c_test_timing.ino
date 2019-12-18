int onHour = 20;
int onMinute = 20;
//Open:     20:20
//Close:    23:23
int offHour = 23;
int offMinute = 23;
//Now:      23:24
int nowHour = 23;
int nowMinute = 23;

void setup() {
  Serial.begin(9600);

  Serial.println("Setting up.." );
  if ((nowHour > onHour) && (nowHour < offHour)) {
    Serial.println("Opening bulb 1");
  } else 
  if ((nowHour == onHour) || (nowHour == offHour)) {
    if (nowMinute >= onMinute) {
      if (nowMinute < offMinute) {
        Serial.println("Opening bulb 2");
      }
    }
  } else {
    Serial.print("Nothing onHour");
  }

  if ((nowHour < onHour) || (nowHour > offHour)) {
    Serial.println("Turning off bulb 1");
  } else 
  if ((nowHour == onHour) || (nowHour == offHour)) {
    if ((nowMinute < onMinute) || (nowMinute >= offMinute)) {
      Serial.println("Turning off bulb 2");
    }
  } else {
    Serial.println("Nothing offHour");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
