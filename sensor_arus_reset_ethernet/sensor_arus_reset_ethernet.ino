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

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "192, 168, 1, 177";  // Ganti dengan nama domain atau IP server
//IPAddress ip(192, 168, 1, 177);
EthernetClient client;

void setup() {
  Serial.begin(9600);
  delay(100);
  emon1.current(sensor, 600.600);

  //  Ethernet.begin(mac, ip);
  Ethernet.begin(mac);
  delay(1000);

  // Cek koneksi
  if (client.connect(server, 80)) {
    Serial.print("server is at ");
    //    Serial.print(Ethernet.localIP());
  } else {
    Serial.println("Connection failed");
  }
  OnDelay = 0 - TimeOn;
}

void loop() {
  int Irms = emon1.calcIrms(1480);  // Calculate Irms only
  if (Irms > threshold) {
    OnDelay = millis();
  }

  // Kirim data ke server
  if (client.connected()) {
    if (millis() - OnDelay >= (TimeOn)) {
      client.print("POST /update HTTP/1.1\n");
      client.print("Host: ");
      client.print(server);
      client.print("\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(String(Irms).length());
      client.print("\n\n");
      client.print("value=");
      client.print(Irms);
      delay(500);
    } else {
      client.print("POST /update HTTP/1.1\n");
      client.print("Host: ");
      client.print(server);
      client.print("\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(String(Irms).length());
      client.print("\n\n");
      client.print("value=");
      client.print(Irms);
      delay(500);
    }
    delay(5000); // Tunggu 10 detik sebelum mengirim data lagi
  }
}

//======================================================================
//void loop() {
//  int Irms = emon1.calcIrms(1480);  // Calculate Irms only
//  if (Irms > threshold) {
//    OnDelay = millis();
//  }
//  if (client.connected()) {
//    client.print(server);
//    client.print("\n");
//    if (millis() - OnDelay >= (TimeOn)) {
//      client.print(String(Irms).length());
//      client.print("\n\n");
//      client.println(Irms);
//      delay(500);
//    } else {
//      client.print(String(Irms).length());
//      client.print("\n\n");
//      client.println(Irms);
//      delay(500);
//    }
//  }
//  delay(5000);
//}
