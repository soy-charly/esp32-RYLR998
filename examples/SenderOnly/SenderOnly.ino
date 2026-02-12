#include <RYLR998.h>

#define RXD2 16
#define TXD2 17

HardwareSerial loraSerial(2);
RYLR998 lora(loraSerial, RXD2, TXD2);

void setup() {
  Serial.begin(115200);
  lora.begin();
  lora.configure(1, 5, 868000000);
  Serial.println("Sender listo. Escribe mensajes para enviar:");
}

void loop() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    msg.trim();
    if (msg.length() > 0) {
      lora.send(2, msg);
      Serial.println("Mensaje enviado");
    }
  }
}

