#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Welcome Arduino~");

  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  float tmp = dht.readTemperature();

  if (isnan(tmp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Temperature: "));
  Serial.println(tmp);
}
