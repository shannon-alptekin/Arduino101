//Materials: encoder, potentiometer, arduino, breadboard, motor, Hbridge, power source
//Remember A0 is the analog that your potentiometer is on
//Motor: 106,000 ticks/rev = 2000*53

#include <Encoder.h>

Encoder enc(2,3);
int enable = 9;
int in1 = 6;
int in2 = 7;

int maxSpeed = 200; //will probably need to lower this at some point due to added mass (wheel)
double kP = 0.5; //cannot exceed a certain value, otherwise we encounter issues
double kI = 0;
double tao;
long error;
long sumError;
long lastError = 0;
long PIDtimecount = 0;
long now;

double currentV = 0;
double currentDist;
double currentTime;
double threshold = 8; //this value will need to be changed; idk what it should be right now (pretty sure it has to be small though)
double lastV = 0;
double lastDist = 0;
double lastTime = 0;
double lastTime2 = 0;
int pValue;
int desiredMotorV; //target velocity
bool clockwise;
bool targetAchieved = false;



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
  writeMotor(desiredMotorV); //initially starts motor
  distToVelocity();
  PIDvelocity();
  Serial.println(enc.read());
    Serial.println("Velocity_____________________ ");
    Serial.print("Ticks/ms: ");
    Serial.print(currentV);
    Serial.print(" | Degrees/sec: ");
    Serial.println(velocityConverter());
    Serial.print(" | Revs/sec: ");
    Serial.println(findRevsPerSec());
}

//function that reads the potentiometer and stores the equivalent value (in terms of motor velocity) in the variable "desiredMotorV"
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

//function accepts values bw 0 and 255
//function changes motor's velocity
void writeMotor(int speed) {
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

//distance measured in ticks
//velocity measured in ticks/millisecond
//Function that returns velocity using information from our encoder
double distToVelocity() {
  currentDist = enc.read();
  currentTime = millis();
  lastV = currentV;
  currentV = (currentDist - lastDist)/(currentTime - lastTime);
  lastDist = currentDist;
  lastTime = currentTime;
  return currentV; //final line of code in function
}

//PID velocity control function
void PIDvelocity() {
  error = desiredMotorV - currentV;
  sumError += error*(millis()-lastTime2);
  tao = kP*error + kI*sumError;
  if(tao<0) {
    tao = tao * -1;
  }
    writeMotor(tao);
  //Serial.println(tao);
  if(abs(lastError) > threshold && abs(error) < threshold) {
    PIDtimecount = millis();
  }
  lastTime2 = millis();
  lastError = error;
}

//void isDoneRotating() {
//  now = millis();
//  if (abs(lastError) < threshold && (now - PIDtimecount) > 750) {
//    targetAchieved = true; 
//  } 
//}

//Converts velocity(ticks/millisecond) to velocity(degrees/second)
double velocityConverter() {
  return currentV *1000*(360.0/106000);
}

//Converts velocity(ticks/millisecond) to velocity(revolutions/second)
double findRevsPerSec() {
 return currentV*1000./106000;
}
