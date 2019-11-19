int const led = 16;
void setup() {
  pinMode(led, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  digitalWrite(led, LOW);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(led, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(led, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
}
