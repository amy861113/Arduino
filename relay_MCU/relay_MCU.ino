#include <WiFi.h>
#include <SPI.h>

const char* ssid = "ghq000";  // Enter SSID here
const char* pass = "qazwsx123.";  //Enter Password here
const int relay = 27;

int status = WL_IDLE_STATUS;

IPAddress local_ip(192,168,1,5);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   Serial.println("Welcome Arduino~");

   pinMode(relay, OUTPUT);
   digitalWrite(relay, LOW);
  
   WiFi.begin(ssid, pass);
   delay(10000);
   
   WiFi.config(local_ip, gateway, subnet);

   Serial.print("Got IP: ");  
   Serial.println(WiFi.localIP());
   server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client1 = server.available();

  if(!client1)
    return;
 

  while(!client1.available())
    delay(1);

  String req = client1.readStringUntil('\r');
  Serial.println(req);
  client1.flush();

  int val;
  if(req.indexOf("/hanshin/open") != -1)
    val = 0; 
  else if(req.indexOf("/hanshin/close") != -1)
    val = 1;
  else{
    Serial.println("invalid request");
    client1.stop();
    return;
  }

   digitalWrite(relay, val);
   client1.flush();

   
   client1.println("HTTP/1.1 200 OK");
   client1.println("Content-Type: text/html");
   client1.println();

   client1.println("<h1>OK~</h1>");

    
   delay(1000);
   client1.stop();
   
}
