//==============================================
// CALIBRASI
//==============================================
//Kondisi           Baca tang amper         Baca Serial Monitor
//Motor idle        misal: 8.50 A           misal: 5.12 A
//Motor grinding    misal: 22.0 A           misal: 13.28 A

//Faktor idle       = 8.50 / 5.12         = 1.660
//Faktor giling     = 22.0 / 13.28        = 1.657
//Rata-rata         = (1.660 + 1.657) / 2 = 1.658

//CALIB_FACTOR = CALIB_FACTOR LAMA(misal: 600.6) × 1.658       = 995.8

#include "EmonLib.h"
#include <SoftwareSerial.h>

//==============================================
// KONFIGURASI
//==============================================
const int   SENSOR_PIN  = 1;       // A1
float       CALIB_FACTOR = 600.6;  // ubah hasil kalibrasi tang amper
#define     DE_RE_PIN   3
const int   ADC_SAMPLES = 4800;
const float EMA_ALPHA   = 0.35;    // nilai ema= di Serial Monitor terasa terlalu lambat naik saat bahan masuk → naikkan ke 0.5. Kalau masih terlalu goyang → turunkan ke 0.2
const float NOISE_FLOOR = 0.10;    // nilai ema= saat motor mati total. Kalau masih muncul angka kecil seperti 0.08 atau 0.05 → naikkan sedikit ke 0.15

//==============================================
// GLOBAL OBJECTS
//==============================================
SoftwareSerial RS485(10, 11);
EnergyMonitor  emon1;
float          emaValue = 0.0;

//==============================================
// SETUP
//==============================================
void setup() {
  Serial.begin(9600);
  RS485.begin(9600);

  pinMode(DE_RE_PIN, OUTPUT);
  digitalWrite(DE_RE_PIN, LOW);

  emon1.current(SENSOR_PIN, CALIB_FACTOR);
  delay(200);

  for (int i = 0; i < 5; i++) {
    float v = emon1.calcIrms(ADC_SAMPLES);
    emaValue = (emaValue < NOISE_FLOOR) ? v
               : EMA_ALPHA * v + (1.0 - EMA_ALPHA) * emaValue;
  }
  Serial.println("[INIT] Ready");
}

//==============================================
// LOOP
//==============================================
void loop() {
  float raw = emon1.calcIrms(ADC_SAMPLES);
  if (raw < NOISE_FLOOR) raw = 0.0;

  float smooth = applyEMA(raw);   // dari filter.ino
  sendRS485(smooth);              // dari rs485.ino

  Serial.print("raw=");   Serial.print(raw, 3);
  Serial.print("  ema="); Serial.println(smooth, 3);
}
