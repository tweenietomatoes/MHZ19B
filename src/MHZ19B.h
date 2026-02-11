#ifndef MHZ19B_h
#define MHZ19B_h

#include <Arduino.h>

class MHZ19B {
  public:
    MHZ19B(Stream &serial);

    void autoCalibration(bool on);
    int spanCalibration(int span);
    void zeroCalibration();
    int setRange(int range);
    int readCO2();

  private:
    Stream *_serial;
    byte _response[9];
    byte _checksum(const byte *data);
};

#endif
