/* kalo mau kirim data dari arduino ke PC
  RO = **RX (kosong juga gpp)
  RE = HIGH masuk ke pin Digial (kasih 5volt klo pin tidak di inisial) (aslinya klo mau slave nerima itu harus low)
  DE = HIGH masuk ke pin Digital (kasih 5volt klo pin tidak di inisial)**TRANSMIT TX
  DI = TX

  VCC  = 5V
  B = USB_B
  A = USB_A
  GND = GND */

//======= library =======
#include "EmonLib.h"
#include <SoftwareSerial.h>

//======= alamat =======
const int sensor = 1;  //A1
#define DE 3  //MAX485 to arduino D3

SoftwareSerial RS485Serial(10, 11); // RX = RO, TX = DI

//======= inisialisasi =======
EnergyMonitor emon1;
const int threshold = 100;
static unsigned long OnDelay;
unsigned long TimeOn = 20000;

void setup() {
  Serial.begin(9600); // cuman buat di serial monitor
  RS485Serial.begin(9600); //komunikasi RS485
  emon1.current(sensor, 600.600);
  delay(100);

  // Set the DE and RE pins as outputs
  pinMode(DE, OUTPUT);

  // Set DE to enable transmission mode or WRITE
  digitalWrite(DE, HIGH); //HIGH (kasih 5volt)**TRANSMIT TX
}

void loop() {
  int Irms = emon1.calcIrms(1480);
  if (Irms > threshold) {
    OnDelay = millis();
  }

  if (millis() - OnDelay >= (TimeOn)) {
    RS485Serial.println(Irms);
    digitalWrite(DE, HIGH);
  } else {
    RS485Serial.println(Irms);
    digitalWrite(DE, HIGH);
  }
  delay(500);
}
