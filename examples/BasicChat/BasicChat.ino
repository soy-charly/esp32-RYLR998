#include <RYLR998.h>

#define RXD2 16
#define TXD2 17

HardwareSerial loraSerial(2);
RYLR998 lora(loraSerial, RXD2, TXD2);

void setup() {
  Serial.begin(115200);
  lora.begin();
  lora.configure(1, 5, 868000000);
  Serial.println("Sistema listo. Escribe mensaje:");
}

void loop() {
  // Enviar
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    msg.trim();
    if (msg.length() > 0) {
      lora.send(2, msg);
      Serial.println("Enviado");
    }
  }

  // Recibir
  if (lora.available()) {
    LoRaMessage incoming = lora.receive();
    Serial.println("---- Mensaje recibido ----");
    Serial.print("De: "); Serial.println(incoming.sender);
    Serial.print("Mensaje: "); Serial.println(incoming.message);
    Serial.print("RSSI: "); Serial.println(incoming.rssi);
    Serial.print("SNR: "); Serial.println(incoming.snr);
    Serial.println("--------------------------");
  }
}

