int echoPin = 2;
int trigPin = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); //Trig >> D3
  pinMode(echoPin, INPUT); //Echo >> D2
  Serial.begin(9600); //initializing serial communication
  Serial.println("Ultrasonic Sensor Test:");
}

double distance;
long time;

void loop() {
  // put your main code here, to run repeatedly:
//clears conditions
digitalWrite(trigPin, LOW);
delayMicroseconds(2);


//Trig active
digitalWrite(trigPin,HIGH);
delayMicroseconds(10);
digitalWrite(trigPin,LOW);

double initialTime;

while(digitalRead(echoPin) == 0) {
initialTime = micros();
}

//

while(digitalRead(echoPin) == 1) {
time = micros() - initialTime;
}

//

distance = time*.034/2;
Serial.println(distance);
delay(100);
}
