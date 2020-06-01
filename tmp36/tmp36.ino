const byte TMP = A0;


void setup()
{
  
  Serial.begin(9600);
  Serial.println("Welcome to Arduino!");
}

void loop()
{
 int val;
 val = analogRead(TMP);
 Serial.print("TMP: ");
 float temp = (val * (5.0/1024) -0.5)/0.01;
 Serial.println(temp);
 delay(1000); 

}
