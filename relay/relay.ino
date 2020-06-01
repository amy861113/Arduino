int RELAYpin = 3;

void setup() {
  pinMode(RELAYpin, OUTPUT);  
  digitalWrite(RELAYpin, LOW);
}

void loop() {
  digitalWrite(RELAYpin, HIGH);
  delay(10000);
  digitalWrite(RELAYpin, LOW);
  delay(10000);
}
