#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0x44, 0x8A, 0x5B, 0xD5, 0xBA, 0x6B };

IPAddress ip(120, 110, 114, 40);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(120, 110, 114, 254);
EthernetServer server(80); 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  
  IPAddress ip = Ethernet.localIP();
  Serial.print("My IP address : ");
  Serial.println(ip);
}

void loop() {
  // put your main code here, to run repeatedly:
  EthernetClient client = server.available();

  if(client){
    while(client.connected()){
      if(client.available()){
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println();

        client.println("<h1>Arduino 物聯網運用</h1>");

        break;
      }
    }  

    delay(1);
    client.stop();
  }
}
