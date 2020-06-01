const byte GAS = A3;
const byte TMP = A5;
int gasValue = 0, tmpValue = 0;


void setup()
{
  Serial.begin(9600);
  Serial.println("Welcome to Arduino!");
  
}

void loop()
{
  gasValue = analogRead(GAS);
  tmpValue = analogRead(TMP);

  float temp = (tmpValue * (5.0/1024) -0.5)/0.01;
  Serial.print("[");
  Serial.print(temp);
  Serial.print(", ");
  Serial.print(gasValue, DEC);
  Serial.println("]");
  delay(1000);
}
