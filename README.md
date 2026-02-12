# RYLR998 Arduino Library

Librería para controlar el módulo **RYLR998 (LoRa)** con **ESP32** en Arduino IDE.
Permite inicializar, configurar, enviar y recibir mensajes de manera sencilla usando comandos AT, sin necesidad de escribirlos manualmente.

## Características

* Inicialización rápida del módulo LoRa.
* Configuración de dirección, network ID y frecuencia.
* Envío de mensajes a nodos específicos.
* Lectura de mensajes recibidos con información de:

  * Dirección del remitente
  * Longitud del mensaje
  * Contenido del mensaje
  * RSSI
  * SNR
* Compatible con ESP32 y Arduino IDE.
* Ejemplos incluidos: BasicChat, SenderOnly, ReceiverOnly.
* Fácil integración en proyectos de comunicación LoRa o IoT.

## Instalación

### Manual

1. Copia la carpeta `RYLR998` en:

```cpp
~/Arduino/libraries/
```

2. Reinicia Arduino IDE.
3. Incluye la librería en tu sketch:

```cpp
#include <RYLR998.h>
```

4. Selecciona la placa **ESP32 Dev Module** y el puerto correspondiente.

### Automática con archivo `.zip`

1. Descarga la librería como un archivo `.zip`.
2. Abre Arduino IDE.
3. Ve a **Sketch → Incluir Librería → Añadir biblioteca .ZIP…**
4. Selecciona el archivo `.zip` descargado.
5. La librería se instalará automáticamente y aparecerá en **Sketch → Incluir Librería**.
6. Incluye la librería en tu sketch:

```cpp  
#include <RYLR998.h>
```

## Conexión ESP32 ↔ RYLR998

| RYLR998 | ESP32  |
| ------- | ------ |
| VDD     | 3.3V   |
| GND     | GND    |
| TXD     | GPIO16 |
| RXD     | GPIO17 |

> Importante: El RYLR998 funciona a 3.3V. No conectar a 5V.

## Ejemplo rápido (BasicChat)
```cpp
#include <RYLR998.h>

#define RXD2 16
#define TXD2 17

HardwareSerial loraSerial(2);
RYLR998 lora(loraSerial, RXD2, TXD2);

void setup() {
  Serial.begin(115200);
  lora.begin();
  lora.configure(1, 5, 868000000); // Dirección, NetworkID, Banda
  Serial.println("Sistema listo. Escribe mensaje:");
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

  if (lora.available()) {
    LoRaMessage incoming = lora.receive();
    Serial.println("Mensaje recibido:");
    Serial.print("De: "); Serial.println(incoming.sender);
    Serial.print("Mensaje: "); Serial.println(incoming.message);
    Serial.print("RSSI: "); Serial.println(incoming.rssi);
    Serial.print("SNR: "); Serial.println(incoming.snr);
    Serial.println("----------------------");
  }
}
```

## Ejemplos incluidos

* **BasicChat**: Comunicación bidireccional tipo chat.
* **SenderOnly**: Solo envío de mensajes.
* **ReceiverOnly**: Solo recepción de mensajes.

## Uso básico

```cpp
lora.begin();
lora.configure(address, networkID, band);
lora.send(destAddress, "Hola mundo");
if (lora.available()) {
    LoRaMessage msg = lora.receive();
}
```
