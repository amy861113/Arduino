#include <ACS712.h>
const int AOUT  = A1;

ACS712 acs(ACS712_30A, AOUT);
void setup() {
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  Serial.begin(9600);
}

void loop() {
  
  digitalWrite(3, HIGH);
  float aout = acs.getCurrentAC();
  Serial.println(aout);
  delay(1000);
  
  
}
