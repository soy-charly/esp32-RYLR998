#ifndef RYLR998_H
#define RYLR998_H

#include <Arduino.h>

struct LoRaMessage {
    int sender;
    int length;
    String message;
    int rssi;
    int snr;
};

class RYLR998 {
  public:
    RYLR998(HardwareSerial &serial, int rxPin, int txPin);

    void begin(long baud = 115200);
    bool configure(int address, int networkID, long band);
    bool send(int address, String message);
    bool available();
    LoRaMessage receive();

  private:
    HardwareSerial* _serial;
    int _rxPin;
    int _txPin;

    void sendCommand(String cmd);
};

#endif

