# EspNow.h

[ESP-NOW](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_now.html) Library for ESP32 in ArduinoIDEs.

## About ESP-NOW

> ESP-NOW is a kind of connectionless Wi-Fi communication protocol that is defined by Espressif. In ESP-NOW, application data is encapsulated in a vendor-specific action frame and then transmitted from one Wi-Fi device to another without connection.
>
> CTR with CBC-MAC Protocol (CCMP) is used to protect the action frame for security. ESP-NOW is widely used in smart light, remote controlling, sensor, etc.
>
> [ESP-NOW - ESP32 - — ESP-IDF Programming Guide latest documentation | Espressif](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_now.html)

- [Original Repository](https://github.com/espressif/esp-now)
- [Original Document](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_now.html)

## Compatibility
- ESP32
- ESP32-C3
- ESP32-S2

## Usage
This library allows an ESP32-based board to communicate with other ESP32-based boards by same type of struct.

To use this library:

``` c
#include <EspNow.h>
```

