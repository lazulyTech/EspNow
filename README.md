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
1. Write this

``` c
#include <EspNow.h>
```

2. Write this

```c
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    char macStr[18];
    Serial.print("Packet to: ");
    // Copies the sender mac address to a string
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.print(macStr);
    Serial.print(" send status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    // Serial.println("Receive!");
    Send_struct buf;
    memcpy(&buf, incomingData, sizeof(buf));
    getData = buf;
}
```

