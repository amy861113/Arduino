#include <Ethernet.h>
#include "sqlard.h"


byte mac[] = { 0x44, 0x8A, 0x5B, 0xD5, 0xBA, 0x6B };



static byte Static_IPAddr[] = { 120, 110, 114, 40 };            
static byte Gateway_IPAddr[] = { 120, 110, 114, 254 };
static byte Subnet_Mask[] = { 255, 255, 255, 0 };
static byte server_IP[] = { 120, 110, 114, 14}
EthernetClient client;

SQLard MSSQL(server_IP, 1433, &client);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while (!Serial); 
  Ethernet.begin(Ethernet_MacAddr, Static_IPAddr, Gateway_IPAddr, Gateway_IPAddr, Subnet_Mask);
  if(MSSQL.connect())
  {
      MSSQL.setCredentials(L"fire", L"hanshin",L"Hanshin519",L"hanshin");
      MSSQL.login();
      Serial.println("Success!");  
  }else{
    Serial.println("failed!");  
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
