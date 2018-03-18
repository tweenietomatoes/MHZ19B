#include <MHZ19B.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial2(6,7);

MHZ19B mhz19b;

void setup()
{
mhz19b.begin(&Serial2);
Serial.begin(9600);
}

void loop()
{
Serial.println(mhz19b.readCO2());
  //mhz19b.autoCalibration(x) , This feature is enabled as default, x = false or true , false = off true = on
  //mhz19b.spanCalibration(y) , y = 2000 or 1000  
  //mhz19b.zeroCalibration()  , Run it at least 20 minute at atmospheric CO2 level
  //mhz19b.setRange(z)        , Default is 5000 , z = 5000 or 2000 , max level of CO2 to be sensed.
delay(1000);
}
