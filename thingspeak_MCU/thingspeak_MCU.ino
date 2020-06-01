#include "ThingSpeak.h"
#include <WiFi.h>

char ssid[] = "ghq000";   // your network SSID (name) 
char pass[] = "qazwsx123.";   // your network password



unsigned long myChannelNumber = 888646;
const char * myWriteAPIKey = "4B26EX5VY01P2Q8B";

IPAddress local_ip(192,168,1,5);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WiFiClient  client;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Welcome Arduino~");

 if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    WiFi.config(local_ip, gateway, subnet);
    Serial.println("\nConnected.");
  }
  
   
 
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  ThingSpeak.setField(1, 0);
  ThingSpeak.setField(2, 0);
  ThingSpeak.setField(3, 0);
  ThingSpeak.setField(4, 0);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  delay(20000); // Wait 20 seconds to update the channel again
}
