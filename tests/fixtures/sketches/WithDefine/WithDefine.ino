// Sketch that uses a preprocessor define - tests build-properties input
#ifndef MY_DEFINE
#define MY_DEFINE 0
#endif

void setup() {
  Serial.begin(9600);
#if MY_DEFINE
  Serial.println("MY_DEFINE is set");
#else
  Serial.println("MY_DEFINE not set");
#endif
}

void loop() {
  // nothing
}
