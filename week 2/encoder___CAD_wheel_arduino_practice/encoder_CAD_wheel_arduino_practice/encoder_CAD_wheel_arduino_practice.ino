#include <Encoder.h>

Encoder enc(2,3);
int enable = 9;
int in1 = 6;
int in2 = 7;
double deg;
double tic = 1;
int motorspeed;
double kP =9;
double kI = .1;
double tao;
int newS;
double error; 
int maxSpeed = 120;
long now;
long lastTime = 0;
long timeCheck = 0;
double updatedErr;
double sumError = 0;
double lastErr = 0;
bool doneRotatingVar;
int threshold = 7;

//kP, kI, and threshold #'s that work well tg:
//2,7,0
//9,7,0.1

void setup() {
  // put your setup code here, to run once:
  pinMode(enable, OUTPUT);
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  Serial.begin(9600);
  Serial.println("Please enter the number of degrees you'd like the wheel to rotate.");
}

void loop() {
    //calls on function isDoneRotating() to set variable
   if(isDoneRotating()) {
      doneRotatingVar = true;
    }
   else doneRotatingVar = false;
   
    //calls on functions rotateOnCommand() and pid()
   rotateOnCommand();
   if (!doneRotatingVar) {
      pid();
     }
     //closing lines of code
  if(doneRotatingVar){ 
    Serial.println("All done!");
    Serial.print("Ticks rotated: ");  
    Serial.println(enc.read());
    doneRotatingVar = false;
  }
}

void rotateOnCommand(){
 if(Serial.available() > 0) {
    deg = Serial.parseInt();
    Serial.read();
    tic = deg/360.0 *48;
    Serial.print("New Goal: ");
    Serial.println(tic);
  }

 //if(enc.read() >= tic) {
 //    doneRotatingVar = true;
 //   }  
}



//function accepts values bw -100 and 100
//function changes motor's velocity
void changeVelocity(int speed) {
  
  //num bw 0 and 100
if(speed>=0) {
  //direction
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  motorspeed = map(speed, 0, 100, 0, maxSpeed);
}

//num bw -100 and 0
else {
  //direction
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  motorspeed = map(speed,-100, 0, maxSpeed, 0);
}
analogWrite(enable, motorspeed);

}

//function conducts proportional control based on our progress towards target
void propControl() {
  //if error>0, we're still approaching target
  //if error<0, we've passed the target
  error = tic-enc.read();
  if(!(error<7 && error>-7)){
    newS = kP*(error);
    changeVelocity(newS);
  }
}

void pid() {
  updatedErr = tic - enc.read();
  sumError += updatedErr*(millis()-lastTime);
  tao = kP*updatedErr + kI*sumError;
  changeVelocity(tao);

  if(abs(lastErr) > threshold && abs(updatedErr) < threshold) {
    timeCheck = millis();
  }
  
  lastTime = millis();
  lastErr = updatedErr;
}

bool isDoneRotating() {
  now = millis();
  (abs(lastErr)< threshold && (now-timeCheck) > 1000);
}
