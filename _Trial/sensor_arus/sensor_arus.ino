//tipe sensor yang digunakan adalah Sct 019


//======= sensor arus ==========
#include "EmonLib.h"

// //======= sensor =======
const int sensor = 1;  //A1

//======= Inisialisasi =======
EnergyMonitor emon1;
const int threshold = 100;

static unsigned long OnDelay;
unsigned long TimeOn = 20000;  // 30 Seconds

 void setup() {
   Serial.begin(9600);
   delay(100);
   emon1.current(sensor, 600.600);  
   OnDelay = 0 - TimeOn;
 }

void loop() {
  int Irms = emon1.calcIrms(1480);  // Calculate Irms only
  if (Irms > threshold) {
    OnDelay = millis();
  }

  if (millis() - OnDelay >= (TimeOn)) {
    Serial.println(Irms);
    delay(500);
  } else {
    Serial.println(Irms);
    delay(500);
  }
}
