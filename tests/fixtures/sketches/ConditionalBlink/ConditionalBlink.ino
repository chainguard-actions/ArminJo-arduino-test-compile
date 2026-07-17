// Sketch that uses a compile-time define for testing build-properties
#ifndef BLINK_DELAY
#define BLINK_DELAY 1000
#endif

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(BLINK_DELAY);
  digitalWrite(LED_BUILTIN, LOW);
  delay(BLINK_DELAY);
}
