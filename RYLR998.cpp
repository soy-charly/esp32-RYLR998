#include "RYLR998.h"

RYLR998::RYLR998(HardwareSerial &serial, int rxPin, int txPin) {
    _serial = &serial;
    _rxPin = rxPin;
    _txPin = txPin;
}

void RYLR998::begin(long baud) {
    _serial->begin(baud, SERIAL_8N1, _rxPin, _txPin);
    delay(2000);
}

void RYLR998::sendCommand(String cmd) {
    _serial->println(cmd);
    delay(300);
    while (_serial->available()) {
        _serial->read();
    }
}

bool RYLR998::configure(int address, int networkID, long band) {
    sendCommand("AT");
    sendCommand("AT+ADDRESS=" + String(address));
    sendCommand("AT+NETWORKID=" + String(networkID));
    sendCommand("AT+BAND=" + String(band));
    return true;
}

bool RYLR998::send(int address, String message) {
    String cmd = "AT+SEND=" + String(address) + "," + String(message.length()) + "," + message;
    _serial->println(cmd);
    return true;
}

bool RYLR998::available() {
    return _serial->available();
}

LoRaMessage RYLR998::receive() {
    LoRaMessage msg;
    String raw = _serial->readStringUntil('\n');

    // Espera formato: +RCV=1,5,Hello,-70,10
    if (raw.startsWith("+RCV=")) {
        raw.replace("+RCV=", "");

        int firstComma = raw.indexOf(',');
        int secondComma = raw.indexOf(',', firstComma + 1);
        int thirdComma = raw.indexOf(',', secondComma + 1);
        int fourthComma = raw.indexOf(',', thirdComma + 1);

        msg.sender = raw.substring(0, firstComma).toInt();
        msg.length = raw.substring(firstComma + 1, secondComma).toInt();
        msg.message = raw.substring(secondComma + 1, thirdComma);
        msg.rssi = raw.substring(thirdComma + 1, fourthComma).toInt();
        msg.snr = raw.substring(fourthComma + 1).toInt();
    }

    return msg;
}

