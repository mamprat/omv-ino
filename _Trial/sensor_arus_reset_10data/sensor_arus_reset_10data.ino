//======= sensor arus =======
#include "EmonLib.h"
//======= sensor =======
const int sensor = 1;  //A1
const int pinReset = 8;

//======= inisialisasi =======
EnergyMonitor emon1;
const int threshold = 100;

static unsigned long OnDelay;
unsigned long TimeOn = 20000;

void (*reset)(void) = 0;
int printCounter = 0;
int dataPrint = 10;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    digitalWrite(pinReset, HIGH);
    delay(100);
    pinMode(pinReset, OUTPUT);
  }
  Serial.println("reset successful");
  delay(100);
  emon1.current(sensor, 600.600);
  OnDelay = 0 - TimeOn;
}

void loop() {
  int Irms = emon1.calcIrms(1480);
  if (Irms > threshold) {
    OnDelay = millis();
  }

  if (millis() - OnDelay >= (TimeOn)) {
    //     Serial.println(Irms);
    Serial.println("0");
    printCounter++;
  } else {
    //    Serial.println(Irms);
    Serial.println("1");
    printCounter++;
  }

  if (printCounter >= dataPrint) {
    delay(100);
    digitalWrite(pinReset, LOW);
    delay(100);
    reset();
  }
  delay(500);
}
