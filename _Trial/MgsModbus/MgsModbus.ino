#include <SPI.h>
#include <Ethernet.h>
#include "MgsModbus.h"

MgsModbus Mb;

byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x94, 0xB5};
IPAddress ip(192, 168, 1, 177);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  delay(100);
  Ethernet.begin(mac, ip, subnet);

  // isi nilai awal register 40001 - 40012
  Mb.MbData[0] = 678;   //register 40001
  Mb.MbData[1] = 11;    //register 40002
  Mb.MbData[2] = 22;    //register 40003
  Mb.MbData[3] = 33;    //register 40004
  Mb.MbData[4] = 44;    //dan seterusnya...

}

void loop() {
  Mb.MbData[5] = analogRead(A0);
  delay(50);
  Mb.MbsRun();
}
