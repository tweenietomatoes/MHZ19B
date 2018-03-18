#ifndef MHZ19B_h
#define MHZ19B_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class MHZ19B {
  public:
    MHZ19B(HardwareSerial *Serial);
    MHZ19B(SoftwareSerial *Serial);

    void begin();
    void autoCalibration(bool off);
    int spanCalibration(int span);
    void zeroCalibration();
    int setRange(int range);
    uint16_t readCO2();

  private:
    Stream *_Serial;
};

#endif
