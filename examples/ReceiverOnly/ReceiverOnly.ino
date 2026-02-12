#include <RYLR998.h>

#define RXD2 16
#define TXD2 17

HardwareSerial loraSerial(2);
RYLR998 lora(loraSerial, RXD2, TXD2);

void setup() {
  Serial.begin(115200);
  lora.begin();
  lora.configure(2, 5, 868000000);
  Serial.println("Receiver listo. Esperando mensajes...");
}

void loop() {
  if (lora.available()) {
    LoRaMessage msg = lora.receive();
    Serial.println("---- Mensaje recibido ----");
    Serial.print("De: "); Serial.println(msg.sender);
    Serial.print("Mensaje: "); Serial.println(msg.message);
    Serial.print("RSSI: "); Serial.println(msg.rssi);
    Serial.print("SNR: "); Serial.println(msg.snr);
    Serial.println("--------------------------");
  }
}

