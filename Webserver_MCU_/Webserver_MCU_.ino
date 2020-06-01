#include <WiFi.h>
#include <SPI.h>

const char* ssid = "ghq000";  // Enter SSID here
const char* pass = "qazwsx123.";  //Enter Password here

int status = WL_IDLE_STATUS;

IPAddress local_ip(192,168,1,5);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WiFiServer server(80);

void setup(){
   Serial.begin(115200);

   WiFi.begin(ssid, pass);
   delay(10000);
   
   WiFi.config(local_ip, gateway, subnet);

   Serial.print("Got IP: ");  
   Serial.println(WiFi.localIP());
   server.begin();
}

void loop(){
  WiFiClient client = server.available();
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
