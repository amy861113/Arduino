#define SENSOR 66
const int AOUT  = A1;

double V = 0;
double VRMS = 0;
double Irms = 0;


float getVPP()
{
  float result;
  int readValue; //從sensor讀值
  int maxValue = 0; // 儲存最大值
  int minValue = 1024; // 儲存最小值
  uint32_t start_time = millis();
  
  while((millis()-start_time) < 1000) //1秒讀取樣品一次
   {
       readValue = analogRead(AOUT);
       // 讀取是否有新的數值
       if (readValue > maxValue) 
       { /*紀錄最大值*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       { /*紀錄最小值*/
           minValue = readValue;
       }
   }
   // 最大值減最小值
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result; 
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   
   digitalWrite(3, HIGH);
   V = getVPP();
   VRMS = (V/2.0) *0.707; 
   Irms = ((VRMS * 1000.000)/SENSOR-0.074);
   Serial.print("Irms= ");
   Serial.print(Irms);
   Serial.println(" A ");
   digitalWrite(3, LOW);
   V = getVPP();
   VRMS = (V/2.0) *0.707; 
   Irms = ((VRMS * 1000.000)/SENSOR-0.074);
   Serial.print("Irms= ");
   Serial.print(Irms);
   Serial.println(" A ");
   
   
   

}
