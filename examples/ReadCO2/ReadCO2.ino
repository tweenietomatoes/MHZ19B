#include <SoftwareSerial.h>
#include <MHZ19B.h>

SoftwareSerial sensorSerial(6, 7); // RX, TX

MHZ19B mhz19b(sensorSerial);

void setup() {
  Serial.begin(9600);
  sensorSerial.begin(9600);
}

void loop() {
  int ppm = mhz19b.readCO2();
  if (ppm >= 0) {
    Serial.print("CO2: ");
    Serial.print(ppm);
    Serial.println(" ppm");
  }
  delay(1000);
}
