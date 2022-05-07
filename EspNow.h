#ifndef ESPNOW_H
#define ESPNOW_H

#if defined(ARDUINO_M5Stick_C)
    #include <M5StickCPlus.h>
#elif defined(M5Stack_Core_ESP32)
    #include <M5Stack.h>
#else
    #include <Arduino.h>
#endif
#include <esp_now.h>
#include <WiFi.h>

enum Role{
    SENDER,
    RECEIVER,
    MEMBER
};

class EspNow {
private:
    Role role;
public:
    static esp_now_peer_info_t peerInfo;
    EspNow();

    template <typename esp_now_cb>
    void Init(Role _role, esp_now_cb cb){
        role = _role;
        if(role == SENDER || role == MEMBER){
            esp_now_register_send_cb((esp_now_send_cb_t)cb);
            peerInfo.channel = 0;
            peerInfo.encrypt = false;
        }
        if(role == RECEIVER || role == MEMBER){
            esp_now_register_recv_cb((esp_now_recv_cb_t)cb);
        }
    }

    void Init(Role _role, esp_now_send_cb_t send_cb, esp_now_recv_cb_t recv_cb);
    bool addPeer(uint8_t* address);
    
    template <typename Message>
    bool send(const uint8_t* address, Message message){
        if(role == SENDER || role == MEMBER){
            esp_err_t result;
            result = esp_now_send(address, (uint8_t*) &message, sizeof(Message));
            return (result == ESP_OK);
        } else {
            return false;
        }
    }
};

#endif //ESPNOW_H
