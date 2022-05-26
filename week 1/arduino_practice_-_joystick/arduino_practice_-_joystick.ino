int VER = 0;
int HOR = 1; 
int SEL = 2;


void setup() {
  // put your setup code here, to run once:
  pinMode(SEL, INPUT_PULLUP);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int v = analogRead(VER);
  int h = analogRead(HOR);
  int s = digitalRead(SEL);
  
  Serial.print("vertical: ");
  Serial.println(v);
  Serial.print("horizontal: ");
  Serial.println(h);
 if(s ==0) {
  Serial.println("select: PRESSED!!"); }
  else { 
    Serial.println("select: NOT PRESSED"); }
  delay(2000);
  Serial.println("________________________________");

}
