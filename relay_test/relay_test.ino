
// Test code for electromagnet relay activation
#define RELAY_PIN 7

void relay_activate()
{
  digitalWrite(RELAY_PIN, HIGH);
}

void relay_deactivate()
{
  digitalWrite(RELAY_PIN, LOW);
}

void setup() {

  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  relay_activate();   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  relay_deactivate();    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
