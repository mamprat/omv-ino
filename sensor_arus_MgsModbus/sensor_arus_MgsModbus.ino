//======= library =======
#include "EmonLib.h"
#include <SPI.h>
#include <Ethernet.h>
#include "MgsModbus.h"

//======= alamat =======
const int sensor = 1;  //A1
MgsModbus Mb;

//======= inisialisasi =======
EnergyMonitor emon1;
const int threshold = 100;
byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x94, 0xB5};
IPAddress ip(172, 70, 66, 999); // IP arduino
//IPAddress ip(172, 70, 66, 111); // IP PC
IPAddress subnet(255, 255, 255, 0);

static unsigned long OnDelay;
unsigned long TimeOn = 20000;

void setup() {
  Serial.begin(9600);
  delay(100);
  emon1.current(sensor, 600.600);

  delay(100);
  Ethernet.begin(mac, ip, subnet);

  // isi nilai awal register 40001 - 40012
  // isi nilai awal register 678 - 44 (nilai awal bebas mau dipake berapa)
  Mb.MbData[0] = 678;   //register 40001
  //  Mb.MbData[1] = 11;    //register 40002
  //  Mb.MbData[2] = 22;    //register 40003
  //  Mb.MbData[3] = 33;    //register 40004
  //  Mb.MbData[4] = 44;    //dan seterusnya...

  OnDelay = 0 - TimeOn;
}

void loop() {
  int Irms = emon1.calcIrms(1480);
  if (Irms > threshold) {
    OnDelay = millis();
  }

  if (millis() - OnDelay >= (TimeOn)) {
    Mb.MbData[0] = Irms;
    delay(50);
    Mb.MbsRun();
    //    Serial.println(Irms);
  } else {
    Mb.MbData[0] = Irms;
    delay(50);
    Mb.MbsRun();
    //    Serial.println(Irms);
  }
  delay(500);
}
