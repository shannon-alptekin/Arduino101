
int SEL = 2;
int echoPin = 6;
int trigPin = 7;
  
  void setup() 
  {
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 
    pinMode(SEL, INPUT_PULLUP);
    Serial.begin(9600);
  }

double distance;
long time;

  void loop() 
  {
    int s = digitalRead(SEL);
     if(s==0) {

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

    while(digitalRead(echoPin) == 1) {
    time = micros() - initialTime;
    }


    distance = time*.034/2;
    Serial.print("Ultrasonic Sensor Test: ");
    Serial.println(distance);
    delay(100);
      
    }
  delay(100);
  }
 
