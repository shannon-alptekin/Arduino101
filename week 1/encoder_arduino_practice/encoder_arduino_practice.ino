#include <Encoder.h>

Encoder enc(2,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ticks = enc.read();
  Serial.print("Ticks: ");
  Serial.print(ticks);
  Serial.print(" | Degrees: ");
  Serial.println(ticks/48.0*360);
  delay(100);
}
