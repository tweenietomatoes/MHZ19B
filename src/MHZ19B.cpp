#include "MHZ19B.h"

MHZ19B::MHZ19B(Stream &serial) : _serial(&serial) {}

byte MHZ19B::_checksum(const byte *data) {
  byte sum = 0;
  for (int i = 1; i < 8; i++) {
    sum += data[i];
  }
  return (~sum) + 1;
}

void MHZ19B::autoCalibration(bool on) {
  byte request[9] = {
    0xFF, 0x01, 0x79,
    (byte)(on ? 0xA0 : 0x00),
    0x00, 0x00, 0x00, 0x00, 0x00
  };
  request[8] = _checksum(request);
  _serial->write(request, 9);
  _serial->flush();
}

int MHZ19B::spanCalibration(int span) {
  if (span != 2000 && span != 1000) {
    return -1;
  }
  byte high = span / 256;
  byte low = span % 256;
  byte request[9] = {
    0xFF, 0x01, 0x88,
    high, low,
    0x00, 0x00, 0x00, 0x00
  };
  request[8] = _checksum(request);
  _serial->write(request, 9);
  _serial->flush();
  return 0;
}

void MHZ19B::zeroCalibration() {
  byte request[9] = {
    0xFF, 0x01, 0x87,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x78
  };
  _serial->write(request, 9);
  _serial->flush();
}

int MHZ19B::setRange(int range) {
  if (range != 2000 && range != 5000) {
    return -1;
  }
  byte high = range / 256;
  byte low = range % 256;
  byte request[9] = {
    0xFF, 0x01, 0x99,
    0x00, 0x00, 0x00,
    high, low, 0x00
  };
  request[8] = _checksum(request);
  _serial->write(request, 9);
  _serial->flush();
  return 0;
}

int MHZ19B::readCO2() {
  byte request[9] = {
    0xFF, 0x01, 0x86,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x79
  };
  _serial->write(request, 9);
  _serial->flush();

  while (_serial->available() > 0 && _serial->peek() != 0xFF) {
    _serial->read();
  }

  if (_serial->readBytes(_response, 9) != 9) {
    return -1;
  }

  if (_response[0] != 0xFF || _response[1] != 0x86) {
    return -1;
  }

  if (_response[8] != _checksum(_response)) {
    return -2;
  }

  return (_response[2] * 256) + _response[3];
}
