#include <SD.h>
#include <SPI.h>


void(* resetFunc) (void) = 0;
const byte GAS = A4;
const byte TMP = A5;
int gasValue = 0, tmpValue = 0;
File file;

void setup()
{
  Serial.begin(9600);
  Serial.println("Welcome to Arduino!");
  
  
  Serial.println("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  if(!SD.exists("fire.txt")){
    Serial.println("Creating fire.txt...");
    file = SD.open("fire.txt", FILE_WRITE);
  }else{
    SD.remove("fire.txt");
    Serial.println("Creating fire.txt...");
    file = SD.open("fire.txt", FILE_WRITE);
  }
  
  
   
}

void loop()
{
 
  if(file){

    int i;
    for(i = 0; i < 100; i++){
      gasValue = analogRead(GAS);
      tmpValue = analogRead(TMP);
      float temp = (tmpValue * (5.0/1024) -0.5)/0.01;
      file.print("[");
      file.print(temp);
      file.print(", ");
      file.print(gasValue);
      file.println("]");
      
      
      Serial.print("[");
      Serial.print(temp);
      Serial.print(", ");
      Serial.print(gasValue, DEC);
      Serial.println("]");
      delay(1000);
    }
    file.println("}");
    file.close();
    
    Serial.println("done.");
  }

  delay(60000);
  resetFunc();
  /*
  float temp = (tmpValue * (5.0/1024) -0.5)/0.01;
  Serial.print("[");
  Serial.print(temp);
  Serial.print(", ");
  Serial.print(gasValue, DEC);
  Serial.println("]");
  delay(1000);
  */
}
