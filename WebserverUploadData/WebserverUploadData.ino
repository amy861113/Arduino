#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0x44, 0x8A, 0x5B, 0xD5, 0xBA, 0x6B };

IPAddress ip(120, 110, 114, 40);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(120, 110, 114, 254);
EthernetServer server(80); 

const byte GAS = A3;
const byte TMP = A5;
int gasValue = 0, tmpValue = 0;

void setData(){
  gasValue = analogRead(GAS);
  tmpValue = analogRead(TMP);

  float temp = (tmpValue * (5.0/1024) -0.5)/0.01;
  Serial.print("[");
  Serial.print(temp);
  Serial.print(", ");
  Serial.print(gasValue, DEC);
  Serial.println("]");
  delay(1000);  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  
  Serial.println("Welcome to Arduino!");
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  
  IPAddress ip = Ethernet.localIP();
  Serial.print("My IP address : ");
  Serial.println(ip);
}

float getTmp(){
    tmpValue = analogRead(TMP);
    float temp = (tmpValue * (5.0/1024) -0.5)/0.01;
    return temp;
}

int getGas(){
    gasValue = analogRead(GAS);
    return gasValue;
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


        client.println("<head>");
        client.println("<meta http-equiv=\"refresh\" content = \"3\" ");
        client.println("</head>");
        client.print("<p>tmp:");
        client.print(getTmp());
        client.println("</p>");

        client.print("<p>gas:");
        client.print(getGas());
        client.println("</p>");
        
       

        break;
      }
    }  

    delay(1);
    client.stop();
  }
}
