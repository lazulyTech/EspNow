//
// Created by Eisuke Kato on 24/10/22.
//

#ifndef ESPNOW_H
#define ESPNOW_H

#if defined(ARDUINO_M5Stick_C)
    #include <M5StickCPlus.h>
#elif defined(M5Stack_Core_ESP32)
    #include <M5Stack.h>
#else
    #include <Arduino.h>
    #include <Esp.h>
#endif
#include <esp_now.h>
#include <WiFi.h>

enum Role{
    SENDER,
    RECEIVER,
    MEMBER
};

void _OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void _OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len);

class EspNow {
private:
    Role role;
    uint32_t structSize;

public:
    static esp_now_peer_info_t peerInfo;
    static void (*on_sent_callback)(const uint8_t*, esp_now_send_status_t);
    static void (*on_recv_callback)(const uint8_t*, const uint8_t*, int);
    EspNow();

    void Init(Role _role, uint32_t structSize);

    bool addPeer(uint8_t* address);

    void set_SentCallback(void (*Callback)(const uint8_t*, esp_now_send_status_t));
    void set_RecvCallback(void (*Callback)(const uint8_t*, const uint8_t*, int));

    uint8_t* getData();

    bool send(const uint8_t* address, uint8_t* message);
};

#endif //ESPNOW_H
