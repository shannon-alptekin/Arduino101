int motorspeed;
String rotation;
int in1 = 6;
int in2 = 7;
int enable = 9;

void setup() {
  // put your setup code here, to run once:
pinMode(enable, OUTPUT);
pinMode(in1, OUTPUT); 
pinMode(in2, OUTPUT);
pinMode(A1, INPUT);
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly
  int yAxis = analogRead(A1);
if(yAxis > 550) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  motorspeed = map(yAxis, 550, 1023, 0, 255);
  rotation = "COUNTERCLOCKWISE!";
  delay(20);
 }

else if (yAxis < 470) {
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  motorspeed = map(yAxis, 0, 470, 255, 0);
  rotation = "CLOCKWISE!";
  delay(20);
}

else {
  motorspeed = 0;
  rotation = "NO ROTATION!";
}

analogWrite(enable, motorspeed);
Serial.print("Direction and speed: ");
Serial.print(rotation);
Serial.print(" ");
Serial.print(motorspeed);
Serial.print(" ");
Serial.println(yAxis);
delay(10);
}
