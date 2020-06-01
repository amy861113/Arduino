#include <Ethernet.h>
#include <SPI.h>

const int relay = 3;




byte mac[] = { 0x44, 0x8A, 0x5B, 0xD5, 0xBA, 0x6B };

IPAddress ip(120, 110, 114, 40);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(120, 110, 114, 254);
EthernetServer server(80); 

void setup() {
  Ethernet.init(10);
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);
  
  Serial.println("Welcome Arduino~");

  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  
  IPAddress ip = Ethernet.localIP();
  Serial.print("My IP address : ");
  Serial.println(ip);
}

void loop() {
  // put your main code here, to run repeatedly:
  EthernetClient client1 = server.available();

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
