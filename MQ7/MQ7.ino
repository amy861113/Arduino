const int MQ7 = 34;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Welcome Arduino~");
}

void loop() {
  // put your main code here, to run repeatedly:
  int gas = analogRead(MQ7);
  Serial.println(gas);
  if(gas > 262)
    Serial.println("warning");
  else
    Serial.println("safe");
  delay(1000);
}
