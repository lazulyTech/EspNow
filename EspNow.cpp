#include "EspNow.h"
#include <esp_now.h>

esp_now_peer_info_t EspNow::peerInfo;

EspNow::EspNow(){
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    } else {
        Serial.println("Successful initializing ESP-NOW");
    }
}

void EspNow::Init(Role _role, esp_now_send_cb_t send_cb, esp_now_recv_cb_t recv_cb){
    role = _role;
    if(role == MEMBER){
        esp_now_register_send_cb(send_cb);
        peerInfo.channel = 0;
        peerInfo.encrypt = false;

        esp_now_register_recv_cb(recv_cb);
    }
}

bool EspNow::addPeer(uint8_t* address){
    if(role == SENDER || role == MEMBER){
        memcpy(peerInfo.peer_addr, address, 6);
        return (esp_now_add_peer(&peerInfo) == ESP_OK);
    } else {
        return false;
    }
}
