#ifndef Mhz19b_h
#define Mhz19b_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class Mhz19b {
  public:

    Mhz19b();

    void begin(SoftwareSerial *serialname);
    void autoCalibration(bool off);
    char spanCalibration(int span);
    void zeroCalibration();
    char setRange(int range);
    uint16_t readGas();

  private:
    SoftwareSerial *_Serial;
};

#endif
