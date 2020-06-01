#include <Ethernet.h>
#include <SPI.h>
#include <WebServer.h>

byte mac[] = { 0x44, 0x8A, 0x5B, 0xD5, 0xBA, 0x6B };

IPAddress ip(120, 110, 114, 40);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(120, 110, 114, 254);
WebServer webserver("", 80); 


P(homePage) = "<!DOCTYPE html>"
               "<html lang=\"en\">"
               "<head><meta charset=\"UTF-8\">"
               "<title>Arduino 微網站</title></head>"
               "<body>這是微網站的首頁。</body>"
               "</html>";
P(faqPage) = "<!DOCTYPE html>"
             "<html lang=\"en\"><head>"
             "<meta charset=\"UTF-8\">"
             "<title>微網站FAQ</title>"
             "</head>"
             "<body>這是FAQ網頁。</body>"
             "</html>";
void defaultCmd(WebServer &server, WebServer::ConnectionType type){
  server.httpSuccess();  
  if(type != WebServer::HEAD)
    server.printP(homePage);
}

void faqCmd(WebServer &server, WebServer::ConnectionType type){
  server.httpSuccess();  
  if(type != WebServer::HEAD)
    server.printP(faqPage);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  
  
  Ethernet.begin(mac, ip, gateway, subnet);
  webserver.setDefaultCommand(&defaultCmd);
  webserver.addCommand("faq.html", &faqCmd);
  webserver.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  webserver.processConnection();
}
