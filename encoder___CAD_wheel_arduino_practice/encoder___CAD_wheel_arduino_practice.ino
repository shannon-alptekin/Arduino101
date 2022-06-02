#include <Encoder.h>

Encoder enc(2,3);
int enable = 9;
int in1 = 6;
int in2 = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(enable, OUTPUT);
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  Serial.begin(9600);
}

int deg;
int tic;

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Please enter the number of degrees you'd like the wheel to rotate.");
  if(Serial.available() > 0) {
    deg = Serial.parseInt();
    tic = deg/360 *48;
    analogWrite(enable,255);
  if(enc.red()==tic) {
    analogWrite(enable, 0);
    Serial.println("Yay! Your wheel is done rotating.");
  }  
  }
    
}
