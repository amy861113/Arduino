#include <TimedAction.h> //同時執行多種任務函式庫
#include "ThingSpeak.h" //連接網站thingSpeak
#include <Ethernet.h>
#include <DHT.h> //溫度濕度sensor


#define DHTPIN 2 
#define DHTTYPE DHT11
#define SENSOR 66 //30A sensor值為66mA

const int relay = 3; //繼電器
const byte GAS = A0;  //MQ7
const int AOUT  = A1; //電流測試sensor

double V = 0; //抓到的類比值
double VRMS = 0;  
double Irms = 0;  //電流大小



unsigned long myChannelNumber = 888646; //thingSpeak的channel_id
const char * myWriteAPIKey = "4B26EX5VY01P2Q8B";  //thingSpeak的channel_APIKey
DHT dht(DHTPIN, DHTTYPE);


byte mac[] = { 0x44, 0x8A, 0x5B, 0xD5, 0xBA, 0x6B };
IPAddress ip(120, 110, 114, 40);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(120, 110, 114, 254);
IPAddress dnServer(8, 8, 8, 8);
EthernetServer server(80); 


EthernetClient client, client1;



//架設網站利用request來開關繼電器
void relayThd()
{
  
  client = server.available();
  
  if(!client)
    return;
 

  while(!client.available())
    delay(1);

  Serial.println("new Client~");
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  int val;
  if(req.indexOf("/hanshin/open") != -1)
    val = 0; 
  else if(req.indexOf("/hanshin/close") != -1)
    val = 1;
  else{
    Serial.println("invalid request");
    client.stop();
    return;
  }

  digitalWrite(relay, val);
  client.flush();

   
   client.println("HTTP/1.1 200 OK");
   client.println("Content-Type: text/html");
   client.println();

   client.println("<h1>OK~</h1>");

    
   delay(1000);
   client.stop();
  
 
  
}

//將需要的資料寫入thingSpeak
void dataWrite()
{
  delay(1000);
  float tmp = dht.readTemperature();
  int gas = analogRead(GAS);
  float hum = dht.readHumidity();
  float aout = aOutput();
  if (isnan(tmp) || isnan(hum)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  ThingSpeak.setField(1, tmp);
  ThingSpeak.setField(2, gas);
  ThingSpeak.setField(3, hum);
  ThingSpeak.setField(4, aout);
  
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
  Serial.print("Irms= ");
  Serial.print(Irms);
  Serial.println(" A ");
  
 
}

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
float aOutput(){
  
   V = getVPP();
   VRMS = (V/2.0) *0.707; 
   Irms = ((VRMS * 1000.000)/SENSOR-0.074);
  

   return Irms;
}

//排程
TimedAction thd1 = TimedAction(1000, relayThd); //每秒啟動
TimedAction thd2 = TimedAction(20000, dataWrite); //每20秒啟動





void setup() {
  
  Serial.begin(9600);
  Serial.println("Welcome Arduino~");

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);

  
  
  dht.begin();
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);
  server.begin();
  delay(1000);
  
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  
  
  ThingSpeak.begin(client1);
  
  
}



void loop() {

  /*排程啟動循環*/
  thd1.check();
  thd2.check();
   
}
