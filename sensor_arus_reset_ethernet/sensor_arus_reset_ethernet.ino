//======= library ==========
#include "EmonLib.h"
#include <SPI.h>
#include <Ethernet.h>

// //======= sensor =======
const int sensor = 1;  //A1

//======= Inisialisasi =======
EnergyMonitor emon1;
const int threshold = 100;
static unsigned long OnDelay;
unsigned long TimeOn = 20000;  // 30 Seconds

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
EthernetServer server (80); // port HTTP
IPAddress ip (192, 168, 1, 177); // IP untuk melihat di lokal

void setup() {
  Serial.begin(9600);
  delay(100);
  emon1.current(sensor, 600.600);

  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  OnDelay = 0 - TimeOn;
}

void loop() {
  // put your main code here, to run repeatedly:

}
