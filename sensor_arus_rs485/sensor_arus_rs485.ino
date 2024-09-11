//======= sensor arus ==========
#include "EmonLib.h"

//======= sensor & pin untuk MAX485 =======
const int sensor = 1;  //A1
#define DE_PIN 2 // Driver Enable
#define RE_PIN 3 // Receiver Enable

//======= Inisialisasi =======
EnergyMonitor emon1;
const int threshold = 100;

static unsigned long OnDelay;
unsigned long TimeOn = 20000;  // 30 Seconds

void setup() {
  Serial.begin(9600);
  delay(100);
  emon1.current(sensor, 600.600);

  // Inisialisasi pin untuk mengontrol MAX485
  pinMode(DE_PIN, OUTPUT);
  pinMode(RE_PIN, OUTPUT);

  // Aktifkan mode penerimaan
  digitalWrite(DE_PIN, LOW); // DE = 0
  digitalWrite(RE_PIN, HIGH); // RE = 1

  OnDelay = 0 - TimeOn;
  // Tunggu sejenak
  delay(1000);
}

void loop() {
  //======= Aktifkan mode transmisi =======
  digitalWrite(DE_PIN, HIGH); // DE = 1
  digitalWrite(RE_PIN, LOW); // RE = 0

  //======= Sensor baca =======
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
  // Matikan mode transmisi dan aktifkan mode penerimaan
  digitalWrite(DE_PIN, LOW); // DE = 0
  digitalWrite(RE_PIN, HIGH); // RE = 1

  delay(1000);
}
