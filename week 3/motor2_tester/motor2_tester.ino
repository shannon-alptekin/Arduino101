//potentiometer regulates motor function
//now test pid

#include <Encoder.h>

Encoder enc(2,3);
int enable = 9;
int in1 = 6;
int in2 = 7;
int maxSpeed = 255;
int counter = 1;

int pValue;
int desiredMotorV; //target velocity
int one = 1;
bool clockwise;
double currentV = 0;
double currentDist;
double currentTime;
double lastV = 0;
double lastDist = 0;
double lastTime = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(enable, OUTPUT);
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  potentiometerRead();
  changeVelocity(desiredMotorV);
  distToVelocity();
 // Serial.println(enc.read()* -1);
    Serial.println("Velocity_____________________ ");
    Serial.print("Ticks/millisecond: ");
    Serial.print(currentV);
    Serial.print(" | Degrees/second: ");
    Serial.println(velocityConverter());
    Serial.print(" | Revs/second: ");
    Serial.println(findRevsPerSec());
}

void potentiometerRead() {
  pValue = analogRead(A0);
  if(pValue >= 511) {
    desiredMotorV = map(pValue, 511, 1023, 0, maxSpeed); //potentiometer moves far to the right clockwise direction
    clockwise = true; 
  }
  else {
    desiredMotorV = map(pValue, 510, 0, 0, maxSpeed); //counter-clockwise direction
    clockwise = false;
  }
}

void changeVelocity(int speed) {
  analogWrite(enable, speed);
  if(clockwise) {   
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW); //clockwise
  }
  else {
    digitalWrite(in2, HIGH);
    digitalWrite(in1, LOW); //counter-clockwise
  }
}

void distToVelocity() {
  currentDist = enc.read();
  currentTime = millis();
  lastV = currentV;
  currentV = (currentDist - lastDist)/(currentTime - lastTime);
  lastDist = currentDist;
  lastTime = currentTime;
  //return currentV; //final line of code in function - don't return anymore
}

//Converts velocity(ticks/millisecond) to velocity(degrees/second)
double velocityConverter() {
  return currentV *1000*(360.0/26500);
}

//Converts velocity(ticks/millisecond) to velocity(revolutions/second)
double findRevsPerSec() {
 return currentV*1000./26500;
}
