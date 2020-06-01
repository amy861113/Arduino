#include "ACS712.h"

ACS712 sensor(ACS712_30A, 35);

void setup() {
  Serial.begin(115200);

  // This method calibrates zero point of sensor,
  // It is not necessary, but may positively affect the accuracy
  // Ensure that no current flows through the sensor at this moment
  sensor.calibrate();
  pinMode(27, OUTPUT);
}

void loop() {
  // Get current from sensor
  digitalWrite(27, 1);
  float I = sensor.getCurrentDC();
  
  // Send it to serial
  Serial.println(String("I = ") + I + " A");
  
  // Wait one second before the new cycle
  delay(1000);
}
