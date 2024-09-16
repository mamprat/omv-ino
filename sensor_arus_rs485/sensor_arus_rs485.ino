//======= library =======
#include "EmonLib.h"
#include <SoftwareSerial.h>

//======= alamat =======
const int sensor = 1;  //A1
//MAX485
#define DE 3  //MAX485 to arduino D3
#define RE 2  //MAX485 to arduino D2

SoftwareSerial RS485Serial(10, 11); // RX, TX

//======= inisialisasi =======
EnergyMonitor emon1;
const int threshold = 100;
static unsigned long OnDelay;
unsigned long TimeOn = 20000;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600); // cuman buat di serial monitor
  RS485Serial.begin(9600); //komunikasi RS485
  emon1.current(sensor, 600.600);
  delay(100);

  // Set the DE and RE pins as outputs
  pinMode(DE, OUTPUT);
  pinMode(RE, OUTPUT);

  // Set DE and RE high to enable transmission mode or WRITE
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);

  //  // Set DE and RE low to enable receiving mode or READ
  //  digitalWrite(DE, LOW);
  //  digitalWrite(RE, LOW);
}

void loop() {
  int Irms = emon1.calcIrms(1480);
  if (Irms > threshold) {
    OnDelay = millis();
  }

  if (millis() - OnDelay >= (TimeOn)) {
    RS485Serial.write(Irms);
    Serial.println(Irms);
  } else {
    RS485Serial.write(Irms);
    Serial.println(Irms);
  }
  delay(500);
}
