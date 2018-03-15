#include "Arduino.h"
#include "Mhz19b.h"

Mhz19b::Mhz19b() {
  _Serial = NULL;
}

void Mhz19b::begin(SoftwareSerial *serialname)
{
  _Serial = serialname;
  _Serial->begin(9600);
}

void Mhz19b::autoCalibration (bool off)
{

const byte Start      = 0xFF;
const byte Sensor     = 0x01;
const byte Command    = 0x79;
      byte Byte3;

if (off == false)
{
Byte3                = 0x00;
}
else
{
Byte3                = 0xA0;
}

const byte Zero       = 0x00;
byte Checksum;
Checksum = (Start - (Sensor + Command + Byte3));
Checksum++;

   byte request[9] = {
    Start,
    Sensor,
    Command,
    Byte3,
    Zero,
    Zero,
    Zero,
    Zero,
    Checksum
    };
 _Serial->write(request, 9);

 _Serial->flush();
  }

char Mhz19b::spanCalibration (int span)
{
const byte Start      = 0xFF;
const byte Sensor     = 0x01;
const byte Command    = 0x88;
byte High;
byte Low;
const byte Zero       = 0x00;
byte Checksum;

if (span != 2000 || span != 1000)
{
  Serial.println("Error");
}
High = span / 256;
Low  = span % 256;

Checksum = (Start - (Sensor + Command + High + Low));
Checksum++;

   byte request[9] = {
    Start,
    Sensor,
    Command,
    High,
    Low,
    Zero,
    Zero,
    Zero,
    Checksum
    };

  _Serial->write(request, 9);

  _Serial->flush();
  }


void Mhz19b::zeroCalibration ()
 {

const byte Start      = 0xFF;
const byte Sensor     = 0x01;
const byte Command    = 0x87;
const byte Zero       = 0x00;
const byte Checksum   = 0x78;

   byte request[9] = {
    Start,
    Sensor,
    Command,
    Zero,
    Zero,
    Zero,
    Zero,
    Zero,
    Checksum
    };

   _Serial->write(request, 9);

   _Serial->flush();
}

char Mhz19b::setRange (int range)
{
      const byte Start      = 0xFF;
      const byte Sensor     = 0x01;
      const byte Command    = 0x99;
      const byte Zero       = 0x00;
      byte High;
      byte Low;
      byte Checksum;

if (range != 5000 || range != 2000)
{
   Serial.println("Error");
}

   High = range / 256;
   Low  = range % 256;
   Checksum = (Start - (Sensor + Command + High + Low));
   Checksum++;

   byte request[9] = {
    Start,
    Sensor,
    Command,
    High,
    Low,
    Zero,
    Zero,
    Zero,
    Checksum
    };

   _Serial->write(request, 9);

   _Serial->flush();

}

uint16_t Mhz19b::readGas()
{

      const int Start      = 0xFF;
      const int Sensor     = 0x01;
      const int Command    = 0x86;
      const int Zero       = 0x00;
      const int Checksum   = 0x79;

    byte request[9] = {
    Start,
    Sensor,
    Command,
    Zero,
    Zero,
    Zero,
    Zero,
    Zero,
    Checksum
    };

  byte response[9];

  _Serial->write(request, 9);

  _Serial->flush();

  while (_Serial->available() && _Serial->peek() != 0xFF) {
    _Serial->read();
    delay(1);
  }

  _Serial->readBytes(response, 9);

  if (response[0] != 0xFF && response[1] != 0x86)
  {
    return -1;
  }

  byte checksum = 0;
  for (int i = 1; i < 8; i++) {
    checksum += response[i];
  }
  checksum = 0xFF - checksum;
  checksum++;

   if (response[8] != checksum) {
     return -2;
   }

    uint16_t low  = (uint16_t)response[3];
    uint16_t high = (uint16_t)response[2];
    uint16_t ppm = (256 * high) + low;

    if (ppm < 0)
    ppm = 0;
    return ppm;

}
