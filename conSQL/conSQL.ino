#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

byte mac[] = { 0x44, 0x8A, 0x5B, 0xD5, 0xBA, 0x6B };

IPAddress server_addr(120, 110, 114, 14);  // IP of the MySQL *server* here
char user[] = "hanshin";              // MySQL user login username
char password[] = "Hanshin519";        // MySQL user login password


char update_data[] = "update fire.Environmental_data set tmpValue = 1, gasValue = 1 where data_id = 1";

EthernetClient client;
MySQL_Connection conn((Client *)&client);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial); // wait for serial port to connect
  Ethernet.begin(mac);
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    Serial.println("Connection Success.");
    delay(1000); 
  }else{
    Serial.println("Connection failed.");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
