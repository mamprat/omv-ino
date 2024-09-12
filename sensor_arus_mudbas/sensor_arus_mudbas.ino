#include <SPI.h>
#include <Ethernet.h>

#include <Mudbus.h>
int pos = 0;
Mudbus Mb;

int val;
void setup() {
  uint8_t mac[]      = { 0x90, 0xA2, 0xDA, 0x00, 0x51, 0x06 };
  uint8_t ip[]       = { 192, 168, 1, 101 };
  uint8_t gateway[]  = { 192, 168, 1, 10 };
  uint8_t subnet[]   = { 255, 255, 255, 0 };
  Ethernet.begin(mac, ip, gateway, subnet);

  delay(5000);
  Serial.begin(9600);

  pinMode(2, INPUT_PULLUP);
  pinMode(8, OUTPUT);
}


void loop() {
  Mb.Run();

  //Analog inputs 0-1023
  Mb.R[0] = analogRead(A0); //pin A0 to Mb.R[0]

  //Digital inputs
  Mb.R[1] = digitalRead(2); //pin 7 to Mb.C[7]

  //Digital outputs
  digitalWrite(8, Mb.R[2]); //pin 8 from Mb.C[8]

  //Analog outputs 0-255
  analogWrite(6, Mb.R[3]); //pin ~6 from Mb.R[6]
}
