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

void loop() {
  // put your main code here, to run repeatedly:

  int potValue = analogRead(A0);
  int pwmValue = map(potValue, 0, 1023, 0, 255);
  analogWrite(enable, pwmValue);
  Serial.print("the value is: ");
  Serial.println(pwmValue);
  delay(2000);

}
