#include <Mhz19b.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial2(6,7);

Mhz19b mySensor;

void setup()
{
mySensor.begin(&Serial2);
Serial.begin(9600);
}

void loop()
{
Serial.println(mySensor.readGas());
delay(1000);
}