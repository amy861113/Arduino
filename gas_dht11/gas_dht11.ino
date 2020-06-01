#include "ThingSpeak.h"
#include <Ethernet.h>



#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT11
const byte GAS = A0;

unsigned long myChannelNumber = 888646;
const char * myWriteAPIKey = "4B26EX5VY01P2Q8B";
DHT  dht(DHTPIN, DHTTYPE);

static byte mac[] =  {0x90, 0xA2, 0xDA, 0x10, 0x40, 0x4F};
IPAddress ip(120, 110, 114, 40);
IPAddress dnServer(8, 8, 8, 8);
IPAddress gateway(120, 110, 114, 254);
IPAddress subnet(255, 255, 255, 0);

EthernetClient client;
void setup() {
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  
  
  Serial.begin(9600);
  Serial.println("Welcome Arduino~");
  
  dht.begin();
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);
  delay(1000);
  
  ThingSpeak.begin(client);
}

void loop() {
 
  delay(1000);
  float tmp = dht.readTemperature();         
  int gas = analogRead(GAS);
  float hum = dht.readHumidity();

  if (isnan(tmp) || isnan(hum)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  ThingSpeak.setField(1, tmp);
  ThingSpeak.setField(2, gas);
  ThingSpeak.setField(3, hum);
  ThingSpeak.setField(4, 0);
  
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }


  
  Serial.print(F("Temperature: "));
  Serial.println(tmp);
  Serial.print(F("gasValue: "));
  Serial.println(gas);
  Serial.print(F("Humidity: "));
  Serial.println(hum);
  delay(20000);
}
