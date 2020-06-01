#include <WiFi.h>                  // Use this for WiFi instead of Ethernet.h
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include "ACS712.h"
#include "DHTesp.h"
#include "Ticker.h"
#include <SPI.h>
#include <TimedAction.h> //同時執行多種任務函式庫


//dht11設定board
#ifndef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP32 ONLY!)
#error Select ESP32 board.
#endif



byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server_addr(120, 110, 114, 39);  
char user[] = "lab519";              // MySQL user login username
char password[] = "lab519";        // MySQL user login password
const char* ssid = "ghq000";  // Enter SSID here
const char* pass = "qazwsx123.";  //Enter Password here

IPAddress local_ip(192, 168, 1, 105);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

char INSERT_DATA[] = "INSERT INTO Lab519.env (temperature, humidity, co_value,  electric_current) VALUES (%f, %f, %f, %f)";
char query[128];

const int relay = 27;
const int MQ7 = 34;

WiFiClient client;
DHTesp dht;

//ACS712設定port與機型
ACS712 sensor(ACS712_30A, 35);          
MySQL_Connection conn((Client *)&client);
WiFiServer server(80);

void saveToMysql(){
  
  TempAndHumidity TmpAndHum = dht.getTempAndHumidity();
  float humidity = TmpAndHum.humidity;
  int gas = analogRead(MQ7);
  float temperature = TmpAndHum.temperature;
  float I = sensor.getCurrentDC();

  if(isnan(humidity) || isnan(temperature)) {
    return;
  }
  
  Serial.println("Recording data.");

  // Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Execute the query

  sprintf(query, INSERT_DATA, temperature, humidity, gas, I);
  cur_mem->execute(query);
  // Note: since there are no results, we do not need to read any data
  // Deleting the cursor also frees up memory used
  delete cur_mem;
  Serial.println("Data recorded.");
  
  Serial.print(humidity);
  Serial.print("\t\t");
  Serial.print(temperature);
  Serial.print("\t\t");
  Serial.print(gas);
  Serial.print("\t\t");
  Serial.println(I);

  
}

void relayOnWeb(){
  WiFiClient client1 = server.available();

  if(!client1)
    return;
 

  while(!client1.available())
    delay(1);

  String req = client1.readStringUntil('\r');
  Serial.println(req);
  //client1.flush();

  int val;
  if(req.indexOf("/hanshin/open") != -1)
    val = 1; 
  else if(req.indexOf("/hanshin/close") != -1)
    val = 0;
  else{
    Serial.println("invalid request");
    client1.stop();
    return;
  }


   if(val == 0 || val == 1){
    client1.println("HTTP/1.1 200 OK");
    client1.println("Content-Type: text/html");
    client1.println();

    client1.println("<h1>OK~</h1>");
   }
  

   digitalWrite(relay, val);
   client1.flush();

   
   

    
   delay(1000);
   client1.stop();
     
}

TimedAction thd1 = TimedAction(1000, relayOnWeb); //每秒啟動
TimedAction thd2 = TimedAction(1000, saveToMysql); 




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Welcome Arduino~");

   
   WiFi.begin(ssid, pass);
   delay(5000);
  // print out info about the connection:
  
   WiFi.config(local_ip, gateway, subnet);
   Serial.println("Connected to network");
   IPAddress ip = WiFi.localIP();
   Serial.print("My IP address is: ");
   Serial.println(ip);
  
  // End WiFi section
   
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
  }
  else{
    Serial.println("Connection failed.");
  }


  // This method calibrates zero point of sensor,
  // It is not necessary, but may positively affect the accuracy
  // Ensure that no current flows through the sensor at this moment
  sensor.calibrate();

  //dht11設定
  dht.setup(15, DHTesp::DHT11);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);

  server.begin();
  
}

void loop() {
  
  thd1.check();
  thd2.check();
}
